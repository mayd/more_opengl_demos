##!smake

LDFLAGS = -mconsole -lfreeglut -lglew32 -lglu32 -lopengl32
CFLAGS = -Wall
SOURCES= csg.c trackball.c
TARGET = csg

OBJECTS = $(SOURCES:.c=.o)

default		: $(TARGET)

$(TARGET)	: $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(LDFLAGS)


