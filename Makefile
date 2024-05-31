CC := gcc
BIN := bin
EXE := executable

# Source Files
SRC := $(wildcard src/**/*.c) \
	   $(wildcard src/*.c) \
	   $(wildcard src/**/**/*.c) \
	   $(wildcard src/**/**/**/*.c)

# Objects - all generated to bin/
OBJ := $(patsubst %.c, $(BIN)/%.o, ${SRC})
LIB_OBJ := $(BIN)/lib/liblog.a \
					 $(BIN)/lib/libtgc.a \
					 $(BIN)/lib/libglfw3.a \
					 $(BIN)/lib/libcglm.a \
					 $(BIN)/lib/glad.o

LIB_HEADER_FLAGS := -Ilib/log.c/src/ \
										-Ilib/tgc/ \
										-Ilib/glfw/include/ \
										-Ilib/cglm/include/ \
										-Ilib/glad/include/

CFLAGS := -O3 -g -Wall -Wextra -Wpedantic $(LIB_HEADER_FLAGS) 
LDFLAGS := $(LIB_OBJ) -lm -lpthread 

.PHONY: all clean

# Run post-compilation
run: all
	./$(BIN)/$(EXE)

# Compile the executable
all: clean dirs libs $(EXE)

# Generate the directories
dirs:
	mkdir -p ./$(BIN) ./$(BIN)/lib ./$(BIN)/src $(dir $(OBJ)) ./data ./out

libs:
	# Compile log.c and convert to shared lib
	$(CC) -o $(BIN)/lib/log.o -c lib/log.c/src/log.c -DLOG_USE_COLOR
	ar rcs $(BIN)/lib/liblog.a $(BIN)/lib/log.o
	# Compile tgc and convert to shared lib
	$(CC) -o $(BIN)/lib/tgc.o -c lib/tgc/tgc.c
	ar rcs $(BIN)/lib/libtgc.a $(BIN)/lib/tgc.o
	# Compile CGLM
	cd lib/cglm && cmake . -DCGLM_STATIC=ON && make
	mv lib/cglm/libcglm.a $(BIN)/lib/
	# Compile GLFW
	cd lib/glfw && cmake . && make
	mv lib/glfw/src/libglfw3.a $(BIN)/lib/ 
	# Compile GLAD
	$(CC) -o $(BIN)/lib/glad.o -Ilib/glad/include -c lib/glad/src/glad.c

$(EXE): $(OBJ)
	$(CC) -o $(BIN)/$(EXE) $^ $(LDFLAGS)

$(BIN)/%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf $(BIN) $(OBJ) $(LIBOBJ)
