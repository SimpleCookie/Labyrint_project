#include "Maze.h"
#include "Inputs.h"
#include "Arg_handles.h"
#include <getopt.h> // includes the getopt command for input flags
#include <stdio.h>  /* for printf */
#include <stdlib.h> // for EXIT_FAILURE and EXIT_SUCCESS
#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>



int main(int argc, char **argv)
{
	// object for the class Maze
	Maze labyrinth; 
	// FileName is the name to print the maze to
	std::string FileName = "";
	// CheckFlag is to check if -b is called
	bool Printing = false, CreateMaze = false, Solving = false, CheckFlag = false;
	// Version number
	std::string Version = "1.0.1";
	// Initializing values for row and col
	int c, col(3), row(3);
	int digit_optind = 0;

	while (1) {
		int this_option_optind = optind ? optind : 1;
		int option_index = 0;
		// Flags for input, colon equals argument taken
		c = getopt_long(argc, argv, "vhpbs:c:r:i:o:",long_options, &option_index);
		if (c == -1)
			break;

		switch (c) {
			case 'v': // Version
				std::cout << "Version: " << Version << std::endl;
				//printf("Version: %s\n", Version.c_str());
				return 1;
				break;

			case 'h': // Help
				/*printf("\n\tProgram supports following commands:\n");
				printf("\033[1;32m--version \t| -v\033[0m \t- prints the current version\n");
				printf("\033[1;32m--help \t\t| -h\033[0m \t- Lists all possible commands\n");
				printf("\033[1;32m--size \t\t| -s\033[0m (NxN size) - Generates a labyrinth with size NxN\n");
				printf("\033[1;32m--columns \t| -c\033[0m (W-width) \t- defines width of the labyrint to be generated\n");
				printf("\033[1;32m--rows \t\t| -r\033[0m (H-height) - defines height of the labyrint to be generated\n");
				printf("\033[1;32m--input \t| -i\033[0m (File) \t- Use a input file instead of generating a maze\n");
				printf("\033[1;32m--output \t| -o\033[0m (File) \t- Print the labyrint to a file\n");
				printf("\033[1;32m--check \t| -b\033[0m \t- Check whether there's a solution or not\n");
				printf("\033[1;32m--path \t\t| -p\033[0m \t- Find the exit\n\n");*/		
				std::cout << std::endl << "\tProgram supports following commands:" << std::endl;
				std::cout << "\033[1;32m--version \t| -v\033[0m \t- prints the current version" << std::endl;
				std::cout << "\033[1;32m--help \t\t| -h\033[0m \t- Lists all possible commands" << std::endl;
				std::cout << "\033[1;32m--size \t\t| -s\033[0m (NxN size) - Generates a labyrinth with size NxN" << std::endl;
				std::cout << "\033[1;32m--columns \t| -c\033[0m (W-width) \t- defines width of the labyrint to be generated" << std::endl;
				std::cout << "\033[1;32m--rows \t\t| -r\033[0m (H-height) - defines height of the labyrint to be generated" << std::endl;
				std::cout << "\033[1;32m--input \t| -i\033[0m (File) \t- Use a input file instead of generating a maze" << std::endl;
				std::cout << "\033[1;32m--output \t| -o\033[0m (File) \t- Print the labyrint to a file" << std::endl;
				std::cout << "\033[1;32m--check \t| -b\033[0m \t- Check whether there's a solution or not" << std::endl;
				std::cout << "\033[1;32m--path \t\t| -p\033[0m \t- Find the exit" << std::endl << std::endl;
				return 1;
				break;

			case 's': // Size NxN
				row = col = Check_valid_size(optarg);
				if (col == 0 || row == 0){  
					std::cout << "Enter a valid number (greater than 3) to represent the size of the maze" << std::endl;
					break;
				}
				CreateMaze = true;
				Printing = true;
				break;

			case 'c': // Columns
				col = Check_valid_size(optarg);
				if (col == 0){
					std::cout << "Enter a valid number (greater than 3) to represent the width of the maze" << std::endl;
					break; 
				}
				CreateMaze = true;
				Printing = true;
				break;

			case 'r': // Rows
				row = Check_valid_size(optarg);
				if (row == 0){
					std::cout << "Enter a valid number (greater than 3) to represent the height of the maze" << std::endl;
					break;
				}
				CreateMaze = true;
				Printing = true;
				break;

			case 'i': // Input file
				labyrinth.Read_file(optarg);
				Printing = true;
				break;

			case 'o': // output file
				FileName = optarg;
				break;

			case 'b': // Check solution
				CheckFlag = true;
				break;

			case 'p': // print solution path
				Solving = true;
				break;

			case '?':
				std::cout << "Type --h for info" << std::endl;
				//printf("Type --h for info\n");
				break;

			default:
				std::cout << "character " << c << " is not a valid choice" << std::endl << "Enter -h for help" << std::endl;
				//printf("character %c is not a valid choice\nEnter -h for help\n", c);
			}
	}
	if (optind < argc) {
			printf("non-option ARGV-elements: ");
			while (optind < argc)
					printf("%s ", argv[optind++]);
			printf("\n");
	}


	//std::ofstream outfile(FileName.c_str());
	std::ofstream outfile(FileName);
	// if file is open, write to file otherwise write to console
	std::ostream &out= (!outfile.is_open()? std::cout : outfile);
	// Check if file failed to open
	if((FileName != "") && (!outfile.is_open())){
		std::cerr << "File failed to open." << std::endl;
		return EXIT_FAILURE;
	} 
	// CheckFlag sets to true if -b is called
	if (CreateMaze)
		labyrinth.Create_maze(col, row);

	if (CheckFlag){
		if(labyrinth.Solve())
			out << "Maze Solved.\n";
		else
			out << "Maze could not be solved\n";
		if(outfile.is_open())
			outfile.close();
		return EXIT_SUCCESS;
	}
		if(outfile.is_open())
			outfile.close();


	if (Solving)
		labyrinth.Solve();
	if (Printing)
		labyrinth.Print_maze(FileName);

	return EXIT_SUCCESS;
}