#include "maze.hh"
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <assert.h>

using namespace std;


Maze::Maze(int rows, int cols){
	numRows = rows;
	numCols = cols;
	int r_exp = 2 * numRows + 1;
	int c_exp = 2 * numCols + 1;
	cells = new MazeCell[r_exp * c_exp];
	for  (int i = 0; i < r_exp * c_exp; i++){
		cells[i] = MazeCell::EMPTY;
	}
}


Maze::Maze(const Maze &m){
	numRows = m.numRows;
    
    // The number of columns with cells in them
    numCols = m.numCols;
    
    // The maze's "expanded representation"
    cells = m.cells;

    // The start of the maze, in cell coordinates
    start = m.start;
    
    // The end of the maze, in cell coordinates
    end = m.end;
    int r_exp = 2 * numRows + 1;
	int c_exp = 2 * numCols + 1;
	cells = new MazeCell[r_exp * c_exp];
	for  (int i = 0; i < r_exp * c_exp; i++){
		cells[i] = m.cells[i];
	}
}

Maze::~Maze() {
	delete[] cells;
}

Maze & Maze::operator=(const Maze &m){
	if (this != &m){
		delete[] cells;
		numRows = m.getNumRows();
		numCols = m.getNumCols();
		int r_exp = 2 * numRows + 1;
		int c_exp = 2 * numCols + 1;
		cells = new MazeCell[r_exp * c_exp];
		for (int i = 0; i < r_exp * c_exp; i++){
			cells[i] = m.cells[i];
		}
		start = m.start;
       	end = m.end;
	}
    return *this;
}

// Returns the expanded coordinates of the specified cell coordinates
Location Maze::getCellArrayCoord(int cellRow, int cellCol) const{
		//cout << "cellRow " << cellRow << endl;
	//	cout << "cellCol " << cellCol << endl;

	assert (cellRow >= 0 && cellRow < numRows);
	assert (cellCol >= 0 && cellCol < numCols);
	int r_exp = 2 * cellRow + 1;
	int c_exp = 2 * cellCol + 1;
	return Location(r_exp, c_exp);
}

// Returns the expanded coordinates of the wall on a specific side of
// a cell given in cell coordinates
Location Maze::getWallArrayCoord(int cellRow, int cellCol, Direction direction) const{
	Location l = getCellArrayCoord(cellRow, cellCol);
	if (direction == Direction::NORTH){
		l.row -=1;
	}
	else if (direction == Direction::SOUTH){
		l.row +=1;
	}
	else if (direction == Direction::EAST){
		l.col +=1;
	}
	else if (direction == Direction::WEST){
		l.col -=1;
	}
	return Location(l.row, l.col);
}

int Maze::getArrayIndex(const Location &loc) const{
	return loc.row * (2 * numCols + 1) + loc.col;
}


// Returns the number of rows in the maze
int Maze::getNumRows() const{
	return numRows;
}


// Returns the number of columns in the maze
int Maze::getNumCols() const{
	return numCols;
}


// Returns the starting point in the maze
Location Maze::getStart() const{
	return start;
}

// Sets the starting point in the maze    
void Maze::setStart(int row, int col){
	start = Location(row, col);
}
    

// Returns the ending point in the maze    
Location Maze::getEnd() const{
	return end;
}
    
// Sets the ending point in the maze
void Maze::setEnd(int row, int col){
	end = Location(row, col);
}
    

// Sets all cells and walls to be empty, so that the maze is
// completely cleared
void Maze::clear(){
	int r_exp = 2 * numRows + 1;
	int c_exp = 2 * numCols + 1;
	for (int i = 0; i < r_exp * c_exp; i++){
		cells[i] = MazeCell::EMPTY;
	}
}
    
// Places a wall at every location that can be a wall in the maze
void Maze::setAllWalls(){
	for (int i = 0; i < numRows; i++){
		for (int j = 0; j < numCols; j++){
			setWall(i, j, Direction::EAST);
			setWall(i, j, Direction::WEST);
			setWall(i, j, Direction::NORTH);
			setWall(i, j, Direction::SOUTH);
		}
	}
}

// Returns the value of the specified
MazeCell Maze::getCell(int cellRow, int cellCol) const{
	Location l = getCellArrayCoord(cellRow, cellCol);
	return cells[getArrayIndex(l)];
}

void Maze::setCell(int cellRow, int cellCol, MazeCell val){
	Location l = getCellArrayCoord(cellRow, cellCol);
	cells[getArrayIndex(l)] = val;
}

// Returns the cell-coordinates of the neighboring cell in the specified
// direction.  Trips an assertion if the given cell has no neighbor in the
// specified direction (e.g. the NORTH neighbor of cell (0,5)).
Location Maze::getNeighborCell(int cellRow, int cellCol, Direction direction) const{
	if (direction == Direction::NORTH){
		if (cellRow > 0){
			cellRow -= 1;
		}
	}
	else if (direction == Direction::SOUTH){
		if (cellRow < numRows - 1){
			cellRow += 1;
		}
	}
	else if (direction == Direction::EAST){
		if (cellCol < numCols - 1){
			cellCol += 1;
		}
	}
	else if (direction == Direction::WEST){
		if (cellCol > 0){
			cellCol -= 1;
		}
	}
	assert (cellRow >= 0 && cellRow < numRows);
	assert (cellCol >= 0 && cellCol < numCols);
	return Location(cellRow, cellCol);
}


    // Returns true if there is a wall in the specified direction from the
    // given cell, false otherwise
bool Maze::hasWall(int cellRow, int cellCol, Direction direction) const{
	Location wall = getWallArrayCoord(cellRow, cellCol, direction);
	int i = getArrayIndex(wall);
	return cells[i] == MazeCell::WALL;
}

// Puts a wall on the specified side of the given cell
void Maze::setWall(int cellRow, int cellCol, Direction direction){
	Location wall = getWallArrayCoord(cellRow, cellCol, direction);
	int i = getArrayIndex(wall);
	cells[i] = MazeCell::WALL;
}

// Removes a wall on the specified side of the given cell
void Maze::clearWall(int cellRow, int cellCol, Direction direction){
	Location wall = getWallArrayCoord(cellRow, cellCol, direction);
	int i = getArrayIndex(wall);
	cells[i] = MazeCell::EMPTY;
}


    // Returns true if the specified maze cell has been visited.
bool Maze::isVisited(int cellRow, int cellCol) const{
	Location l = getCellArrayCoord(cellRow, cellCol);
	int i = getArrayIndex(l);
	return cells[i] == MazeCell::VISITED;
}

    // Changes the cell's value to VISITED
void Maze::setVisited(int cellRow, int cellCol){
	Location l = getCellArrayCoord(cellRow, cellCol);
	int i = getArrayIndex(l);
	cells[i] = MazeCell::VISITED;
}


void Maze::print(ostream &os) const{
	os << "Number of rows: " << numRows << endl;
	os << "Number of columns: " << numCols << endl;
	for  (int i = 0; i < numRows; i++){
		for (int j = 0; j < numCols; j++){
			if (hasWall(i,j, Direction::NORTH)){
				os << "+---";
			}
			else{
				os << "+   ";
			}

		}
		os << "+" << endl;
		for (int j = 0; j < numCols; j++){
			if (hasWall(i,j, Direction::WEST)){
				os << "| ";
			}
			else {
				os << "  ";

			}
			if (start.row == i && start.col == j){
					os << "S ";
			}
			else if (end.row == i && end.col == j){
				//os << end.row << "end" << endl;
				os << "E ";
			}
			else{
				os << "  ";
			}
		

		}
		os << "|" << endl;
	}
	for (int n = 0; n < numCols; n++){
		os << "+---";
	}
	os << "+" << endl;
}