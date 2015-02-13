# Compiler settings
CXX 	= g++
CFLAGS  = -Wall $(SYSTEMC_LIBRARY_DIRS)
LFLAGS  = $(SYSTEMC_LIBRARY_DIRS)
LIBS    = -lm

# Directories
DEST_DIR 	= bin
EXECUTABLE  = $(DEST_DIR)/main
OBJ_DIR 	= build
SRC_DIR 	= src
TEST_DIR 	= tests

SOURCES 	:= $(wildcard $(SRC_DIR)/**/*.cpp $(SRC_DIR)/*.cpp)
INCLUDES 	:= $(wildcard $(SRC_DIR)/**/*.h $(SRC_DIR)/*.h)
OBJECTS 	:= $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
TEST_SRC 	:= $(wildcard $(TEST_DIR)/**/*.cpp $(TEST_DIR)/*.cpp)
TESTS 		:= $(TEST_SRC:$(TEST_DIR)/%.cpp=$(TEST_DIR)/%.o)
TEST_EXES 	:= $(TESTS:%.o=%.tst)
rm = rm -rf

all: $(EXECUTABLE)

test: $(TEST_EXES)
	@cd $(TEST_DIR); \
	./run_tests.sh

debug: CXX += -O0 -fno-inline
debug: all

$(EXECUTABLE): $(OBJECTS)
	@echo "Linking..."
	@mkdir -p $(@D)
	$(CXX) $(CFLAGS) $(LFLAGS) -o $@ $+ $(LIBS)

$(TEST_EXES): %.tst: %.o
	@echo "Linking tests..."
	@mkdir -p $(@D)
	$(CXX) $(CFLAGS) -o $@ $<

$(OBJECTS): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "Compiling..."
	@mkdir -p $(@D)
	$(CXX) $(CFLAGS) -c -o $@ $<

clean:
	@echo "Cleaning..."
	$(rm) $(OBJ_DIR)
	$(rm) $(TEST_DIR)/*.out
	$(rm) $(TEST_DIR)/*.log
	$(rm) $(TESTS) $(TEST_EXES)
	$(rm) $(DEST_DIR)

.PHONY: all test debug clean
