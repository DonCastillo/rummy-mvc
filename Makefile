CXX=g++
CXXFLAGS= -std=c++11 -g -fprofile-arcs -ftest-coverage

LINKFLAGS= -lgtest

SRC_DIR = src
SRCS = $(SRC_DIR)/Card.cpp $(SRC_DIR)/Deck.cpp \
	$(SRC_DIR)/Game.cpp $(SRC_DIR)/GameUI.cpp $(SRC_DIR)/GoFish.cpp \
	$(SRC_DIR)/GoFishUI.cpp $(SRC_DIR)/Player.cpp $(SRC_DIR)/Rummy.cpp \

TEST_DIR = test

GMOCK = -lgmock -lpthread

SRC_INCLUDE = include
TEST_INCLUDE = test
INCLUDE = -I ${SRC_INCLUDE} -I ${TEST_INCLUDE}

GCOV = gcov
LCOV = lcov
COVERAGE_RESULTS = results.coverage
COVERAGE_DIR = coverage

MEMCHECK_RESULTS = ValgrindOut.xml

STATIC_ANALYSIS = cppcheck

STYLE_CHECK = cpplint.py

STATIC_RESULTS = CppCheckResults.xml

BROWSER = firefox

PROGRAM = cardGame
PROGRAM_TEST = testGame

.PHONY: all
all: $(PROGRAM) $(PROGRAM_TEST) memcheck-test coverage docs static

# default rule for compiling .cc to .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf *~ $(SRC)/*.o $(TEST_SRC)/*.o *.gcov *.gcda *.gcno $(COVERAGE_RESULTS) $(PROGRAM) $(PROGRAM_TEST) $(MEMCHECK_RESULTS) $(COVERAGE_DIR) $(STATIC_RESULTS)


.PHONY: clean-all
clean-all: clean
	rm -rf $(PROGRAM) $(PROGRAM_TEST)

$(PROGRAM):
	$(CXX) $(CXXFLAGS) -o $(PROGRAM) -I $(SRC_INCLUDE) $(SRC_DIR)/*.cpp $(LINKFLAGS)

$(PROGRAM_TEST):
	$(CXX) $(CXXFLAGS) -o $(PROGRAM_TEST) $(INCLUDE) $(TEST_DIR)/*.cpp $(SRCS) $(LINKFLAGS) $(GMOCK)
	$(PROGRAM_TEST)

.PHONY: tests
tests: $(PROGRAM_TEST)

memcheck-game: $(PROGRAM)
	valgrind --tool=memcheck --leak-check=yes --xml=yes --xml-file=$(MEMCHECK_RESULTS) $(PROGRAM)


memcheck-test: $(PROGRAM_TEST)
	valgrind --tool=memcheck --leak-check=yes $(PROGRAM_TEST)

coverage: $(PROGRAM_TEST)
	./$(PROGRAM_TEST)
	$(LCOV) --capture --gcov-tool $(GCOV) --directory . --output-file $(COVERAGE_RESULTS) --rc lcov_branch_coverage=1
	$(LCOV) --extract $(COVERAGE_RESULTS) "*/src/*" -o $(COVERAGE_RESULTS) --rc lcov_branch_coverage=1
	genhtml $(COVERAGE_RESULTS) --output-directory $(COVERAGE_DIR) --rc lcov_branch_coverage=1
	#rm -f *.gc*
	rm -f *.gcda *.gcno
	$(BROWSER) $(COVERAGE_DIR)/index.html

static: ${SRC_DIR}
	cppcheck --verbose --enable=all --xml ${SRC_DIR} ${TEST_DIR} ${INCLUDE} --suppress=missingInclude

style: ${TEST_DIR} ${SRC_INCLUDE} ${SRC_DIR}
	${STYLE_CHECK} $(SRC_INCLUDE)/* ${TEST_DIR}/* ${SRC_DIR}/*

docs: ${SRC_INCLUDE}
	doxygen
