#include "BFSSearcher.h"



BFSSearcher::BFSSearcher(int size)
{
	this->size = size;
	this->initial = nullptr;
}


BFSSearcher::~BFSSearcher()
{
	delete(this->initial);
	this->initial = nullptr;
}

void BFSSearcher::solve()
{
	std::queue<Board*> open;
	std::set<std::string> closed;
	open.push(this->initial);
	closed.insert(this->initial->serialize());

	this->solution = nullptr;
	Board* current = nullptr;
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
}
