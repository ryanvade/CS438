/*
* BFSSearcher.cpp
*
* By Ryan Owens
*
* For CS438
*
* Created on 02/13/2018
*
* Performs an BFS Search
*/
#include "BFSSearcher.h"

BFSSearcher::BFSSearcher(int size)
{
	this->size = size;
	this->initial = nullptr;
}


BFSSearcher::~BFSSearcher()
{
}

void BFSSearcher::solve()
{
	std::queue<Board*> open;
	std::set<std::string> closed;
	open.push(this->initial);
	closed.insert(this->initial->serialize());

	this->solution = nullptr;
	Board* current;
	while (!open.empty() && this->solution == nullptr) {
		current = open.front();
		open.pop();

		if (current->solved()) {
			this->solution = current;
			break;
		}
		else {
			std::vector<Board*> moves = current->getMoves();
			for (auto iter = moves.begin(); iter != moves.end(); iter++) {
				Board* move = *iter;
				if (closed.find(move->serialize()) == closed.end()) {
					move->gv = (current->gv) + 1.0;
					move->fv = move->hValue() + move->gv;

					closed.insert(move->serialize());
					open.push(move);
				}
				else {
					delete(move);
				}
			}
		}
	}
}

void BFSSearcher::createBoard()
{
	this->initial = new Board(this->size);
}

void BFSSearcher::printResults()
{
	if (this->solution == nullptr) {
		std::cout << "No Solution" << std::endl;
	}

	std::stack<Board*> boards;
	Board* current = this->solution;
	while (current != nullptr) {
		boards.push(current);
		current = current->parent;
	}
	current = nullptr;
	int steps = boards.size();
	std::ofstream out;
	std::string filename = "BFS" + std::to_string(this->size) + ".out";
	out.open(filename, std::ofstream::out);
	if (!out.is_open()) {
		std::cerr << "Could not open file: " << filename << std::endl;
		exit(1);
	}

	while (!boards.empty()) {
		current = boards.top();
		boards.pop();
		/*#ifdef DEBUG
		current->print(std::cout);
		std::cout << std::endl;
		#endif */
		current->print(out);
		out << std::endl;
	
		delete(current);
	}

		/*#ifdef DEBUG
		std::cout << steps << " steps" << std::endl;
		#endif*/
		out << steps << " steps" << std::endl;
		out.close();
	
}
