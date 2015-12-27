#ifndef KNIGHTENGINE_H
#define KNIGHTENGINE_H

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>

#include "KnightBoard.h"

using namespace std;

class KnightEngine {

	private:

		vector <Position> path;

		KnightBoard knightBoard;

		// REQUIRES:
		// EFFECTS: Builds the current order of path from start to end positions.
		void buildPath(unordered_map<int, Position> &fromNodes,
						Position &currentNode);

		// REQUIRES:
		// EFFECTS: Calculates the heuristic cost via two points.
		int calculateHeuristicCost(const Position &from, const Position &to);

		int toHash(const Position &pos) const {
			return pos.y * BOARD_SIZE + pos.x;
		};

	public:

		KnightEngine(const Position &start, const Position &stop, const char *inputFile);

		// REQUIRES: The current state of the knight board and a sequence of moves.
		// EFFECTS: Returns true if the sequence contains all valid knight moves.
		bool isMoveValid(const Position& position);

		// REQUIRES: The current state of the knight board and xy values of the board to check.
		// EFFECTS: Returns true if the terrain is valid.
		bool isTerrainValid(int x, int y);

		// REQUIRES: The position that we are moving into.
		// EFFECTS: Calculates the terrain cost for entering the specified position.
		int calculateTerrainCost(const Position &pos);

		// EFFECTS: Finds the best path from the given start and end points.
		//			Returns a non-negative number for the cost of the path,
		//			Returns -1 if it fails to find a path.
		int findBestPath();

		// EFFECTS: Prints the path.
		void printPath();

		void task1();
};

#endif
