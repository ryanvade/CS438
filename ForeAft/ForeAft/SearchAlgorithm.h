#include <set>
#include <string>
#include "Board.h"

#define DEBUG true
#pragma once
class SearchAlgorithm
{
public:
	virtual void solve() = 0;
	virtual void printResults() = 0;
	virtual void createBoard() = 0;
	virtual ~SearchAlgorithm() {}
protected:
	int size;
	Board* initial;
	Board* solution;
	std::set<std::string> closed;
};

