#pragma once
#include "SearchAlgorithm.h"
class BFSSearcher :
	public SearchAlgorithm
{
public:
	BFSSearcher(int size);
	~BFSSearcher();
	void solve();
	void createBoard();
	void printResults();
};

