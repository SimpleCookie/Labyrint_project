#ifndef MAZEH
#define MAZEH
#include <vector>
#include <utility>	// std::pair
#include <stack>
#include <string>

class Maze{
public:
	enum { north, east, south, west };
	static const char WALL, PATH, END, START, SOLVEDPATH;
	static const int STARTposx, STARTposy;
	unsigned int VisitedCells, TotalCells, x, y;

	
	// sets total cells and fill the map with WALLS, calls Generate_maze	
	Maze & Create_maze(unsigned int row, unsigned int col);

	// Self explantory, prints the maze
	//void Print_maze(std::string file = "no!ne");
	Maze & Print_maze(std::string file = "");

	// Solves the maze with recurison
	bool Solve(int x = 1, int y = 1);

	// Reads a file into a vector<vector<char> >
	bool Read_file(std::string file);

	std::vector<char> operator [](int i) const{
		return Map[i];
	}
	std::vector<char> &operator [](int i){
		return Map[i];
	}

	int Get_height(){
		return Map.size();
	}
	int Get_width(){
		if(Map.size())
			return Map[0].size();
		return 0;
	}

private:
	// Pair<int, int> for the current cell
	std::pair <unsigned int, unsigned int> CurrentCell;

	// CellStack to hold list of all cell locations
	std::stack< std::pair<unsigned int, unsigned int> > CellStack; 

	// Vector<pair> for which neighbours to visit
	std::vector< std::pair<unsigned int, unsigned int> > NeighboursToVisit;

	// Keep track of the direction of where to remove the wall
	std::vector<unsigned int> Direction;

	// Calls Walls_intact and returns neighbours with walls intact
	void Generate_maze(std::pair<unsigned int, unsigned int> CurrentCell);

	// Check whether the walls are still there or already crushed
	bool Walls_intact(std::pair<unsigned int, unsigned int> CurrentCell);

	// Crush a wall
	void Crush_wall(std::pair<unsigned int, unsigned int> CurrentCell, int dir);

	// Calls Find_neighbours and walks to next cell and crush the wall between
	std::vector< std::pair<unsigned int, unsigned int> > Find_neighbours(std::pair<unsigned int, unsigned int> CurrentCell);

	// Find the direction between two cells, this will be applied with the Crush_wall function
	std::vector<unsigned int> Check_direction(unsigned int x, unsigned int y, std::vector<std::pair <unsigned int, unsigned int> > v);

	// vector<vector> with chars to indicate the maze map
	std::vector< std::vector<char> > Map;
};

#endif 
/* MAZE.H */
