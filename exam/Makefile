SRC = main.cc

CXX = g++
CXXFLAGS = -Wall -Wextra -g -std=c++14

EXE = $(SRC:.cc=.x)

OBJ = $(SRC:.CC=.o)

INC = bst.hpp

TPL = bst.tpp

#default rule
all: $(EXE)

.PHONY: all

#make the executable
$(EXE): $(OBJ) 
	$(CXX) $^ -o $@ $(CXXFLAGS)

#make the object

main.e: main.cc $(INC) $(TPL) Makefile
	$(CXX) $(CXXFLAGS) -E $< -o $@

main.o: main.cpp $(INC) $(TPL) Makefile
	$(CXX) $(CXXFLAGS) -c $< -o $@

# eliminate default suffixes
.SUFFIXES:
SUFFIXES =

# just consider our own suffixes
.SUFFIXES: .cc .tpp .o

format: $(SRC)
	@clang-format -i $^ -verbose || echo "Please install clang-format to run this command"

.PHONY: format

clean:
	rm -rf main.x  main.o

.PHONY: clean
