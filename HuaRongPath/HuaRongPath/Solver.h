/*
* Solver.h
*
* Implements a HuaRong Search Tree solver
*
* CS438 HW2
*
* Updated on 02/05/2018
*
* Created by Ryan Owens
*/
#pragma once
#include "Board.h"
#include "State.h"
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <algorithm>

#define DEBUG true


class Solver
{
public:
	Solver(Board* board);
	bool dfs();
	bool bfs();
	State* solution;
	virtual ~Solver();
private:
	State * initial;
	bool solved(State* current);
	std::vector<State*> calculateMoves(State* current);
};

