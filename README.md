#KnightBoard Program
A C++ implementation of the Knight's Tour algorithm

How to run:
----------
A Makefile has been provided for you in the home directory. Just type 'make'
to compile it. Type 'make clean' to clean the directory.

After that, run:

./knightboard <map file>

Example:

./knightboard testcases/map1.txt

The map file (map1.txt) needs to be formatted correctly, with exactly 32x32 positions.

NOTE: This program assumes that there are none or exactly 2 teleportation portals (T).

Files
-----
1. KnightBoard.h/cpp: This is where the knight board is implemented.
2. KnightEngine.h/cpp: This is the main interface for running the knight's tour.
3. testcases/map1.txt : This is a sample map for which the program will parse and
						run knight's tour on. More maps will be added here.


Approaches
-----------
Level 1: KnightEngine::isMoveValid(const Position &knightPosition, const Position& position);

This function validates the move given to it and returns true/false if the knight can be moved
to the specified position. It is called in a loop that generates neighbors, and this function
is responsible for validating these moves.

Level 2/3: KnightEngine::findBestPath(const Position &start, Position &stop);

This function returns the cost of the best path from start to stop positions. The cost here is
defined as the minimum number of moves required to reach the destination. Returns -1 if no path
can be found.

Level 4: KnightEngine::calculateTerrainCost(int x, int y);

This function is primarily responsible for calculating the terrain cost of given x and y coordinates.
A separate function called isTerrainValid is responsible for checking if the terrain is valid.

Level 5: KnightEngine::knightTour();

This function is responsible for running the knight tour. The best path will be printed out to console.

I used a A*/Dijkstra's algorithm to find the best path between start and end points. The main difference
between the two algorithms is that A* requires a heuristic cost (handled via calculateHeuristicCost()) and
Dijkstra doesn't. However, when we have teleportation, we can accurately give a good heuristic as it's
possible to teleport right to the end point (Example, S and E are both Ts!) We will be overestimating/break
our upper bound if we used A*. My program uses A* whenever there are no Ts on the map, and Dijkstra whenever they are present (return 0 on heuristicCost). It will be optimally efficient.

For level 5, although it is possible to use a brute force algorithm (use every node as start/end points and figure out which one works), this will not be scalable.  A 8x8 board will have approximately 4×10^(51)
moves. Another way to do it is to use a divide and conquer approach. Since our board is at least the size of 6, we can cut the board into different parts and try to solve the knight's tour in each of them. Then, we can generalize this by connecting the end points of each square to form a larger tour. We can also use
another heuristic called the Warnsdorff's rule. In this heuristic, we aim to travel to the positions where
there are least possible moves to that position. This will help us travel/visit more nodes without revisiting them again.

Another thing to keep in mind when implementing level 5 is to know that we can "prune" early if our path tries to revisit certain paths that we have visited before. In other words, those tours have failed and can only go as far as the number of nodes that it visited before hitting a previously visited node. We can keep track of this using a data structure on the side and updating the best path so far as we explore more paths.

NOTE: There is one part of my solution that sorts a vector (O(n log n)) for the openSet. This is somewhere
in the findBestPath() function, and it needs to be sorted by the fScore of each visited node. I wanted to use a priority queue for this, and I tried to do this but I was running into problems as the comparator isn't applied whenever new/old elements are added/removed from the queue. This made it significantly worse as I
do not have access to an iterator given the nature of the STL's priority_queue. There is a workaround for this, and I believe I'm able to achieve better time complexity, but given the time constraints in getting a correct program running, I wasn't able to do so.

With that in mind, I strongly believe that my implementation of the knight board still has tons of improvements/optimizations that I can work on.

Support
-------
Please feel free to contact me if you have any questions/concerns. My email address is tanzhao@umich.edu
