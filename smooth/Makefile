#!make

TARGETS = smooth
SRCS = smooth.c trackball.c glm.c gltx.c
OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall
LDFLAGS = -mconsole -lfreeglut -lglew32 -lglu32 -lopengl32
#LLDLIBS = -lglut -lGLU -lGL -lXmu -lXext -lX11 -lm

default		: $(TARGETS)

$(TARGETS)	: $(OBJS)
	$(CC) -o $@ $? $(LDFLAGS)

glm.o: glm.h
gltx.o: gltx.h
`trackball.o:	trackball.h

