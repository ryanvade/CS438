#pragma once
#include <queue>
#include <vector>
#include <functional>
#include <memory>
#include "SearchAlgorithm.h"
class BoardComparator
{
public:
	int operator() (Board* p1, Board* p2)
	{
		return p1->fv < p2->fv;
	}
};


class AStarSearcher :
	public SearchAlgorithm
{
public:
	AStarSearcher(int size);
	~AStarSearcher();
	void solve();
	void createBoard();
	void printResults();
};

