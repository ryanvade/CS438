#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#pragma once
#define RED 'R'
#define BLACK 'B'
#define OUTOFBOUNDS '#'
#define BLANK ' '
#define DEBUG false

class Board
{
public:
	Board(int size);
	Board::Board(int size, char** board);
	std::string serialize();
	bool solved();
	std::vector<Board*> getMoves();
	void print(std::ostream& out);
	void __serialize();
	Board* attemptUp(int r, int c);
	Board* attemptDown(int r, int c);
	Board* attemptLeft(int r, int c);
	Board* attemptRight(int r, int c);
	Board* attemptJumpUp(int r, int c);
	Board* attemptJumpDown(int r, int c);
	Board* attemptJumpLeft(int r, int c);
	Board* attemptJumpRight(int r, int c);
	~Board();
	Board* parent;

private:
	int size;
	char** board;
	std::string serialized;

};

