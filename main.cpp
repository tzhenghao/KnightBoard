// Zheng Hao Tan
// Date: December 25, 2015

#include <iostream>
#include <vector>

#include "KnightBoard.h"

using namespace std;

// Prototypes.
bool areMovesValid (const KnightBoard &knightBoard, const vector<Position>& moves);

bool areTerrainsValid(const KnightBoard &knightBoard, const Position &pos);

int calculateTerrainCost(const KnightBoard &knightBoard, const Position &pos);

int findBestPath(KnightBoard &knightBoard, const vector <Position> &moves);

void printPath(const vector <Position> &moves);

int main(int argc, char *argv[]) {

	if (argc != 2) {
		cerr << "Invalid file arguments\n";
		return -1;
	}

	KnightBoard knightBoard(argv[1]); // File argument.

	vector <Position> bestPathSoFar;

	knightBoard.printKnightBoard();

	return 0;
}

// REQUIRES: A sequence of moves
// EFFECTS: Returns true if the sequence contains all valid knight moves.
bool areMovesValid (const KnightBoard &knightBoard, const vector<Position>& moves) {

	Position knightPosition = knightBoard.getKnightPosition();

	for (auto &position: moves) {

		// Check for outside the allocated board.
		if (position.x < 0 || position.y < 0
			|| position.x > BOARD_SIZE - 1
			|| position.y > BOARD_SIZE - 1) {
			return false;
		}
		// Check for top and bottom
		else if (knightPosition.x - position.x == 2) {

			if (knightPosition.y - position.y == 1) {

			}
			else if (position.y - knightPosition.y == 1) {

			}
			else {
				return false;
			}
		}
		else if (position.x - knightPosition.x == 2) {

			if (knightPosition.y - position.y == 1) {

			}
			else if (position.y - knightPosition.y == 1) {

			}
			else {
				return false;
			}
		}
		else if (knightPosition.y - position.y == 2) {

			if (knightPosition.x - position.x == 1) {

			}
			else if (position.x - knightPosition.x == 1) {

			}
			else {
				return false;
			}
		}
		else if (position.y - knightPosition.y == 2) {

			if (knightPosition.x - position.x == 1) {

			}
			else if (position.x - knightPosition.x == 1) {

			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}

	return true;
}

// EFFECTS: Returns true if the terrain is valid.
bool areTerrainsValid(const KnightBoard &knightBoard, const Position &dest) {

	char terrain = knightBoard.getTerrainType(dest);

	return terrain != 'R' && terrain != 'B';
}

// REQUIRES: The position that we are moving into.
// EFFECTS: Calculates the terrain cost for entering the specified position.
int calculateTerrainCost(const KnightBoard &knightBoard, const Position &pos) {

	char terrain = knightBoard.getTerrainType(pos);

	if (terrain == 'W') {
		return 2;
	}
	else if (terrain == 'R') {
		return -1; // error
	}
	else if (terrain == 'B') {
		return -1; // error
	}
	else if (terrain == 'T') {
		return 0;
	}
	else if (terrain == 'L') {
		return 5;
	}
	else if (terrain == '.') {
		return 1;
	}
	else {
		return -1; // error
	}
}

// EFFECTS: Finds the best path from the given start and end points.
int findBestPath(KnightBoard &knightBoard, const vector <Position> &moves) {

	return -1;
}

// EFFECTS: Prints the path.
void printPath(const vector <Position> &moves) {

	for (auto &pos: moves) {
		cout << "(" << pos.x << "," << pos.y << "),";
	}
	cout << "\n";
}
