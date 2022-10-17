
# Directories
TEST_BIN_DIR = $(BIN_DIR)/test
TEST_OBJ_DIR = $(OBJ_DIR)/test

TEST_LDFLAGS = $(LDFLAGS) \
	-lgtest \
	-lgtest_main \
	-pthread

# Files
TEST_SRCS = \
	todo_list_test.cpp

TEST_NAMES = $(TEST_SRCS:.cpp=)

TEST_TARGETS = $(addprefix $(TEST_BIN_DIR)/,$(TEST_NAMES))

TEST_OBJECTS = $(addprefix $(TEST_OBJ_DIR)/,$(addsuffix .o, $(TEST_NAMES)))
TEST_OBJECTS += $(filter-out $(OBJ_DIR)/gentodo.o, $(OBJECTS))

# Compile
$(TEST_OBJ_DIR)%.o: test/%.cpp
	@mkdir -p $(dir $@)
	@echo "Compiling $@..."
	@$(CC) $(CFLAGS) -c $^ -o $@
	@echo ""

# Link
$(TEST_TARGETS): $(TEST_OBJECTS)
	@mkdir -p $(dir $@)
	@echo "Linking..."
	@$(CC) -o $@ $^ $(TEST_LDFLAGS)
	@echo ""

test: all $(TEST_TARGETS)
	@./build/bin/test/todo_list_test

