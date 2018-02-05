/*
* Main.cpp
*
* Attempts to solve HuaRong Game boards
*
* CS438 HW2
*
* Updated on 02/05/2018
*
* Created by Ryan Owens
*/


/*
 * Performance Notes:
 *		Each of the input files (HR4-HR138 will) complete within approx. 5 minutes (HR138 taking the longest).
 *      Both HR4 and HR10 find solutions within seconds.
 *      However, only HR4 and HR10 will find solutions with both DFS and BFS.
 *      The others run but do not find solutions. 
 *      They have been tested on an i5-4690K with 16GB ram. 
 *      I decided not to include any limits to the number of states. 
 *      As mentioned in Solver.cpp, I suspect that my program is missing
 *      some actions based on how I'm defining the board. 
 *      The larger input files can use > 40MB ram. 
 *      
 *      Do not run HR81 with BFS, it is cursed with my program.
 */

#include "Board.h"
#include "Solver.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include "main.h"

void backTrack(State* success, std::string outfilename, int choice);

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
		input = input;
		
		board = new Board();
		// read file into board
		bool read = board->instantiate(input + ".in");
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
		if (solved) {
			std::cout << "Solved!" << std::endl;
			backTrack(solver->solution, input + ".out", choice);
		}
		else {
			std::cout << "Could not find a solution." << std::endl;
		}
		delete(solver);
	// repeat or quit
	} while (input != "Q" && input != "Quit");
	
	//if (board != nullptr) delete(board);
	//if (solver != nullptr) delete(solver);

	return 0;
}

void backTrack(State* success, std::string outfilename, int choice) {
	std::stack<State*> track;
	State* curr = success;
	track.push(curr);
	while (curr != nullptr) {
		track.push(curr);
		curr = curr->parent;
	}
		std::ofstream out(outfilename);
		if (!out.is_open()) {
			std::cerr << "Unable to open " << outfilename << std::endl;
			exit(1);
		}
		while (!track.empty()) {
			curr = track.top();
			track.pop();
			curr->result->print(out);
			if (DEBUG) {
					curr->result->print(std::cout);
					std::cout << std::endl;
			}
			out << std::endl;
		}
		if (choice == 1) {
			out << "BFS" << std::endl;
		}
		else {
			out << "DFS" << std::endl;
		}
		out.close();

	
}