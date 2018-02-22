/*
* BFSSearcher.h
*
* By Ryan Owens
*
* For CS438
*
* Created on 02/13/2018
*
*
*/
#include <queue>
#include <memory>

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

