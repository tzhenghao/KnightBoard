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

all: main.o
	g++ $(FLAGS) main.o -o knightboard

main.o:	Position.h KnightBoard.h
	g++ $(FLAGS) $? -c main.cpp

# make clean - remove .o files and the executable file.
# You can modify it to remove whatever.
clean:
	rm -f *.o knightboard
