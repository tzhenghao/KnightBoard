#include "KnightEngine.h"
#include <cassert>

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
};

KnightEngine::KnightEngine(const Position &start, const Position &stop,
							const char *inputFile) {

	knightBoard.initializeKnightBoard(start, stop, inputFile);

	assert(path.empty());
}

bool KnightEngine::isMoveValid(const Position& position) {

	Position knightPosition = knightBoard.getKnightPosition();

	// Check for outside the allocated board.
	if (position.x < 0 || position.y < 0
		|| position.x > BOARD_SIZE - 1
		|| position.y > BOARD_SIZE - 1) {
		cerr << "Move is outside allocated board!\n";
		return false;
	}
	else if (!isTerrainValid(position.x, position.y)) {
		return false;
	}
	// Check for top and bottom
	else if (knightPosition.x - position.x == 2) {

		if (knightPosition.y - position.y == 1) {

			for (int i = 0; i < 2; ++i) {
				if (!isTerrainValid(position.x + i, position.y)) {
					return false;
				}
			}
		}
		else if (position.y - knightPosition.y == 1) {

			for (int i = 0; i < 2; ++i) {
				if (!isTerrainValid(position.x + i, position.y)) {
					return false;
				}
			}
		}
		else {
			return false;
		}
	}
	else if (position.x - knightPosition.x == 2) {

		if (knightPosition.y - position.y == 1) {

			for (int i = 0; i < 2; ++i) {
				if (!isTerrainValid(position.x - i, position.y)) {
					return false;
				}
			}

		}
		else if (position.y - knightPosition.y == 1) {
			for (int i = 0; i < 2; ++i) {
				if (!isTerrainValid(position.x - i, position.y)) {
					return false;
				}
			}
		}
		else {
			return false;
		}
	}
	else if (knightPosition.y - position.y == 2) {

		if (knightPosition.x - position.x == 1) {

			for (int i = 0; i < 2; ++i) {
				if (!isTerrainValid(position.x, position.y + i)) {
					return false;
				}
			}
		}
		else if (position.x - knightPosition.x == 1) {

			for (int i = 0; i < 2; ++i) {
				if (!isTerrainValid(position.x, position.y + i)) {
					return false;
				}
			}
		}
		else {
			return false;
		}
	}
	else if (position.y - knightPosition.y == 2) {

		if (knightPosition.x - position.x == 1) {

			for (int i = 0; i < 2; ++i) {
				if (!isTerrainValid(position.x, position.y - i)) {
					return false;
				}
			}
		}
		else if (position.x - knightPosition.x == 1) {

			for (int i = 0; i < 2; ++i) {
				if (!isTerrainValid(position.x, position.y - i)) {
					return false;
				}
			}
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
		cerr << "Error: CalculateTerrainCost evaluated to R or B\n";
		return -1;
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
		return -1;
	}
}

int KnightEngine::findBestPath() {

	// Set of explored nodes.
	unordered_set<int> closedSet;

	priority_queue<Position, vector<Position>, PriorityQueueComparator> openSet;
	unordered_set<int> isInOpenSet; // Mapping for whether the node is in the open set.

	openSet.push(knightBoard.startPosition);
	isInOpenSet.insert(toHash(knightBoard.startPosition));

	unordered_map<int, Position> fromNodes;

	// Total cost from starting position along best known path.
	unordered_map<int, int> gScore;
	gScore[toHash(knightBoard.startPosition)] = 0; // Cost from start along best known path.

	fScore[toHash(knightBoard.startPosition)] = calculateHeuristicCost(knightBoard.startPosition, knightBoard.endPosition);

	while (!openSet.empty()) {

		Position currentPos = openSet.top();

		if (currentPos == knightBoard.endPosition) {

			buildPath(fromNodes, knightBoard.endPosition);

			// Move knight to that position and print the knight board.
			knightBoard.moveKnightToPosition(path[path.size() - 1]);
			knightBoard.printKnightBoard();

            return fScore[toHash(currentPos)];
		}

        openSet.pop();
		isInOpenSet.erase(toHash(currentPos));

		closedSet.insert(toHash(currentPos));

		Position neighbor;

		for (int i = 0 ; i < 8; ++i) {

			generateNeighbor(neighbor, currentPos, (Moves)i);

			if (isMoveValid(neighbor)) {

				if (closedSet.find(toHash(neighbor)) != closedSet.end()) {
					continue;
				}

				int currentGScore = gScore[toHash(currentPos)]
									+ calculateTravelCost((Moves)i, neighbor);

				// Add to open set if it isn't there already.
				if (isInOpenSet.find(toHash(neighbor)) == isInOpenSet.end()) {
					openSet.push(neighbor);
					isInOpenSet.insert(toHash(currentPos));
				}
				// Don't bother looking if the cost is more than what we already have.
				else if (currentGScore >= gScore[toHash(neighbor)]) {
					continue;
				}

				// Best path so far.
				fromNodes[toHash(neighbor)] = currentPos;
				gScore[toHash(neighbor)] = currentGScore;
				fScore[toHash(neighbor)] = gScore[toHash(neighbor)]
									+ calculateHeuristicCost(neighbor, knightBoard.endPosition);
			}
		}
	}
	return -1;
}

int KnightEngine::calculateTravelCost(Moves i, const Position&neighbor) {

	Position knightPosition = knightBoard.getKnightPosition();

	int totalCost = calculateTerrainCost(knightPosition.x, knightPosition.y);

	if (i == LEFTUP || i == LEFTDOWN) {

		for (int i = 0; i < 2; ++i) {
			totalCost += calculateTerrainCost(neighbor.x + i, neighbor.y);
		}
	}
	else if (i == RIGHTUP || i == RIGHTDOWN) {

		for (int i = 0; i < 2; ++i) {
			totalCost += calculateTerrainCost(neighbor.x - i, neighbor.y);
		}
	}
	else if (i == UPLEFT || i == UPRIGHT) {

		for (int i = 0; i < 2; ++i) {
			totalCost += calculateTerrainCost(neighbor.x, neighbor.y + i);
		}
	}
	else if (i == DOWNLEFT || i == DOWNRIGHT) {

		for (int i = 0; i < 2; ++i) {
			totalCost += calculateTerrainCost(neighbor.x, neighbor.y - i);
		}
	}
	else {
		cerr << "Error: Cannot find correct knight move!\n";
		return -1;
	}

	return totalCost;
}

int KnightEngine::calculateHeuristicCost(const Position &from, const Position &to) {

	// TODO: Calculate heuristic cost.
	return 0;
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

	assert(path.empty());
	path.resize(fromNodes.size() - 1);

	path[path.size() - 1] = currentNode;

	int i = path.size() - 2;

	while (fromNodes.find(toHash(currentNode)) != fromNodes.end()) {

		currentNode = fromNodes[toHash(currentNode)];
		path[i] = currentNode;
		--i;
	}
}

void KnightEngine::printPath() {

	for (auto &pos: path) {
		cout << "(" << pos.x << "," << pos.y << ") ";
	}
	cout << "\n";
}

void KnightEngine::task1() {

	// Populate moves.
	path.push_back(Position(2, 2));
	//path.push_back(Position(2, 1));

	bool movesAreInvalid = false;

	if (!path.empty()) {

		for (auto &position: path) {

			if (!isMoveValid(position)) {
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
