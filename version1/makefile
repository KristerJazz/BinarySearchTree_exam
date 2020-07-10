SRC = bst.cpp
CC = c++
CCFLAGS = -Wall -Wextra -std=c++14

EXE = $(SRC:.cpp=.x)

.SUFFIXES:
.SUFFIXES: .cpp .x

all: $(EXE)
.PHONY: all

%.x : %.cpp
	$(CC) $< -o $@ $(CCFLAGS)

clean:
	rm -f *.x
.PHONY: clean
