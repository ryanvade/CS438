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
	virtual ~Solver();
private:
	State * initial, * solution;
	bool solved(State* current);
	State* left(Board* board, int r, int c);
	State* right(Board* board, int r, int c);
	State* up(Board* board, int r, int c);
	State* down(Board* board, int r, int c);
	std::vector<State*> calculateMoves(State* current);
};

