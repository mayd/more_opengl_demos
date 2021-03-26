##
##  Makefile for SGI
##

TARGET = chess

SRCS	= chess.c trackball.c glm.c gltx.c
OBJS = $(SRCS:.c=.o)

# defines
CFLAGS = -g
LDFLAGS = -lfreeglut -lglew32 -lglu32 -lopengl32

$(TARGET)	: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $? $(LDFLAGS)

.c.o	: 
	$(CC) $(CFLAGS) -c $<

# dependencies (must come AFTER inference rules)
trackball.o	: trackball.h
glm.o		: glm.h
gltx.o		: gltx.h

# cleanup rules
clean	:
	rm -f *.o *~ #* .~* 

clobber	: 
	rm -f $(TARGET) $(TARGET).exe
