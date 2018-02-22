/*
* AStarSearcher.cpp
*
* By Ryan Owens
*
* For CS438
*
* Created on 02/13/2018
*
* Performs an A* Search
*/
#include "AStarSearcher.h"

AStarSearcher::AStarSearcher(int size)
{
	this->size = size;
	this->initial = nullptr;
}


AStarSearcher::~AStarSearcher()
{

}

void AStarSearcher::solve()
{
	std::priority_queue<Board*, std::vector<Board*>, BoardComparator> open;
	std::set<std::string> closed;
	this->initial->gv = 0;
	this->initial->fv = this->initial->hValue();
	open.push(this->initial);
	closed.insert(this->initial->serialize());

	this->solution = nullptr;
	Board* current;
	while (!open.empty() && this->solution == nullptr) {
		current = open.top();
		open.pop();
			#ifdef DEBUG
			std::cout << "Current FV: " << current->fv << std::endl;
			#endif

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

void AStarSearcher::createBoard()
{
	this->initial = new Board(this->size);
}

void AStarSearcher::printResults()
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
		std::string filename = "Best" + std::to_string(this->size) + ".out";
		out.open(filename, std::ofstream::out);
		if (!out.is_open()) {
			std::cerr << "Could not open file: " << filename << std::endl;
			exit(1);
		}

		while (!boards.empty()) {
			current = boards.top();
			boards.pop();
				#ifdef DEBUG
				current->print(std::cout);
				std::cout << std::endl;
				#endif
				current->print(out);
				out << std::endl;
			delete(current);
		}

			#ifdef DEBUG
			std::cout << steps << " steps" << std::endl;
			#endif
			out << steps << " steps" << std::endl;
			out.close();
}
