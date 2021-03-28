#!make

TARGETS = gliq

SRCS = board.c game.c gliq.c pick.c score.c trackball.c
OBJS = $(SRCS:.c=.o)

CFLAGS = -DWIN32
LDFLAGS = -mconsole -luser32 -lgdi32 -lwinmm -lfreeglut -lglew32 -lglu32 -lopengl32

default		: $(TARGETS)

$(TARGETS)	: $(OBJS)
	$(CC) -o $@ $? $(LDFLAGS)

# dependencies
trackball.o	: trackball.h
$(OBJS)	: gliq.h

