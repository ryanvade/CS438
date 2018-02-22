/*
* SearchAlgorithm.h
*
* By Ryan Owens
*
* For CS438
*
* Created on 02/13/2018
*
* State Tree searcher interface
*/
#include <set>
#include <string>
#include <stack>
#include "Board.h"

// enable for debugging
//#define DEBUG true
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

