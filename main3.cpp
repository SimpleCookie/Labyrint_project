#include "Maze.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <getopt.h> // includes the getopt command for input flags
#include <stdlib.h> // for EXIT_FAILURE and EXIT_SUCCESS
#include "Inputs.h"
#include <fstream> // File management

int main(int argc, char const *argv[])
{
	Maze labyrinth; 
	std::string choice, width, height, file;
	int col, row;
	std::cout << "\t -:: Welcome to Marcuz maze generator ::-" << std::endl;
	while (choice != "3"){ // Simple user interface
		std::cout 
			<< "Choose option" << std::endl
			<< "[1] -\t Generate maze" << std::endl
			<< "[2] -\t Generate and solze maze" << std::endl
			<< "[3] -\t Use input-data" << std::endl
			<< "[4] -\t Use output-data" << std::endl
			<< "[5] -\t Exit program" << std::endl;
		getline(std::cin, choice);
		std::cout << std::endl;
		if (choice.find('1') != std::string::npos){ // print maze



			std::cout << "Enter width of maze ...\n";
			std::getline(std::cin, width);
			std::cout << "Enter height of maze ...\n";
			std::getline(std::cin, height);
			row = Check_valid_size(height);
			col = Check_valid_size(width);
			if (row == 0 || col == 0){	
				std::cout << "Enter a valid number (greater than 3) to represent the size of the maze" << std::endl;
			}
			if (row != 0 || col != 0){	
					// Generate a maze
				labyrinth.Create_maze(row, col);
				labyrinth.Print_maze();
			}
	





		}else if(choice.find('2') != std::string::npos){ // print and solve
			std::cout << "Enter width of maze ...\n";
			std::getline(std::cin, width);
			std::cout << "Enter height of maze ...\n";
			std::getline(std::cin, height);
			row = Check_valid_size(height);
			col = Check_valid_size(width);
				// Generate a maze
			labyrinth.Create_maze(row, col);
			labyrinth.Solve(1, 1);
			labyrinth.Print_maze();
			

		}else if(choice.find('3') != std::string::npos){ // print and solve
			std::cout << "Enter name of file ...\n";
			std::getline(std::cin, file);
			if (labyrinth.Read_file(file)){
				labyrinth.Solve(1, 1);
				labyrinth.Print_maze();
			}
			else{
				std::cout << "Error opening file" << std::endl;
			}

		}else if(choice.find('4') != std::string::npos){ // print and solve
			std::cout << "Enter name of file ...\n";
			std::getline(std::cin, file);
			labyrinth.Create_maze(15, 15);
			labyrinth.Solve(1, 1);
			labyrinth.Print_maze(file);

		}else if(choice.find('5') != std::string::npos){
			return 0;
		}else{
			std::cout << "Please choose between [1], [2] and [3]." << std::endl;
		}
	}




	return 0;
}








