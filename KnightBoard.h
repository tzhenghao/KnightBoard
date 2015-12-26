#ifndef KNIGHTBOARD_H
#define KNIGHTBOARD_H

#define BOARD_SIZE 32 // Board size is 32x32

#include "Position.h"

class KnightBoard {

	private:

		Position knightPosition;
		Position startPosition;
		Position endPosition;

		vector< vector <char> > board;

	public:

		// Constructor with no arguments.
		KnightBoard();

		// Constructor with start and stop initial positions.
		KnightBoard(const Position &start, const Position &stop);

		// EFFECTS: Initializes the knight board.
		void initializeKnightBoard();

		// EFFECTS: Returns the knight position.
		Position getKnightPosition(const Position &position);

		// REQUIRES: The position to be a valid move.
		// EFFECTS: Moves the knight to the specified position.
		Position KnightBoard::moveKnightToPosition(const Position&dest);

		// EFFECTS: Returns the terrain
		char getTerrainType();

		// EFFECTS: Prints the current board state.
		void printKnightBoard();
};

#endif
