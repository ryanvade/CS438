/*
* Main.cpp
*
* By Ryan Owens
*
* For CS438
*
* Created on 02/13/2018
*
* Performs ForeAft State Tree search
*/

/*
 * Performance:
 * DFS/BFS/A* 5x5 works well
 * A* 7x7 uses 2GB ram but runs in less than 10 sec
 * A* 9x9 and 11x11 do not find solutions
 */
#include <iostream>
#include <fstream>
#include <string>
#include "SearchAlgorithm.h"
#include "AStarSearcher.h"
#include "BFSSearcher.h"
#include "DFSSearcher.h"

int main(int argc, char** argv) {

	do {
		// ask for a search method
		char search = ' ';
		do {
			std::cout << "Select a search method: " << std::endl;
			std::cout << "\t1) Depth First Search" << std::endl;
			std::cout << "\t2) Breadth First Search" << std::endl;
			std::cout << "\t3) A* Search" << std::endl;
			std::cout << "\t4) Quit" << std::endl;
			std::cin >> search;
		} while (search != '1' && search != '2' && search != '3' && search != '4');

		if (search == '4') {
			break;
		}
		std::string size = " ";
		int s;
		std::string sizes = "";
		SearchAlgorithm* sa;
		if (search == '1') {
			// ask for a board size
			do {
				std::cout << "Enter puzzle size for DFS (5 only): " << std::endl;
				std::cin >> size;
			} while (size != "5" /*&& size != "7" */);
			s = std::stoi(size);
			sa = new DFSSearcher(s);
		}
		else if (search == '2') {
			// ask for a board size
			do {
				std::cout << "Enter a puzzle size for BFS (5 only):  " << std::endl;
				std::cin >> size;
			} while (size != "5");
			s = std::stoi(size);
			sa = new BFSSearcher(s);
		}
		else if (search == '3') {
			// ask for a board size
			do {
				std::cout << "Enter a puzzle size for A* (5, 7, 9, or 11):  " << std::endl;
				std::cin >> size;
			} while (size != "5" && size != "7" && size != "9" && size != "11");
			s = std::stoi(size);
			sa = new AStarSearcher(s);
		}
		else {
			return 0;
		}
		// create board
		sa->createBoard();
		// solve
		sa->solve();
		// print results
		sa->printResults();
		// cleanup
		delete(sa);
	} while (true);
	
	return 0;
}