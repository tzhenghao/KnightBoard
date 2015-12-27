#include "KnightEngine.h"

using namespace std;

KnightEngine::KnightEngine(const Position &start, const Position &stop,
							const char *inputFile) {

	knightBoard.initializeKnightBoard(start, stop, inputFile);

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

int KnightEngine::calculateTerrainCost(const Position &pos) {

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

int KnightEngine::findBestPath() {

	// Set of explored nodes.
	unordered_set<int> closedSet;

	queue<Position> openSet;
	openSet.push(knightBoard.startPosition);

	unordered_map<int, Position> fromNodes;

	// Total cost from starting position along best known path.
	unordered_map<int, int> gScore;
	gScore[toHash(knightBoard.startPosition)] = 0; // Cost from start along best known path.

    // Estimated total cost from start to goal through y.
	unordered_map<int, int> fScore;
	fScore[toHash(knightBoard.startPosition)] = calculateHeuristicCost(knightBoard.startPosition, knightBoard.endPosition);

	while (!openSet.empty()) {

		Position currentPos = openSet.front(); // TODO:the node in OpenSet having the lowest f_score[] value

		if (currentPos == knightBoard.endPosition) {
			buildPath(fromNodes, knightBoard.endPosition);
            return gScore[toHash(currentPos)];
		}

        //openSet.Remove(current)
		closedSet.insert(toHash(currentPos));

        //for each neighbor of current {

		//	if (closedSet.find(neighbor) != closedSet.end()) {
        //        continue;
		//	}
        //    int currentGScore = gScore[currentPos]
		//						+ calculateTerrainCost(knightBoard, neighbor);

		//	if (openSet.find(neighbor) == openSet.end()) {
		//		openSet.enqueue(neighbor);
		//	}
        //    else if (currentGScore >= gScore[neighbor])
        //        continue;

        //    // Best path so far.
        //    fromNodes[neighbor] = currentPos;
        //    gScore[neighbor] = currentGScore;
        //    fScore[neighbor] = gScore[neighbor]
		//						+ calculateHeuristicCost(neighbor, endPosition);
		//}
	}
	return -1;
}

int KnightEngine::calculateHeuristicCost(const Position &from, const Position &to) {

}

void KnightEngine::buildPath(unordered_map<int, Position> &fromNodes,
								Position &currentNode) {

	path.resize(fromNodes.size());

	path[fromNodes.size() - 1] = currentNode;

	int i = fromNodes.size() - 2;

	while (fromNodes.find(toHash(currentNode)) != fromNodes.end()) {

		currentNode = fromNodes[toHash(currentNode)];
		path[i] = currentNode;
		--i;
	}
}

void KnightEngine::printPath() {

	for (auto &pos: path) {
		cout << "(" << pos.x << "," << pos.y << "),";
	}
	cout << "\n";
}

void KnightEngine::task1() {

	// Populate moves.
	path.push_back(Position(2, 2));
	path.push_back(Position(2, 1));

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
