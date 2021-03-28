#!make

TARGETS = sgiflag

SRCS = sgiflag.c
OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall
LDFLAGS = -mconsole -lfreeglut -lglew32 -lglu32 -lopengl32
#LLDLIBS = -lglut -lGLU -lGL -lXmu -lXext -lX11 -lm

default		: $(TARGETS)

$(TARGETS):	$(OBJS)
	$(CC) -o $@ $? $(LDFLAGS)

sgiflag.o:	sgiflag.h logopoints.h
