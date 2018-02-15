#include "DFSSearcher.h"



DFSSearcher::DFSSearcher(int size)
{
	this->size = size;
	this->initial = nullptr;
}


DFSSearcher::~DFSSearcher()
{
}

void DFSSearcher::solve()
{
	std::stack<Board*> open;
	std::set<std::string> closed;
	open.push(this->initial);
	closed.insert(this->initial->serialize());

	this->solution = nullptr;
	Board* current = nullptr;
	while (!open.empty() && this->solution == nullptr) {
		current = open.top();
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

void DFSSearcher::createBoard()
{
	this->initial = new Board(this->size);
}

void DFSSearcher::printResults()
{
}
