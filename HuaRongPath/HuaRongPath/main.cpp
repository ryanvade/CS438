#include "Board.h"
#include "Solver.h"
#include <iostream>
#include <fstream>
#include <string>
#include "main.h"


int main()
{
	Board* board = nullptr;
	Solver* solver = nullptr;
	std::string input = "";
	int choice = 0;
	do
	{
	// Ask for input file
		std::cout << "Please enter the name of the input file or 'Q' or 'Quit' to quit " << std::endl;
		std::cout << "Filename: ";
		std::cin >> input;
		if (input == "Q" || input == "Quit") break;
		input = input + ".in";
		
		board = new Board();
		// read file into board
		bool read = board->instantiate(input);
		if (!read) {
			std::cout << "\n Could not open file " << input << std::endl;
			delete(board);
			board = nullptr;
			continue;
		}
		if (DEBUG) {
			board->print(std::cout);
		}

	// Ask for search type
		do
		{
			std::cout << std::endl << "Searches available: " << std::endl;
			std::cout << "\t1) BFS" << std::endl;
			std::cout << "\t2) DFS" << std::endl;
			std::cout << "Please select either 1 or 2: ";
			std::cin >> choice;
		} while (choice != 1 && choice != 2);
		
	// solve using solve type
		bool solved;
		solver = new Solver(board);
		if (choice == 1) solved = solver->bfs();
		else solved = solver->dfs();
	// write steps to file
	// repeat or quit
	} while (input != "Q" && input != "Quit");
	
	if (board != nullptr) delete(board);
	if (solver != nullptr) delete(solver);

	return 0;
}