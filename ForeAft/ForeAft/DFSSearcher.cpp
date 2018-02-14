#include "DFSSearcher.h"



DFSSearcher::DFSSearcher(int size)
{
	this->size = size;
	this->initial = nullptr;
}


DFSSearcher::~DFSSearcher()
{
	delete(this->initial);
	this->initial = nullptr;
}

void DFSSearcher::solve()
{
	std::stack<Board*> open;
	open.push(this->initial);
	this->closed.clear();
	while (!open.empty()) {
		Board* current = open.top();
		open.pop();
		if (current->solved()) {
			this->solution = current;
			break;
		}

		current->children = current->getMoves();
		for (auto iter = current->children.begin(); iter != current->children.end(); iter++) {
			Board* b = *iter;
			if (b != nullptr && this->closed.find(b->serialize()) != this->closed.end()) {
				open.push(b);
			}
		}
		this->closed.emplace(current->serialize());
	}
}

void DFSSearcher::createBoard()
{
	this->initial = new Board(this->size);
}

void DFSSearcher::printResults()
{
}
