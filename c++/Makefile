EXE = exe.x
CXX = c++
CFLAGS = -I include -g -std=c++11 -Wall -Wextra

SRC= main.cc src/tree.cc
OBJ=$(SRC:.cc=.o)
INC = $(wildcard *.h)

all: $(EXE)

clean:
	$(info clean up)
	@rm -rf $(OBJ) $(EXE) src/*~ include/*~ *~ html latex

.PHONY: clean

%.o: %.cc
	$(CXX) -c $< -o $@ $(CFLAGS)

$(EXE): $(OBJ)
	$(CXX) $^ -o $(EXE)



main.o: include/tree.h

format: $(SRC) $(INC)
	@clang-format -i $^ 2>/dev/null || echo "Please install clang-format to run this commands"
