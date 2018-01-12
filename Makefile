CXX=g++
CXXFLAGS= -std=c++0x -g -fprofile-arcs -ftest-coverage

LINKFLAGS= -lgtest

SRC_DIR = src
SRCS = ${SRC_DIR}/Card.cpp ${SRC_DIR}/Deck.cpp ${SRC_DIR}/GoFish.cpp ${SRC_DIR}/Player.cpp


TEST_DIR = test

OBJ_DIR = obj
OBJS = $(SRC)/Circle.o $(SRC)/Cone.o $(SRC)/Cuboid.o $(SRC)/Cylinder.o $(SRC)/Quadrilateral.o $(SRC)/Sphere.o  $(SRC)/Triangle.o
ALL_OBJS = $(OBJS)
TEST_OBJS = $(TEST_DIR)/TestCircle.o $(TEST_DIR)/TestCone.o $(TEST_DIR)/TestCuboid.o $(TEST_DIR)/TestCylinder.o $(TEST_DIR)/TestQuad.o $(TEST_DIR)/TestSphere.o  $(TEST_DIR)/TestTriangle.o $(TEST_DIR)/main.o

INCLUDE = -I include -I test

GCOV = gcov
LCOV = lcov
COVERAGE_RESULTS = result.coverage
COVERAGE_DIR = coverage

MEMCHECK_RESULTS = results.memcheck

PROGRAM = cardGame
PROGRAM_TEST = gameTest

.PHONY: all
all: $(PROGRAM_TEST)

# default rule for compiling .cc to .o
%.o: %.cpp
# $(CC) $(CFLAGS) -c $< -o $(patsubst %.cpp,%.o,$<) ${INCLUDE}
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf *~ $(SRC)/*.o $(TEST_SRC)/*.o *.gcov *.gcda *.gcno $(COVERAGE_RESULTS) $(PROGRAM_TEST) $(MEMCHECK_RESULTS) ${COVERAGE_DIR}


.PHONY: clean-all
clean-all: clean
	rm -rf $(PROGRAM) $(PROGRAM_TEST)


$(PROGRAM_TEST):
	#$(CC) $(CFLAGS) -o $@ $^ -lgtest $(INCLUDE)
	$(CXX) $(CXXFLAGS) -o $(PROGRAM_TEST) ${INCLUDE} $(TEST_DIR)/*.cpp ${SRCS} $(LINKFLAGS)

test: $(PROGRAM_TEST)
	$(PROGRAM_TEST)

memcheck: $(PROGRAM_TEST)
	rm -f results
	valgrind --leak-check=yes $(PROGRAM_TEST) &> results
	more results

coverage: test
	$(LCOV) --capture --gcov-tool ${GCOV} --directory . --output-file $(COVERAGE_RESULTS)
	$(LCOV) --extract ${COVERAGE_RESULTS} "*/src/*" -o ${COVERAGE_RESULTS}
	genhtml $(COVERAGE_RESULTS) --output-directory ${COVERAGE_DIR}
	rm -f *.gc*

lib:
	ar rcs libshapes.a $(OBJS)

