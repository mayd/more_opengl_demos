##!make

LDFLAGS = -lfreeglut -lglew32 -lglu32 -lopengl32
TARGETS = distort ripple_precalc

SRCS = distort.c ripple.c ripple_table.c rubber.c texture.c
OBJS = $(SRCS:.c=.o)

default: $(TARGETS)

distort: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)

ripple_precalc: ripple_precalc.o
	$(CC) -o $@ ripple_precalc.o $(LDFLAGS)

ripple_table.c: ripple_precalc
	./ripple_precalc > ripple_table.c

# dependencies
texture.o: texture.h
ripple.o: ripple.h
rubber.o: rubber.h
$(OBJS): defs.h
