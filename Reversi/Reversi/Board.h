#pragma once

#define EMPTY 0
#define RED 1
#define BLACK -1

struct Board
{
	int m[8][8];	// 1, 0, -1
	int r, c, turn;	// the move that gets to this board
	Board(int n[][8], int row = 8, int column = 8, int t = 1)
	{
		for (int k = 0; k<8; k++)
			for (int l = 0; l<8; l++)
				m[k][l] = n[k][l];
		r = row; c = column; turn = t;
	}
};

typedef Board* state_t;

typedef int Color;

// Highest Value to corners
// Lowest scores to squares adjacent to corners
// Dislike edges
// Ignore the center 4
int staticScores[8][8] = {
	{ 20, -3, 11, 8, 8, 11, -3, 20 },
	{ -3, -7, -4, 1, 1, -4, -7, -3 },
	{ 11, -4,  2, 2, 2,  2, -4, 11 },
	{  8,  1,  2, 0, 0,  2,  1,  8 },
	{  8,  1,  2, 0, 0,  2,  1,  8 },
	{ 11, -4,  2, 2, 2,  2, -4, 11 },
	{ -3, -7, -4, 1, 1, -4, -7, -3 },
	{ 20, -3, 11, 8, 8, 11, -3, 20 },
};