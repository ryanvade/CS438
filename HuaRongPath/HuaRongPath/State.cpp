/*
* State.cpp
*
* Defines a 'state' of the HuaRong Game Board
*
* CS438 HW2
*
* Updated on 02/05/2018
*
* Created by Ryan Owens
*/

#include "State.h"

State::State(Board* result)
{
	this->parent = nullptr;
	this->result = result;
	this->cost = 0;
}

State::State(Board* result, State* parent)
{
	this->parent = parent;
	this->result = result;
	this->cost = parent->cost + 1;
}

bool State::operator==(const State other)
{
	for (size_t r = 0; r < 5; r++)
	{
		for (size_t c = 0; c < 4; c++)
		{
			if (other.result->board[r][c] != this->result->board[r][c]) {
				return false;
			}
		}
	}
	return true;
}

bool State::operator<(const State& A) {
	return this->cost < A.cost;
}


State::~State()
{
	if (result != nullptr) {
		//delete(result);
		//result == nullptr;
	}

	if (parent != nullptr) {
		//delete(parent);
	}

	/*for (size_t i = 0; i < this->children.size(); i++)
	{
		if (children.at(i) != nullptr) {
			delete(children.at(i));
			children.at(i) = nullptr;
		}
	}*/
}
