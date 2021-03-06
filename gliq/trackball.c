/*
 *  Simple trackball-like motion ripped off from projtex.c (written by
 *  David Yu and David Blythe).  See the GLUT sample programs (advanced).
 *
 *  Copyright (C) 1997 Nate Robins (ndr@pobox.com)
 *
 *  email: ndr@pobox.com
 *  www: http://www.pobox.com/~ndr
 *
 *  This program is freely distributable without licensing fees and is
 *  provided without guarantee or warrantee expressed or implied. This
 *  program is not in the public domain.
 *
 */


/* includes */
#include <math.h>
#include <GL/glut.h>
#include "trackball.h"


/* globals */
static GLuint    tb_lasttime;
static GLfloat   tb_lastposition[3];

static GLfloat   tb_angle = 0.0;
static GLfloat   tb_axis[3];
static GLfloat   tb_transform[4][4];

static GLuint    tb_width;
static GLuint    tb_height;

static GLint     tb_button = -1;
static GLboolean tb_animate = GL_TRUE;


/* functions */
static void
_tbPointToVector(int x, int y, int width, int height, float v[3])
{
  float d, a;

  /* project x, y onto a hemi-sphere centered within width, height. */
  v[0] = (2.0 * x - width) / width;
  v[1] = (height - 2.0 * y) / height;
  d = sqrt(v[0] * v[0] + v[1] * v[1]);
  v[2] = cos((3.14159265 / 2.0) * ((d < 1.0) ? d : 1.0));
  a = 1.0 / sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
  v[0] *= a;
  v[1] *= a;
  v[2] *= a;
}

static void
_tbAnimate(void)
{
  glutPostRedisplay();
}

void
tbInit()
{
  /* put the identity in the trackball transform */
  glPushMatrix();
  glLoadIdentity();
  glGetFloatv(GL_MODELVIEW_MATRIX, (GLfloat *)tb_transform);
  glPopMatrix();
}

void
tbMatrix()
{
  glPushMatrix();
  glLoadIdentity();
  glRotatef(tb_angle, tb_axis[0], tb_axis[1], tb_axis[2]);
  glMultMatrixf((GLfloat *)tb_transform);
  glGetFloatv(GL_MODELVIEW_MATRIX, (GLfloat *)tb_transform);
  glPopMatrix();

  glMultMatrixf((GLfloat *)tb_transform);
}

void
tbReshape(int width, int height)
{
  tb_width  = width;
  tb_height = height;
}

void
tbStartMotion(int x, int y, int button, int time)
{
  tb_button = button;
  tb_lasttime = time;
  _tbPointToVector(x, y, tb_width, tb_height, tb_lastposition);
}

void
tbStopMotion(int button, unsigned time)
{
  tb_button = -1;

  if (time == tb_lasttime && tb_animate) {
    glutIdleFunc(_tbAnimate);
  } else {
    tb_angle = 0.0;
    if (tb_animate)
      glutIdleFunc(0);
  }
}

void
tbMotion(int x, int y)
{
  GLfloat current_position[3], dx, dy, dz;

  if (tb_button == -1)
    return;

  _tbPointToVector(x, y, tb_width, tb_height, current_position);

  /* calculate the angle to rotate by (directly proportional to the
     length of the mouse movement */
  dx = current_position[0] - tb_lastposition[0];
  dy = current_position[1] - tb_lastposition[1];
  dz = current_position[2] - tb_lastposition[2];
  tb_angle = 90.0 * sqrt(dx * dx + dy * dy + dz * dz);

  /* calculate the axis of rotation (cross product) */
  tb_axis[0] = tb_lastposition[1] * current_position[2] - 
               tb_lastposition[2] * current_position[1];
  tb_axis[1] = tb_lastposition[2] * current_position[0] - 
               tb_lastposition[0] * current_position[2];
  tb_axis[2] = tb_lastposition[0] * current_position[1] - 
               tb_lastposition[1] * current_position[0];

  /* reset for next time */
  tb_lasttime = glutGet(GLUT_ELAPSED_TIME);
  tb_lastposition[0] = current_position[0];
  tb_lastposition[1] = current_position[1];
  tb_lastposition[2] = current_position[2];

  /* remember to draw new position */
  glutPostRedisplay();
}
