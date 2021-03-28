##!make

TARGETS = lorenz

SRCS = lorenz.c
OBJS = $(SRCS:.c=.o)

LDFLAGS = -mconsole -lfreeglut -lglew32 -lglu32 -lopengl32
CFLAGS = -Wall

default		: $(TARGETS)

$(TARGETS): $(OBJS)
	$(CC) -o $@ $? $(LDFLAGS)
