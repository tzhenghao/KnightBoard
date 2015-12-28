#include "KnightBoard.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cassert>

using namespace std;

KnightBoard::KnightBoard(const char *inputFile) {

	Position start(0, 1);
	Position stop(0, 15);

	initializeKnightBoard(start, stop, inputFile);
}

KnightBoard::KnightBoard(const Position &start, const Position &stop,
							const char* inputFile) {

	initializeKnightBoard(start, stop, inputFile);
}

void KnightBoard::initializeKnightBoard(const Position &start, const Position &stop,
										const char *inputFileName) {

	hasTeleport = 0;

	startPosition.x = start.x;
	startPosition.y = start.y;

	endPosition.x = stop.x;
	endPosition.y = stop.y;

	knightPosition.x = startPosition.x;
	knightPosition.y = startPosition.y;

	// Read map from file.
	ifstream inputFile(inputFileName);

	if (inputFile.is_open()) {

		string line;
		int i = 0;
		int countTeleport = 0;
		while (getline(inputFile,line)) {

			for (int j = 0; j < BOARD_SIZE; ++j) {
				board[i][j] = line[j];

				// Save teleportation positions.
				if (line[j] == 'T') {
					hasTeleport = 1;
					teleport[countTeleport++] = Position(i, j);
				}
			}
			++i;
		}

		inputFile.close();
	}
	else {
		cerr << "Unable to open file";
	}
}

Position KnightBoard::getKnightPosition() const {

	return knightPosition;
}

void KnightBoard::moveKnightToPosition(const Position &dest) {

	// Initialize start and end positions.
	board[startPosition.y][startPosition.x] = 'S';
	board[endPosition.y][endPosition.x] = 'E';

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
