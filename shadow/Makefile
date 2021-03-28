#!make

TARGETS = shadow

SRCS	= shadow.c glm.c gltx.c trackball.c
OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall
LDFLAGS = -mconsole -lfreeglut -lglew32 -lglu32 -lopengl32
#LIBS	= -L$(GLUTHOME) -lglut -lGLU -lGL -lXext -lX11 -lXmu -lm

default: $(TARGETS)

$(TARGETS): $(OBJS)
	$(CC) -o $@ $? $(LDFLAGS)

trackball.o: trackball.h
glm.o: glm.h
gltx.o: gltx.h

# cleanup rules
clean	:
	rm -f *.o *~ #* .~*

clobber	: 
	rm -f $(EXES)
