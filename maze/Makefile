##!make

TARGETS	= maze

SRCS = maze.c
OBJS = $(SRCS:.c=.o)

CFLAGS	= -DWIN32 -Wall -g
LDFLAGS = -mconsole -luser32 -lgdi32 -lWinmm -lfreeglut -lglew32 -lglu32 -lopengl32

default	: $(TARGETS)

$(TARGETS): $(OBJS)
	$(CC) -o $@ $? $(LDFLAGS)

clean	:
	@rm -f $(OBJS)

clobber	: 
	@rm -f maze.exe
