#include <iostream>
#include "Maze.h"
#include <fstream>
#include <cstdio> // EOF()
#include <stdlib.h>

typedef	unsigned int Uint;
const char Maze::WALL = '#';
const char Maze::PATH = ' ';
const char Maze::SOLVEDPATH = '*';
const char Maze::END = 'E';
const char Maze::START = 'S';
const int Maze::STARTposx = 1;
const int Maze::STARTposy = 1;


Maze & Maze::Create_maze(Uint row, Uint col){
	if (row%2 == 0)
		row++;
	if (col%2 == 0)
		col++;

	// Fill the vector<vector> with WALLs
	Map = std::vector< std::vector<char> >(row, std::vector<char>(col, WALL)); 
	// Number of cells in the grid/map
	TotalCells = row*col; 
	// Mark first CurrentCell as (STARTposx, STARTposy)
	CurrentCell = std::make_pair(STARTposx,STARTposy);
	// Set visited cells to 1
	VisitedCells = 1;
	Generate_maze(CurrentCell);
	return *this;
}

void Maze::Generate_maze(std::pair<Uint, Uint> CurrentCell){
	srand (time(NULL));
	int RandElement;
	while (VisitedCells < TotalCells){

		// To check the direction of neighbour
		x = CurrentCell.first, y = CurrentCell.second;
		Map[x][y] = PATH;

		// NeighboursToVisit is an vector<pair<Uint, Uint> >
		NeighboursToVisit.clear();
		NeighboursToVisit = Find_neighbours(CurrentCell);

		if (!NeighboursToVisit.empty()){
			// RandElement is the index to access a random neighbour
			RandElement = rand()%NeighboursToVisit.size();

			// Keep track of the direction of where to remove the wall
			Direction = Check_direction(x, y, NeighboursToVisit);

			// Knock down the wall between this random cell and CurrentCell
			Crush_wall(NeighboursToVisit[RandElement], Direction[RandElement]);

			// push CurrentCell location on the CellStack  
			CellStack.push(std::make_pair(CurrentCell.first, CurrentCell.second));

			// make the new cell CurrentCell  
			CurrentCell = std::make_pair(NeighboursToVisit[RandElement].first, NeighboursToVisit[RandElement].second);
			VisitedCells++;
		}
		else{
			if(!CellStack.empty()){
				// make the top of the cellstack to CurrentCell
				CurrentCell = CellStack.top();
				// pop the most recent cell entry off the CellStack  
				CellStack.pop();
			}
			else
				VisitedCells = TotalCells;
		}
	}
	// Set end position
	Map[Map.size()-2][Map[Map.size()-2].size()-2] = END;
	Map[1][1] = START;
}

// x, y is the previous value of CurrentCell
std::vector<Uint> Maze::Check_direction(Uint x, Uint y, std::vector<std::pair <Uint, Uint> > v){
	std::vector<Uint> dir;
	int dx, dy;
	for (int i = 0; i < v.size(); i++)
	{
		dx = (v[i].first - x); // Computing the direction
		dy = (v[i].second - y); // Computing the direction
		//std::cout << "Delta:" << dx << " " << dy << std::endl;

		if (dx == 2)			// If east
			dir.push_back(1); // Push 1 (east by the enumeration)
		else if (dx == -2)	// if west
			dir.push_back(3); // Push 3 (west by the enumeration)
		else if (dy == -2)	// if north
			dir.push_back(0); // push 0 (north by the enumeration)
		else if (dy == 2)	// if south
			dir.push_back(2); // push 2 (south by the enumeration)
		//std::cout << dir.back() << std::endl;
	}
	return dir;
}

std::vector< std::pair<Uint, Uint> > Maze::Find_neighbours(std::pair<Uint, Uint> CurrentCell){
	std::vector<std::pair <Uint, Uint> > v;
	CurrentCell.first+=2;	// East of original Cell
	// If walls intact of the neighbour to the east of original cell
	if (Walls_intact(CurrentCell)) 
		v.push_back(CurrentCell);

	// If walls intact of the neighbour to the west of original cell
	CurrentCell.first-=4;	// West of original cell
	if (Walls_intact(CurrentCell))
		v.push_back(CurrentCell);

	CurrentCell.first+=2;	// Back to original cell
	// If walls intact of the neighbour to the south of original cell
	CurrentCell.second+=2;	// South of original cell
	if (Walls_intact(CurrentCell))
		v.push_back(CurrentCell);

	// If walls intact of the neighbour to the north of original cell
	CurrentCell.second-=4;	// North of original cell
	if (Walls_intact(CurrentCell))
		v.push_back(CurrentCell);

	//CurrentCell.second-=2;	// Back to original cell
	// Return a vector with all neighbours with all walls intact
	return v;
}

bool Maze::Walls_intact(std::pair<Uint, Uint> CurrentCell){ // Returns wether all walls intact or not
	int row = CurrentCell.first;
	int col = CurrentCell.second;
	if (col < 1 || row < 1)
		return false;
	// If it's outside the map
	if(row < Map.size()-1 && col < Map[row].size()-1){	
		// If all walls intact, return true
		if( 
			(Map[row+1][col] == WALL) && // check east wall
			(Map[row-1][col] == WALL) && // check west wall
			(Map[row][col-1] == WALL) && // check north wall
			(Map[row][col+1] == WALL)){	 // check south wall
			return true;
		}
	}
	return false;
}

void Maze::Crush_wall(std::pair<Uint, Uint> CurrentCell, int dir){
	// dir is a variable obtained from Check_direction()
	if (dir == north){
		Map[CurrentCell.first][CurrentCell.second+1] = PATH; // set north of CurrentCell to path
	}
	else if (dir == east){
		Map[CurrentCell.first-1][CurrentCell.second] = PATH; // set east of CurrentCell to path
	}
	else if (dir == south){
		Map[CurrentCell.first][CurrentCell.second-1] = PATH; // set south of CurrentCell to path
	}
	else if (dir == west){
		Map[CurrentCell.first+1][CurrentCell.second] = PATH; // set west of CurrentCell to path
	}
}

Maze & Maze::Print_maze(std::string file){
	std::ofstream outfile(file.c_str());
	// if file is open, write to file otherwise write to console
	std::ostream &out= (!outfile.is_open()? std::cout : outfile);
	// Check if file failed to open
	if(file != "" && (!outfile.is_open()))
		std::cerr << "File failed to open." << std::endl;
	for (int i = 0; i < Map.size(); i++)
	{
		for (int j = 0; j < Map[i].size(); j++)
		{
				out << Map[i][j];
		}
			out << std::endl;
	}
	if(outfile.is_open())
		outfile.close();
	return *this;
}

bool Maze::Solve(int x, int y){
	// If x, y is outside maze, return false
	if (x >= Map.size() || x < 0 || y < 0 || y >=  Map[Map.size()-1].size()){
		return false;
	}
	// If x, y is the goal/end, return true
	if (Map[x][y] == END){
		return true;
	}
	// If x, y is not open, return false
	if (Map[x][y] != PATH && Map[x][y] != START)
		return false;
	// Mark x, y part of the solution
	Map[x][y] = SOLVEDPATH;

	// If Solve North of x, y is true, return true
	if (Solve(x, y-1) == true) return true;
	// If Solve East of x, y is true, return true
	if (Solve(x+1, y) == true) return true;
	// If Solve South of x, y is true, return true
	if (Solve(x, y+1) == true) return true;
	// If Solve West of x, y is true, return true
	if (Solve(x-1, y) == true) return true;
	Map[x][y] = PATH;
	return false;
}

bool Maze::Read_file(std::string file){
	Map.clear(); // Make sure it's cleared
	int j(0);
	std::string line;
	std::ifstream infile(file); //  The input file
	if (infile.is_open()) {		// Make sure the file is open
	    while (!infile.eof()) {	// until we're at the end of the file
	    	std::getline(infile, line);	// Take line by line
	    	if(line.empty())
	    		continue;
	    	// Push vector<char> to make it a vector<vector<char > >
	    	Map.push_back(std::vector<char>());
			for (int i = 0; i < line.length(); i++){
				// If invalid character found, return false and give error message.
				if ((line[i] != WALL) && (line[i] != PATH) && (line[i] != SOLVEDPATH) && (line[i] != START) && (line[i] != END)){
					std::cerr << "File consists of invalid characters." << std::endl;
					return false;
				}
				// Add next element
				Map[j].push_back(line[i]);
	    	}
			j++;
		}
		infile.close();
		return true;
	}
	std::cerr << "File failed to be open." << std::endl;
	return false;
}