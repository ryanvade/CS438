#pragma once
#include "SearchAlgorithm.h"
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

