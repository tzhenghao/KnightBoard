#include "KnightEngine.h"
#include <cassert>
#include <limits.h>
#include <algorithm>

using namespace std;

// Estimated total cost from start to goal through y.
unordered_map<int, int> fScore;

// REQUIRES: A given position.
// EFFECTS: Returns a hash value for the position (Used by unordered_map).
int toHash(const Position &pos) {
	return pos.y * BOARD_SIZE + pos.x;
}

// Comparator for the priority queue when evaluating travel cost.
struct PriorityQueueComparator {

	bool operator()(const Position& lhs, const Position&rhs) const
	{
		return fScore[toHash(lhs)] < fScore[toHash(rhs)];
	}
} comparator;

KnightEngine::KnightEngine(const Position &start, const Position &stop,
							const char *inputFile) {

	knightBoard.initializeKnightBoard(start, stop, inputFile);

	assert(path.empty());
}

bool KnightEngine::isMoveValid(const Position &knightPosition, const Position& position) {

	// Check for outside the allocated board.
	if (position.x < 0 || position.y < 0
		|| position.x > BOARD_SIZE - 1
		|| position.y > BOARD_SIZE - 1) {
		return false;
	}
	// Check if destination's terrain is valid.
	else if (!isTerrainValid(position.x, position.y)) {
		return false;
	}
	// Check for top and bottom
	else if (knightPosition.x - position.x == 2) {

		if (knightPosition.y - position.y == 1) {

			bool invalid = false;
			for (int i = 0; i < 3; ++i) {
				if (!isTerrainValid(position.x + i, position.y)) {
					invalid = true;
					break;
				}
			}

			if (invalid) {
				invalid = false;
				for (int i = 0; i < 2; ++i) {
					if (!isTerrainValid(position.x + i, position.y + 1)) {
						invalid = true;
						break;
					}
				}
			}

			return !invalid;
		}
		else if (position.y - knightPosition.y == 1) {

			bool invalid = false;
			for (int i = 0; i < 3; ++i) {
				if (!isTerrainValid(position.x + i, position.y)) {
					invalid = true;
					break;
				}
			}

			if (invalid) {
				invalid = false;
				for (int i = 0; i < 2; ++i) {
					if (!isTerrainValid(position.x + i, position.y - 1)) {
						invalid = true;
						break;
					}
				}
			}

			return !invalid;
		}
		else {
			return false;
		}
	}
	else if (position.x - knightPosition.x == 2) {

		if (knightPosition.y - position.y == 1) {

			bool invalid = false;
			for (int i = 0; i < 3; ++i) {
				if (!isTerrainValid(position.x - i, position.y)) {
					invalid = true;
					break;
				}
			}

			if (invalid) {
				invalid = false;
				for (int i = 0; i < 2; ++i) {
					if (!isTerrainValid(position.x - i, position.y + 1)) {
						invalid = true;
						break;
					}
				}
			}

			return !invalid;

		}
		else if (position.y - knightPosition.y == 1) {
			bool invalid = false;
			for (int i = 0; i < 3; ++i) {
				if (!isTerrainValid(position.x - i, position.y)) {
					invalid = true;
					break;
				}
			}

			if (invalid) {
				invalid = false;
				for (int i = 0; i < 2; ++i) {
					if (!isTerrainValid(position.x - i, position.y - 1)) {
						invalid = true;
						break;
					}
				}
			}

			return !invalid;
		}
		else {
			return false;
		}
	}
	else if (knightPosition.y - position.y == 2) {

		if (knightPosition.x - position.x == 1) {

			bool invalid = false;
			for (int i = 0; i < 3; ++i) {
				if (!isTerrainValid(position.x, position.y + i)) {
					invalid = true;
					break;
				}
			}

			if (invalid) {
				invalid = false;
				for (int i = 0; i < 2; ++i) {
					if (!isTerrainValid(position.x + 1, position.y + i)) {
						invalid = true;
						break;
					}
				}
			}

			return !invalid;
		}
		else if (position.x - knightPosition.x == 1) {

			bool invalid = false;
			for (int i = 0; i < 3; ++i) {
				if (!isTerrainValid(position.x, position.y + i)) {
					return false;
				}
			}

			if (invalid) {
				invalid = false;
				for (int i = 0; i < 2; ++i) {
					if (!isTerrainValid(position.x - 1, position.y + i)) {
						invalid = true;
						break;
					}
				}
			}

			return !invalid;
		}
		else {
			return false;
		}
	}
	else if (position.y - knightPosition.y == 2) {

		if (knightPosition.x - position.x == 1) {

			bool invalid = false;
			for (int i = 0; i < 3; ++i) {
				if (!isTerrainValid(position.x, position.y - i)) {
					return false;
				}
			}

			if (invalid) {
				invalid = false;
				for (int i = 0; i < 2; ++i) {
					if (!isTerrainValid(position.x + 1, position.y - i)) {
						invalid = true;
						break;
					}
				}
			}

			return !invalid;
		}
		else if (position.x - knightPosition.x == 1) {

			bool invalid = false;
			for (int i = 0; i < 3; ++i) {
				if (!isTerrainValid(position.x, position.y - i)) {
					invalid = true;
					break;
				}
			}

			if (invalid) {
				invalid = false;
				for (int i = 0; i < 2; ++i) {
					if (!isTerrainValid(position.x - 1, position.y - i)) {
						invalid = true;
						break;
					}
				}
			}

			return !invalid;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}

	return true;
}

bool KnightEngine::isTerrainValid(int x, int y) {

	Position dest;
	dest.x = x;
	dest.y = y;

	char terrain = knightBoard.getTerrainType(dest);

	return terrain != 'R' && terrain != 'B';
}

int KnightEngine::calculateTerrainCost(int x, int y) {

	Position pos(x, y);
	char terrain = knightBoard.getTerrainType(pos);

	if (terrain == 'W') {
		return 2;
	}
	else if (terrain == 'R' || terrain == 'B') {
		return 999;
	}
	else if (terrain == 'T') {
		return 0;
	}
	else if (terrain == 'L') {
		return 5;
	}
	else if (terrain == '.' || terrain == 'E' || terrain == 'S') {
		return 1;
	}
	else {
		cerr << "Error: CalculateTerrainCost evaluated to unknown terrain\n";
		return 999;
	}
}

int KnightEngine::findBestPath(const Position &start, Position &stop) {

	// Set of explored nodes.
	unordered_set<int> closedSet;

	vector<Position> openSet;
	unordered_set<int> isInOpenSet; // Mapping for whether the node is in the open set.

	openSet.push_back(start);
	isInOpenSet.insert(toHash(start));

	unordered_map<int, Position> fromNodes;

	// Total cost from starting position along best known path.
	unordered_map<int, int> gScore;
	gScore[toHash(start)] = 0; // Cost from start along best known path.

	fScore[toHash(start)] = calculateHeuristicCost(start, stop);

	while (!openSet.empty()) {

		Position currentPos = openSet[0];

		if (currentPos == stop) {

			buildPath(fromNodes, stop);

			// Move knight to that position and print the knight board.
			knightBoard.moveKnightToPosition(path[0]);
			knightBoard.printKnightBoard();

            return fScore[toHash(currentPos)];
		}

        openSet.erase(openSet.begin());
		isInOpenSet.erase(toHash(currentPos));

		closedSet.insert(toHash(currentPos));

		// Handle teleportation.
		if(knightBoard.getTerrainType(currentPos) == 'T') {

			if (currentPos == knightBoard.teleport[0]) {
				currentPos = knightBoard.teleport[1];
			}
			else {
				currentPos = knightBoard.teleport[0];
			}
		}

		Position neighbor;

		for (int i = 0 ; i < 8; ++i) {

			generateNeighbor(neighbor, currentPos, (Moves)i);
			if (isMoveValid(currentPos, neighbor)) {

				if (closedSet.find(toHash(neighbor)) != closedSet.end()) {
					continue;
				}

				int currentGScore = gScore[toHash(currentPos)]
									+ calculateTravelCost((Moves)i, neighbor);

				int temp;
				if (gScore.find(toHash(neighbor)) == gScore.end()) {
					temp = INT_MAX;
				}
				else {
					temp = gScore[toHash(neighbor)];
				}

				// Add to open set if it isn't there already.
				if (isInOpenSet.find(toHash(neighbor)) == isInOpenSet.end()) {
					openSet.push_back(neighbor);
					isInOpenSet.insert(toHash(currentPos));
				}
				// Don't bother looking if the cost is more than what we already have.
				else if (currentGScore >= temp) {
					continue;
				}

				// Best path so far.
				fromNodes[toHash(neighbor)] = currentPos;
				gScore[toHash(neighbor)] = currentGScore;
				fScore[toHash(neighbor)] = gScore[toHash(neighbor)]
									+ calculateHeuristicCost(neighbor, stop);
			}
		}

		sort(openSet.begin(), openSet.end(), comparator);
	}
	return -1;
}

int KnightEngine::calculateTravelCost(Moves i, const Position&neighbor) {

	int totalCost = 0;
	int totalCost1 = 0;
	int totalCost2 = 0;

	if (i == LEFTUP || i == LEFTDOWN) {

		for (int i = 0; i < 3; ++i) {
			totalCost1 += calculateTerrainCost(neighbor.x + i, neighbor.y);
		}

		int tempY;
		if (i == LEFTUP) {
			tempY = neighbor.y + 1;
		}
		else {
			tempY = neighbor.y - 1;
		}

		totalCost2 += calculateTerrainCost(neighbor.x, neighbor.y);

		for (int i = 0; i < 2; ++i) {
			totalCost2 += calculateTerrainCost(neighbor.x + i, tempY);
		}

		totalCost = min(totalCost1, totalCost2);
	}
	else if (i == RIGHTUP || i == RIGHTDOWN) {

		for (int i = 0; i < 3; ++i) {
			totalCost1 += calculateTerrainCost(neighbor.x - i, neighbor.y);
		}

		int tempY;
		if (i == RIGHTUP) {
			tempY = neighbor.y + 1;
		}
		else {
			tempY = neighbor.y - 1;
		}

		totalCost2 += calculateTerrainCost(neighbor.x, neighbor.y);

		for (int i = 0; i < 2; ++i) {
			totalCost2 += calculateTerrainCost(neighbor.x - i, tempY);
		}

		totalCost = min(totalCost1, totalCost2);
	}
	else if (i == UPLEFT || i == UPRIGHT) {

		for (int i = 0; i < 3; ++i) {
			totalCost1 += calculateTerrainCost(neighbor.x, neighbor.y + i);
		}

		int tempX;
		if (i == UPLEFT) {
			tempX = neighbor.x + 1;
		}
		else {
			tempX = neighbor.x - 1;
		}

		totalCost2 += calculateTerrainCost(neighbor.x, neighbor.y);

		for (int i = 0; i < 2; ++i) {
			totalCost2 += calculateTerrainCost(tempX, neighbor.y + i);
		}

		totalCost = min(totalCost1, totalCost2);
	}
	else if (i == DOWNLEFT || i == DOWNRIGHT) {

		for (int i = 0; i < 3; ++i) {
			totalCost1 += calculateTerrainCost(neighbor.x, neighbor.y - i);
		}

		int tempX;
		if (i == DOWNLEFT) {
			tempX = neighbor.x + 1;
		}
		else {
			tempX = neighbor.x - 1;
		}

		totalCost2 += calculateTerrainCost(neighbor.x, neighbor.y);

		for (int i = 0; i < 2; ++i) {
			totalCost2 += calculateTerrainCost(tempX, neighbor.y - i);
		}

		totalCost = min(totalCost1, totalCost2);
	}
	else {
		cerr << "Error: Cannot find correct knight move!\n";
		return -1;
	}

	return totalCost;
}

int KnightEngine::calculateHeuristicCost(const Position &from, const Position &to) {

	// Distance between the two positions have to be at least diffX + diffY long.
	return knightBoard.hasTeleport? 0 :(abs(to.x - from.x) + abs(to.y - from.y));
}

void KnightEngine::generateNeighbor(Position &neighbor, const Position &pos, Moves i) {

	if (i == LEFTUP) {
		neighbor.x = pos.x - 2;
		neighbor.y = pos.y - 1;
	}
	else if (i == LEFTDOWN) {
		neighbor.x = pos.x - 2;
		neighbor.y = pos.y + 1;
	}
	else if (i == RIGHTUP) {
		neighbor.x = pos.x + 2;
		neighbor.y = pos.y - 1;
	}
	else if (i == RIGHTDOWN) {
		neighbor.x = pos.x + 2;
		neighbor.y = pos.y + 1;
	}
	else if (i == UPLEFT) {
		neighbor.x = pos.x - 1;
		neighbor.y = pos.y - 2;
	}
	else if (i == UPRIGHT) {
		neighbor.x = pos.x + 1;
		neighbor.y = pos.y - 2;
	}
	else if (i == DOWNLEFT) {
		neighbor.x = pos.x - 1;
		neighbor.y = pos.y + 2;
	}
	else if (i == DOWNRIGHT) {
		neighbor.x = pos.x + 1;
		neighbor.y = pos.y + 2;
	}
	else {
		cerr << "Error: cannot generate neighbor in generateNeighbor()\n";
	}
}

void KnightEngine::buildPath(unordered_map<int, Position> &fromNodes,
								Position &currentNode) {

	if (!path.empty()) {
		cerr << "Error: path is filled!\n";
		return;
	}

	path.push_back(currentNode);

	while (fromNodes.find(toHash(currentNode)) != fromNodes.end()) {

		currentNode = fromNodes[toHash(currentNode)];
		path.push_back(currentNode);
	}
}

void KnightEngine::printPath() {

	for (int i = path.size() - 1; i >= 0; --i) {
		cout << "(" << path[i].x << "," << path[i].y << ") ";
	}
	cout << "\n";
}

void KnightEngine::task1() {

	// Populate moves.
	path.push_back(Position(2, 2));
	//path.push_back(Position(2, 1));

	bool movesAreInvalid = false;

	Position knightPosition = knightBoard.getKnightPosition();
	if (!path.empty()) {

		for (auto &position: path) {

			if (!isMoveValid(knightPosition, position)) {
				cerr << "Move is invalid!\n";
				movesAreInvalid = true;
				break;
			}
		}

		if (!movesAreInvalid) {
			knightBoard.moveKnightToPosition(path[path.size() - 1]);
		}
	}
	else {
		cerr << "Moves are invalid!\n";
	}

	knightBoard.printKnightBoard();
}

void KnightEngine::knightTour() {

}
