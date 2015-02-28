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

SOURCES 	= $(wildcard $(SRC_DIR)/**/*.cpp $(SRC_DIR)/*.cpp)
OBJECTS 	= $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
SOURCES_T 	= $(filter-out $(SRC_DIR)/main.cpp, $(SOURCES))
OBJECTS_T 	= $(SOURCES_T:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
TEST_SRC 	= $(wildcard $(TEST_DIR)/**/*.cpp $(TEST_DIR)/*.cpp)
TESTS 		= $(TEST_SRC:$(TEST_DIR)/%.cpp=$(TEST_DIR)/%.o)
TEST_EX 	= $(TEST_DIR)/main_test

# Tools
RM 			= rm -rf
VALGRIND  	= valgrind --error-exitcode=1 --track-origins=yes --leak-check=full --dsymutil=yes --suppressions=valgrind-osx.supp 

all: $(EXECUTABLE)

test: $(TEST_EX)
	./$(TEST_EX)

debug: CFLAGS += -O0 -fno-inline -g
debug: LFLAGS += -g
debug: all

valgrind: debug
	$(VALGRIND) $(EXECUTABLE)

valgrind-test: test
	$(VALGRIND) $(TEST_EX)

$(EXECUTABLE): $(OBJECTS)
	@echo "Linking..."
	@mkdir -p $(@D)
	$(CXX) $(CFLAGS) $(LFLAGS) -o $@ $+ $(LIBS)

$(TEST_EX): $(TESTS) $(OBJECTS_T)
	@echo "Linking tests..."
	@mkdir -p $(@D)
	$(CXX) $(CFLAGS) $(LFLAGS) -o $@ $+ $(LIBS)

$(OBJECTS): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "Compiling..."
	@mkdir -p $(@D)
	$(CXX) $(CFLAGS) -c -o $@ $<

clean:
	@echo "Cleaning..."
	$(RM) $(OBJ_DIR)
	$(RM) $(TEST_DIR)/*.out
	$(RM) $(TEST_DIR)/*.log
	$(RM) $(TESTS) $(TEST_EX)
	$(RM) $(DEST_DIR)

print-%:
	@echo '$*=$($*)'

.PHONY: all test debug clean print-%
