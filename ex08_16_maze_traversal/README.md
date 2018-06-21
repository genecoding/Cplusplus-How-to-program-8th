8.16 (Maze Traversal) The grid of hashes (#) and dots (.) in Fig. 8.22 is a two-dimensional array
representation of a maze. In the two-dimensional array, the hashes represent the walls of the maze
and the dots represent squares in the possible paths through the maze. Moves can be made only to
a location in the array that contains a dot.

There is a simple algorithm for walking through a maze that guarantees finding the exit
(assuming that there is an exit). If there is not an exit, you’ll arrive at the starting location again.
Place your right hand on the wall to your right and begin walking forward. Never remove your
hand from the wall. If the maze turns to the right, you follow the wall to the right. As long as you
do not remove your hand from the wall, eventually you’ll arrive at the exit of the maze. There may
be a shorter path than the one you’ve taken, but you are guaranteed to get out of the maze if you
follow the algorithm.

Write recursive function mazeTraverse to walk through the maze. The function should
receive arguments that include a 12-by-12 character array representing the maze and the starting
location of the maze. As mazeTraverse attempts to locate the exit from the maze, it should place
the character X in each square in the path. The function should display the maze after each move,
so the user can watch as the maze is solved.
