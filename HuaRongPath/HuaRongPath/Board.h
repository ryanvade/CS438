#pragma once
#include <fstream>
#include <iostream>
class Board
{
public:
	Board();
	Board(Board* b);
	virtual ~Board();
	bool instantiate(std::string filename);
	void print(std::ostream& stream);
	bool isSingle(int r, int c);
	bool isLeftOfHorizontalTwo(int r, int c);
	bool isTopOfVerticalTwo(int r, int c);
	bool isTopLeftOfQuad(int r, int c);
	char board[5][4];
};

