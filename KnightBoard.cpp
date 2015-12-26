#include "KnightBoard.h"


KnightBoard::KnightBoard() {

}

KnightBoard::KnightBoard(const Position &start, const Position &stop) {


}

void KnightBoard::initializeKnightBoard() {


}

Position KnightBoard::getKnightPosition() {

	return knightPosition;
}

Position KnightBoard::moveKnightToPosition(const Position &dest) {

	knightPosition.x = dest.x;
	knightPosition.y = dest.y;

	// Update drawn board.
	board[knightPosition.y][knightPosition.x] = 'K';
}

char KnightBoard::getTerrainType(const Position &position) {

	return board[pos.y][pos.x];
}

void KnightBoard::printKnightBoard() {

	for (int i = 0; i < BOARD_SIZE; ++i) {

		for (int j = 0; j < BOARD_SIZE; ++j) {
			cout << board[i][j];
		}
		cout << "\n";
	}
}
