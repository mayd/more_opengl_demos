#!make

TARGETS = simpleci

SRCS = simpleci.c
OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall
LDFLAGS = -mconsole -luser32 -lgdi32 -lwinmm -lfreeglut -lglew32 -lglu32 -lopengl32
#LLDLIBS = -lglut -lGLU -lGL -lXmu -lXext -lX11 -lm

default		: $(TARGETS)

$(TARGETS): $(OBJS)
	$(CC) -o $@ $? $(LDFLAGS)

