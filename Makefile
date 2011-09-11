CC = gcc
BIN = ./bin/
EXEC = cov


DATA = voxelmodels.o
OBJS = Core.o Viewplane.o Camera.o math.o Render.o \
	Octree.o Octant.o

OBJS := $(addprefix $(BIN), $(OBJS))
DATA := $(addprefix $(BIN), $(DATA))

CFLAGS = -W -Wall -Wpadded -Wpacked -pedantic -O0 -g2
LDFLAGS = -lglut -lstdc++


all: $(BIN)$(EXEC)

$(BIN)$(EXEC): $(OBJS) $(DATA)
	$(CC) -o $@ $^ $(LDFLAGS)

$(BIN)%.o: %.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf $(OBJS)
	rm -rf $(BIN)$(EXEC)
