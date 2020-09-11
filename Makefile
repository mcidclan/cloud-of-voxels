CC = g++
BIN = ./bin/
EXEC = cov

DATA = voxeldisplays.o voxelmodels.o
OBJS = Options.o Core.o Camera.o math.o Render.o \
	Octree.o Octant.o main.o $(DATA)

OBJS := $(addprefix $(BIN), $(OBJS))
DATA := $(addprefix $(BIN), $(DATA))

CFLAGS = -W -Wall -Wpadded -Wpacked -O0 -g2 -std=c++11 -m32 -pedantic
LDFLAGS = $(CFLAGS) -lglut -lGL -lGLU -lm -lstdc++

all: $(BIN)$(EXEC)

$(BIN)$(EXEC): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

$(BIN)%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)
	rm -rf $(BIN)$(EXEC)
