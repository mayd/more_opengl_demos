##!make

SRCS = drip.cpp main.cpp
OBJS = $(SRCS:.c=.o)

TARGETS = drip

CFLAGS = -DWIN32
LDFLAGS = -lfreeglut -lglew32 -lglu32 -lopengl32

default		: $(TARGETS)

drip	: $(OBJS)
	$(CXX) -o $@ $? $(LDFLAGS)

# dependencies
$(OBJS)	: Drip.h
