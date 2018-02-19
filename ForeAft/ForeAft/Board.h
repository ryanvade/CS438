
#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>
#include <math.h> 
#define RED 'R'
#define BLACK 'B'
#define OUTOFBOUNDS '#'
#define BLANK ' '
#define DEBUG false
#define C 100.0

class Board
{
public:
	Board();
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
	bool operator>(Board* rhs) const;
	float hValue();
	float hv, gv, fv;

private:
	int size;
	char** board;
	std::string serialized;
	int blank_r;
	int blank_c;
	int outOfBounds_count;

};

