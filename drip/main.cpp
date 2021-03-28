/*
 * (c) Copyright 1993, 1994, 1995, 1996 Silicon Graphics, Inc.
 * ALL RIGHTS RESERVED 
 * Permission to use, copy, modify, and distribute this software for 
 * any purpose and without fee is hereby granted, provided that the above
 * copyright notice appear in all copies and that both the copyright notice
 * and this permission notice appear in supporting documentation, and that 
 * the name of Silicon Graphics, Inc. not be used in advertising
 * or publicity pertaining to distribution of the software without specific,
 * written prior permission. 
 *
 * THE MATERIAL EMBODIED ON THIS SOFTWARE IS PROVIDED TO YOU "AS-IS"
 * AND WITHOUT WARRANTY OF ANY KIND, EXPRESS, IMPLIED OR OTHERWISE,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY OR
 * FITNESS FOR A PARTICULAR PURPOSE.  IN NO EVENT SHALL SILICON
 * GRAPHICS, INC.  BE LIABLE TO YOU OR ANYONE ELSE FOR ANY DIRECT,
 * SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY
 * KIND, OR ANY DAMAGES WHATSOEVER, INCLUDING WITHOUT LIMITATION,
 * LOSS OF PROFIT, LOSS OF USE, SAVINGS OR REVENUE, OR THE CLAIMS OF
 * THIRD PARTIES, WHETHER OR NOT SILICON GRAPHICS, INC.  HAS BEEN
 * ADVISED OF THE POSSIBILITY OF SUCH LOSS, HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE
 * POSSESSION, USE OR PERFORMANCE OF THIS SOFTWARE.
 * 
 * US Government Users Restricted Rights 
 * Use, duplication, or disclosure by the Government is subject to
 * restrictions set forth in FAR 52.227.19(c)(2) or subparagraph
 * (c)(1)(ii) of the Rights in Technical Data and Computer Software
 * clause at DFARS 252.227-7013 and/or in similar or successor
 * clauses in the FAR or the DOD or NASA FAR Supplement.
 * Unpublished-- rights reserved under the copyright laws of the
 * United States.  Contractor/manufacturer is Silicon Graphics,
 * Inc., 2011 N.  Shoreline Blvd., Mountain View, CA 94039-7311.
 *
 * OpenGL(TM) is a trademark of Silicon Graphics, Inc.
 */
#include "Drip.h"

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <GL/glut.h>
#ifdef WIN32
#include <windows.h>
#include <winsock.h>
#define trunc(x) ((float)((int)(x)))

// Implementation of gettimeofday() taken from reply by user Michaelangel007 to post on Stackoverflow
// "Equivalent of gettimeday() for Windows" <https://stackoverflow.com/questions/10905892/equivalent-of-gettimeday-for-windows>

int gettimeofday(struct timeval * tp, struct timezone * tzp)
{
    // Note: some broken versions only have 8 trailing zero's, the correct epoch has 9 trailing zero's
    // This magic number is the number of 100 nanosecond intervals since January 1, 1601 (UTC)
    // until 00:00:00 January 1, 1970 
    static const uint64_t EPOCH = ((uint64_t) 116444736000000000ULL);

    SYSTEMTIME  system_time;
    FILETIME    file_time;
    uint64_t    time;

    GetSystemTime( &system_time );
    SystemTimeToFileTime( &system_time, &file_time );
    time =  ((uint64_t)file_time.dwLowDateTime )      ;
    time += ((uint64_t)file_time.dwHighDateTime) << 32;

    tp->tv_sec  = (long) ((time - EPOCH) / 10000000L);
    tp->tv_usec = (long) (system_time.wMilliseconds * 1000);
    return 0;
}
#else
#include <sys/time.h>
#endif


float win_width, win_height;
float random_time;
float random_probability;	
float drips_second;

int rrandom = 0;
float *points;
int create_drips;
int random_color;

float back_r = 0, back_g = 0, back_b = 0;

float speed = 0.25;			/* Scaling factor for time */

const int max_drips = 255;
float drip_position[max_drips][2];
float drip_age[max_drips];		/* Age in seconds */
Drip *drips[max_drips];

int first_drip, new_drip;

const float time_gran = 0.0001;		/* Granularity of time */
struct timeval old_time;

const float scale_radius = 100.0;	/* This relates radius to time */
const float max_ring_radius = 250.0;	/* How big to let them get before
					 * destroying them */

const float default_drips_second = 3.0;	/* How many drips should be randomly
					 * created for a full-size screen */


float probability(float win_width, float win_height)
{
    float dpy_area = glutGet(GLUT_SCREEN_WIDTH) * glutGet(GLUT_SCREEN_HEIGHT);
    float win_area = win_width * win_height;

    return (win_area / dpy_area);
}

inline float randmax(float max = 1.0) 
{
    return (max * ((float)rand() / (float)RAND_MAX));
}

inline float ring_increment(float dt)
{
    return dt * scale_radius;
}

inline float outer_increment(float dt) 
{
    return 2.0 * dt * scale_radius;
}

float draw() 
{
    struct timeval new_time;
    float dtime;
    float rel_size;
    int i;

    gettimeofday(&new_time, NULL);
    if (old_time.tv_sec == 0 && old_time.tv_usec == 0) {
	old_time.tv_sec = new_time.tv_sec;
	old_time.tv_usec = new_time.tv_usec;
	dtime = 0.0;
    } else {
	dtime = (new_time.tv_sec - old_time.tv_sec) +
	    (new_time.tv_usec - old_time.tv_usec) / 1000000.0;
	dtime *= speed;
	if (dtime < time_gran) dtime = 0.0;
    }

    glClear(GL_COLOR_BUFFER_BIT);

    for (i = first_drip; i != new_drip; i = (i + 1) % max_drips) {
	glPushMatrix();
	glTranslatef(drip_position[i][0], drip_position[i][1], 0.0);
	drips[i]->draw();
	glPopMatrix();
    
	drip_age[i] += dtime;
	drips[i]->ring_radius += ring_increment(dtime);
	drips[i]->outer_radius += outer_increment(dtime);

	rel_size = drips[i]->ring_radius / max_ring_radius;
	drips[i]->ring_color[3] = 1.0 - rel_size*rel_size;
	drips[i]->inner_color[3] = 1.0 - rel_size;

	/* This is a bit of a hack, but makes sense */
	if (drips[i]->ring_radius > max_ring_radius) 
	    first_drip = (first_drip + 1) % max_drips;
    }

    glutSwapBuffers();
  
    if (dtime > 0.0) {
	old_time.tv_sec = new_time.tv_sec;
	old_time.tv_usec = new_time.tv_usec;
    }

    return dtime;

}

void create_drip(float x, float y, float r, float g, float b)
{
    drips[new_drip]->inner_color[0] = drips[new_drip]->ring_color[0] = 
	drips[new_drip]->outer_color[0] = r;
    drips[new_drip]->inner_color[1] = drips[new_drip]->ring_color[1] = 
	drips[new_drip]->outer_color[1] = g;
    drips[new_drip]->inner_color[2] = drips[new_drip]->ring_color[2] = 
	drips[new_drip]->outer_color[2] = b;

    drips[new_drip]->inner_color[3] = 1.0;
    drips[new_drip]->ring_color[3] = 1.0;
    drips[new_drip]->outer_color[3] = 0.0;
  
    drips[new_drip]->ring_radius = 0.0;
    drips[new_drip]->outer_radius = 0.0;

    drip_position[new_drip][0] = x;
    drip_position[new_drip][1] = y;

    drip_age[new_drip] = 0.0;

    new_drip = (new_drip + 1) % max_drips;
    if (new_drip == first_drip) 
	first_drip = (first_drip + 1) % max_drips;
}


void
mouse(int button, int state, int x, int y)
{
    if (state == GLUT_DOWN) {
	create_drip((float)x, 
		    glutGet(GLUT_WINDOW_HEIGHT) - (float)y,
		    button == GLUT_LEFT_BUTTON ? 1.0 : 0.0,
		    button == GLUT_MIDDLE_BUTTON ? 1.0 : 0.0,
		    button == GLUT_RIGHT_BUTTON ? 1.0 : 0.0);
	drip_age[new_drip] = 0.0;
    }
}

void
keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case ' ':
	new_drip = first_drip = 0;
	break;
    case 27:				/* ESC */
	exit(0);
    }
}

void
reshape(int width, int height)
{
    win_width = width;
    win_height = height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, win_width, 0, win_height, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); 
    random_probability = probability(win_width, win_height);
}

void
display()
{
    draw();
}

void
idle()
{
    int i;

    random_time += draw() * drips_second;
    if (rrandom) {
	create_drips = (int)trunc(random_time);
	for (i = 0; i < create_drips; i++) {
	    if (randmax() < random_probability) {
		random_color = (int)randmax(3.0);
		create_drip(randmax(win_width), randmax(win_height), 
			    random_color == 0 ? 1.0 : 0.0, 
			    random_color == 1 ? 1.0 : 0.0,
			    random_color == 2 ? 1.0 : 0.0);
	    }
	}
	random_time = random_time - (float)create_drips;
    }
}

int main(int argc, char **argv)
{
    int fullscreen = 0;
    int i;
  
    glutInit(&argc, argv);

    for (i = 1; i < argc; i++) 
	switch(argv[i][1]) {
	case 'f':
	    fullscreen = 1;
	    break;
	case 'r': 
	    rrandom = 1;
	    drips_second = atof(&argv[i][2]);
	    if (drips_second == 0.0) drips_second = default_drips_second;
	    break;
	case 'w':
	    back_r = back_g = back_b = 1.0;
	    break;
	case 'h':
	default:
	    fprintf(stderr, "Usage:\n%s [-r[number]] [-f] [-w]\n", argv[0]);
	    break;
	}

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutCreateWindow("Drip");
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutDisplayFunc(display);
    glutIdleFunc(idle);

    if (fullscreen) 
	glutFullScreen();

    drips[0] = new Drip();
    drips[0]->alloc_points();
    drips[0]->fill_points();
    points = drips[0]->get_points();
    for (i = 1; i < max_drips; i++) {
	drips[i] = new Drip();
	drips[i]->set_points(points);
    }

    first_drip = new_drip = 0;

    old_time.tv_sec = 0;
    old_time.tv_usec = 0;

    random_time = 0.0;
    random_probability = 0.0;

    win_width = win_height = 0.0;

    glClearColor(back_r, back_g, back_b, 1.0);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    glutMainLoop();
}
