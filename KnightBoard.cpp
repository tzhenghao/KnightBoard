#include "KnightBoard.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

KnightBoard::KnightBoard(const char *inputFile) {

	// Random start and stop locations.
	Position start;
	Position stop;
	start.x = 0;
	start.y = 1;

	stop.x = 0;
	stop.y = 15;

	initializeKnightBoard(start, stop, inputFile);
}

KnightBoard::KnightBoard(const Position &start, const Position &stop,
							const char* inputFile) {

	initializeKnightBoard(start, stop, inputFile);
}

void KnightBoard::initializeKnightBoard(const Position &start, const Position &stop,
										const char *inputFileName) {

	startPosition.x = start.x;
	startPosition.y = start.y;

	endPosition.x = stop.x;
	endPosition.y = stop.y;

	// Read map from file.
	ifstream inputFile(inputFileName);

	if (inputFile.is_open()) {

		string line;
		int i = 0;

		while (getline(inputFile,line)) {

			for (int j = 0; j < BOARD_SIZE; ++j) {
				board[i][j] = line[j];
			}
			++i;
		}

		inputFile.close();
	}
	else {
		cerr << "Unable to open file";
	}

	// update start and end positions.
	board[startPosition.y][startPosition.x] = 'S';
	board[endPosition.y][endPosition.x] = 'E';
}

Position KnightBoard::getKnightPosition() const {

	return knightPosition;
}

void KnightBoard::moveKnightToPosition(const Position &dest) {

	knightPosition.x = dest.x;
	knightPosition.y = dest.y;

	// Update drawn board.
	board[knightPosition.y][knightPosition.x] = 'K';
}

char KnightBoard::getTerrainType(const Position &pos) const {

	return board[pos.y][pos.x];
}

void KnightBoard::printKnightBoard() const {

	for (int i = 0; i < BOARD_SIZE; ++i) {

		for (int j = 0; j < BOARD_SIZE; ++j) {
			cout << board[i][j];
		}
		cout << "\n";
	}
}
