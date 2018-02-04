#pragma once
#include "Board.h"
#include <vector>

class State
{
public:
	State(Board* result);
	State(Board* result, State* parent);
	bool operator==(const State other);
	bool operator<(const State& A);
	virtual ~State();
	int cost;
	State* parent;
	std::vector<State*> children;
	Board* result;
};

