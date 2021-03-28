##!make

LDFLAGS = -mconsole -lfreeglut -lglew32 -lglu32 -lopengl32
SOURCES  = bounce.c glui.c trackball.c
TARGET = bounce
OBJECTS = $(SOURCES:.c=.o)

default		: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(LDFLAGS)

# dependencies
trackball.o	: trackball.h
$(OBJECTS)	: glui.h
