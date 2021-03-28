#!make

TARGETS = meshview sine sinc

SRCS	= meshview.c sine.c sinc.c
OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -g

#LDFLAGS = -lglut -lGLU -lGL -lXext -lX11 -lXmu -lm
LDFLAGS = -mconsole -lfreeglut -lglew32 -lglu32 -lopengl32

default	: $(TARGETS)

meshview: meshview.o trackball.o
	$(CC) -o $@ $? $(LDFLAGS)

sine	: sine.o
	$(CC) -o $@ $? $(LDFLAGS)

sinc	: sinc.o
	$(CC) -o $@ $? $(LDFLAGS)

trackball.o	: trackball.h

clean	:
	rm -f $(OBJS) *~ #* .~*

clobber	: 
	rm -f $(SRCS:.c=.exe)
