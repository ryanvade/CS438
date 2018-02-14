#include "AStarSearcher.h"



AStarSearcher::AStarSearcher(int size)
{
	this->size = size;
	this->initial = nullptr;
}


AStarSearcher::~AStarSearcher()
{
	delete(this->initial);
	this->initial = nullptr;
}

void AStarSearcher::solve()
{

}

void AStarSearcher::createBoard()
{
	this->initial = new Board(this->size);
}

void AStarSearcher::printResults()
{
}
