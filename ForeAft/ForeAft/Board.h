/*
* Board.h
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
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>
#include <math.h> 
#include <map>
#define RED 'R'
#define BLACK 'B'
#define OUTOFBOUNDS '#'
#define BLANK '0'
#define C 1000.0

// Enable for debugging
//#define DEBUG true

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
	double hValue();
	double hv, gv, fv;

private:
	int size;
	char** board;
	std::string serialized;
	int blank_r;
	int blank_c;
	int outOfBounds_count;
	std::map<int, int> black_max, red_max;
};

