// Zheng Hao Tan
// Date: December 25, 2015

#include <iostream>
#include <vector>

#include "KnightEngine.h"

using namespace std;

// Prototypes.

int main(int argc, char *argv[]) {

	if (argc != 2) {
		cerr << "Invalid file arguments\n";
		cerr << "Please run:\n";
		cerr << "./knightboard <test case file>";
		return -1;
	}

	Position start(0, 1);
	Position stop(1, 3);

	KnightEngine knightEngine(start, stop, argv[1]); // File argument.

	//knightEngine.task1();
	int cost = knightEngine.findBestPath();

	cout << "Total cost: " << cost << "\n";

	knightEngine.printPath();
	return 0;
}
