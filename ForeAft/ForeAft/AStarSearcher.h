/*
* AStarSearch.h
*
* By Ryan Owens
*
* For CS438
*
* Created on 02/13/2018
*
* 
*/
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

