#!make

TARGETS = signal

SRCS = signal.c trackball.c
OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall
#LLDLIBS = -lglut -lGLU -lGL -lXmu -lXext -lX11 -lm
LDFLAGS = -mconsole -lfreeglut -lglew32 -lglu32 -lopengl32

default		: $(TARGETS)

$(TARGETS): $(OBJS)
	$(CC) -o $@ $? $(LDFLAGS)

trackball.o:	trackball.h

