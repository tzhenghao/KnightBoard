#ifndef BOARD_H
#define BOARD_H

class Board {


	private:

	public:

		virtual void initializeBoard() = 0;

		// EFFECTS: Prints the current board state.
		virtual void printBoard() const = 0;
};
