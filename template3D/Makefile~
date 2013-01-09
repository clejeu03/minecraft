CC = g++
CFLAGS = -Wall -ansi -pedantic -I include
LDFLAGS = -lSDL -lGL

SRC_PATH = src
BIN_PATH = bin

EXEC = Imac2GL3

SRC_FILES = $(shell find $(SRC_PATH) -type f -name '*.cpp')
OBJ_FILES = $(patsubst $(SRC_PATH)/%.cpp, $(SRC_PATH)/%.o, $(SRC_FILES))

all: $(BIN_PATH)/$(EXEC)

$(BIN_PATH)/$(EXEC): $(OBJ_FILES) $(SRC_PATH)/glew-1.9/glew.o
	$(CC) -o $@ $^ $(LDFLAGS)

$(SRC_PATH)/glew-1.9/glew.o: $(SRC_PATH)/glew-1.9/glew.c
	$(CC) -c -o $@ $(CFLAGS) $^ 

$(SRC_PATH)/%.o: $(SRC_PATH)/%.cpp
	$(CC) -c -o $@ $(CFLAGS) $^ 

clean:
	rm $(OBJ_FILES) $(SRC_PATH)/glew-1.9/glew.o

cleanall:
	rm $(BIN_PATH)/$(EXEC) $(OBJ_FILES) $(SRC_PATH)/glew-1.9/glew.o
