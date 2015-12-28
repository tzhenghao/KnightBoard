#ifndef KNIGHTBOARD_H
#define KNIGHTBOARD_H

#define BOARD_SIZE 32 // Board size is 32x32

#include <vector>
#include <iostream>

using namespace std;

// Position on the knight board.
class Position {

	public:
		int x;
		int y;

		Position() {
			x = 0;
			y = 0;
		};

		Position(int argX, int argY) {
			x = argX;
			y = argY;
		};

		bool operator==(const Position &other) const
		{
			return x == other.x && y == other.y;
		}

		Position& operator=(const Position &other)
		{
			this->x = other.x;
			this->y = other.y;
			return *this;
		}
};

class KnightBoard {

	private:

		char board[BOARD_SIZE][BOARD_SIZE];

	public:

		Position knightPosition;
		Position startPosition;
		Position endPosition;

		Position teleport[2]; // Assuming that there are only two teleportation portals.
		
		bool hasTeleport; // keep track of teleportation - needed for heuristic.

		// Constructor with no arguments.
		KnightBoard() {

		};

		KnightBoard(const char *inputFile);

		// Constructor with start and stop initial positions.
		KnightBoard(const Position &start, const Position &stop,
					const char *inputFile);

		// EFFECTS: Initializes the knight board.
		void initializeKnightBoard(const Position &start, const Position &stop,
									const char *inputFileName);

		// EFFECTS: Returns the knight position.
		Position getKnightPosition() const;

		// REQUIRES: The position to be a valid move.
		// EFFECTS: Moves the knight to the specified position.
		void moveKnightToPosition(const Position&dest);

		// EFFECTS: Returns the terrain
		char getTerrainType(const Position &dest) const;

		// EFFECTS: Prints the current board state.
		void printKnightBoard() const;
};

#endif
