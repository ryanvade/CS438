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
	this->initial->hv = 1.0;
	open.push(this->initial);
	closed.insert(this->initial->serialize());

	this->solution = nullptr;
	Board* current;
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
}
