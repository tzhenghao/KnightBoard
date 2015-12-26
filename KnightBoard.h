#ifndef KNIGHTBOARD_H
#define KNIGHTBOARD_H

#define BOARD_SIZE 32 // Board size is 32x32

#include <vector>

using namespace std;

// Position on the knight board.
struct Position {

	int x;
	int y;
};

class KnightBoard {

	private:

		Position knightPosition;
		Position startPosition;
		Position endPosition;

		//vector< vector <char> > board;
		char board[BOARD_SIZE][BOARD_SIZE];

	public:

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
