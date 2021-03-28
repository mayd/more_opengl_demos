##!nmake

CFLAGS	= -DWIN32
LDFLAGS = -mconsole -luser32 -lgdi32 -lfreeglut -lglew32 -lglu32 -lopengl32

SOURCES = cube.c
OBJECTS = $(SOURCES:.c=.o)
TARGET	= cube

default	: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(LDFLAGS)

clean	:
	@rm -f $(OBJECTS)

clobber	: 
	@rm -f $(TARGET).exe

