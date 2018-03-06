EXE = exe.x
CXX = g++
CFLAGS = -I include/ -g -std=c++11 -Wall -Wextra -DSEED=0 -O3

SRC= main.cc

all: $(EXE)

gnu:
	$(CXX) $(SRC) $(CFLAGS) -o $(EXE) -DGNU

clean:
	$(info clean up)
	@rm -rf $(OBJ) $(EXE) src/*~ include/*~ *~ html latex

.PHONY: clean

$(EXE):
	$(CXX) $(SRC) $(CFLAGS) -o $(EXE)


format: $(SRC) $(INC)
	@clang-format -i $^ 2>/dev/null || echo "Please install clang-format to run this commands"

documentation: doc/doxy.in
	doxygen $^
