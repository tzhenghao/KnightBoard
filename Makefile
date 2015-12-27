# Name: Zheng Hao Tan
# Email: tanzhao@umich.edu

# Makefile for the knightboard program written in C++.

#Default Flags
FLAGS = -Wall -Wextra -pedantic -Wvla -std=c++11

# make release - will compile "all" with $(FLAGS) and the O3 flag
release: FLAGS += -O3
release: all

# make debug - will compile "all" with $(FLAGS) and the g flag
debug: FLAGS += -g
debug: all

CC = g++
PROGRAM = knightboard

all: KnightBoard.h KnightBoard.cpp KnightEngine.h KnightEngine.cpp main.cpp
	$(CC) $(FLAGS) $? -o $(PROGRAM)

# make clean - remove .o files and the executable file.
clean:
	rm -f *.o $(PROGRAM)

# test:
