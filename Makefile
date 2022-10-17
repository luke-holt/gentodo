# Directories
INC_DIR = include
LIB_DIR = $(INC_DIRS)
BLD_DIR = build
OBJ_DIR = $(BLD_DIR)/obj
BIN_DIR = $(BLD_DIR)/bin
SRC_DIR = src

# Files
TARGET = $(BIN_DIR)/gentodo

SOURCES = \
	ignore_list.cpp \
	todo_list.cpp \
	scan.cpp \
	gentodo.cpp

OBJECTS = $(addprefix $(OBJ_DIR)/,$(SOURCES:.cpp=.o))

# Toolchain
CC = clang++

# Flags
WFLAGS = -Wall -Wextra -Wunused -Wcast-align \
		 -Wpointer-arith -Wmissing-prototypes \
		 -Wno-missing-braces -Wmissing-declarations

# Common flags. Optimize for speed, enable debug options
COM_FLAGS = -Os -g -std=c++1z

# Compiler and linker flags
CFLAGS = $(COM_FLAGS) $(WFLAGS) $(addprefix -I,$(INC_DIR))
LDFlAGS = $(COM_FLAGS) $(addprefix -L,$(LIB_DIR))

# Compile
$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	@mkdir -p $(dir $@)
	@echo "Compiling $@..."
	@$(CC) $(CFLAGS) -c $^ -o $@
	@echo ""

# Link
$(TARGET): $(OBJECTS)
	@mkdir -p $(dir $@)
	@echo "Linking..."
	@$(CC) $(LDFLAGS) -o $@ $^
	@echo ""

# Phony targets
.PHONY: all clean run test

# default
all: $(TARGET)

clean:
	@rm -r $(BLD_DIR)

run: $(TARGET)
	@./build/bin/gentodo

include test/test.mk
