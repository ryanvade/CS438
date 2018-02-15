#pragma once
#include <stack>
#include <memory>
#include "SearchAlgorithm.h"
#include "Board.h"

class DFSSearcher :
	public SearchAlgorithm
{
public:
	DFSSearcher(int size);
	~DFSSearcher();
	void solve();
	void createBoard();
	void printResults();
};

