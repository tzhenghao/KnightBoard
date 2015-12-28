#ifndef KNIGHTENGINE_H
#define KNIGHTENGINE_H

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>

#include "KnightBoard.h"

using namespace std;

// The eight possible moves that the knight can take from its current position.
enum Moves { LEFTUP, LEFTDOWN, RIGHTUP, RIGHTDOWN, UPLEFT, UPRIGHT, DOWNLEFT, DOWNRIGHT };

class KnightEngine {

	private:

		vector <Position> path; // Stores the path that the program will take

		int countPath = 0;

		KnightBoard knightBoard;

		// REQUIRES: A map of nodes which they came from and the current node.
		// EFFECTS: Builds the current order of path from start to end positions.
		void buildPath(unordered_map<int, Position> &fromNodes,
						Position &currentNode);

		// REQUIRES: The two points.
		// EFFECTS: Calculates the heuristic cost via two points.
		//			Returns 0 if teleportation is enabled.
		//			Returns abs distance if teleportation is disabled.
		int calculateHeuristicCost(const Position &from, const Position &to);

		// REQUIRES:
		// EFFECTS: Generates neighbors for the current position.
		void generateNeighbor(Position &neighbor, const Position &pos, Moves i);

		// REQUIRES: The move to be valid.
		// EFFECTS: Returns the total travel cost to move to neighbor.
		int calculateTravelCost(Moves i, const Position &neighbor);

		// REQUIRES: The current state of the knight board and xy values of the board to check.
		// EFFECTS: Returns true if the terrain is valid.
		bool isTerrainValid(int x, int y);

		// REQUIRES: The position that we are moving into.
		// EFFECTS: Calculates the terrain cost for entering the specified position.
		int calculateTerrainCost(int x, int y);

		// REQUIRES: The current state of the knight board and a sequence of moves.
		// EFFECTS: Returns true if the sequence contains all valid knight moves.
		bool isMoveValid(const Position &knightPosition, const Position& position);

	public:

		KnightEngine(const Position &start, const Position &stop, const char *inputFile);

		// EFFECTS: Finds the best path from the given start and end points.
		//			Returns a non-negative number for the cost of the path,
		//			Returns -1 if it fails to find a path.
		int findBestPath(const Position &start, Position &stop);

		// EFFECTS: Prints the path.
		void printPath();

		void task1();

		void knightTour();
};

#endif
