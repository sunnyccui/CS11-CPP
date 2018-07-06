#include <cstdlib>   // needed for srand() and rand() functions
#include <ctime>     // needed for time() function
#include <vector>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <assert.h>
#include "maze.hh"

using namespace std;


void usage(const char *progname) {
    cout << "usage: " << progname << "numRows numCols" << endl;
    cout << "\tnumRows is the number of rows in the maze" << endl;
    cout << "\tnumCols is the number of columns in the maze" << endl;
}

// Get the location of the neighbor cell in the specified direction.
// If the neighbor cell has NOT been marked visited, append the direction into the vector
void addDirectionOption(const Maze &maze, const Location &current,
                        Direction dir, vector<Direction> &v){
    Location next = maze.getNeighborCell(current.row, current.col, dir);
    if (!maze.isVisited(next.row, next.col)){
        v.push_back(dir);
    }

}


int main(int argc, char **argv){

    if (argc != 3){
        usage(argv[0]);
            return 1;
    }

    int numRows = (int) atoi(argv[1]);
    int numCols = (int) atoi(argv[2]);

    // Variables:

    Maze maze(numRows, numCols);
    vector<Location> path;
    srand(time(NULL));

    // Clear the maze.
    // Fill in all walls in the maze.
    maze.clear();
    maze.setAllWalls();

    // Set the start to be the top-left cell in the maze.
    maze.setStart(0, 0);

    // Set the end to be the bottom-right cell in the maze.
    maze.setEnd(numRows - 1, numCols - 1);
    maze.setVisited(0,0);
    path.push_back(Location(0,0));
    while (!path.empty()){
        Location current = path.back();

        // If the cell we are looking at is the end of the maze, skip the
        // cell so that the current path will not go through the end-point.

        if (current == maze.getEnd()){
            // Remove the last element off of the path vector.
            path.pop_back();
        }
        //  Continue on to the next iteration of the loop

        // Generating this vector of potential directions that can be taken is a
    // bit complex.  If the cell is on a border of the maze, then that will
    // eliminate one or two directions that could be taken.  Additionally, if
    // the neighbor cell has already been marked VISITED, then that direction
    // is not available.

        vector<Direction> options;
        if (current.row > 0){  // I can move up a row
            addDirectionOption(maze, current, Direction::NORTH, options);
        }

        if (current.row < maze.getNumRows() - 1){ // I can move down a row
            addDirectionOption(maze, current, Direction::SOUTH, options);
        }
        if (current.col > 0){  // I can move up a col
            addDirectionOption(maze, current, Direction::WEST, options);
        }
        if (current.row < maze.getNumCols() - 1){ // I can move down a row
            addDirectionOption(maze, current, Direction::EAST, options);
        }

        // There are no directions we can move from the current cell!  We
        // need to backtrack.  (See vector::pop_back() for this operation.)
        if (options.size()==0){
            path.pop_back();
            continue;
        }
        //  Continue on to the next iteration of the loop


        // Choose a random direction!  Then, clear the wall in that direction,
        // and move into the next cell.
        int index = rand() % options.size();
        Direction dir = options[index];
        maze.clearWall(current.row, current.col, dir);
        Location next = maze.getNeighborCell(current.row, current.col, dir);
        maze.setVisited(next.row, next.col);
        path.push_back(next);
    }
    maze.print(cout);

    return 0;
}
