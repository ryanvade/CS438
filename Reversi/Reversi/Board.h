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

// Array of points to check in decreasing point value order
int places[60][2] = {
	// Corners
	{ 0, 0 },
	{ 0, 7 },
	{ 7, 7 },
	{ 7, 0 },
	// Value of 11
	{ 2, 0 },
	{ 5, 0 },
	{ 7, 2 },
	{ 7, 5 },
	{ 2, 7 },
	{ 5, 7 },
	{ 0, 2 },
	{ 0, 5 },
	// Value of 8
	{ 3, 0 },
	{ 4, 0 },
	{ 7, 3 },
	{ 7, 4 },
	{ 3, 7 },
	{ 4, 7 },
	{ 0, 3 },
	{ 0, 4 },
	// Value of 2
	{ 2, 2 },
	{ 3, 2 },
	{ 4, 2 },
	{ 5, 2 },
	{ 5, 3 },
	{ 5, 4 },
	{ 5, 5 },
	{ 4, 5 },
	{ 3, 5 },
	{ 2, 5 },
	{ 2, 4 },
	{ 2, 3 },
	// Value of 1
	{ 3, 1 },
	{ 4, 1 },
	{ 6, 3 },
	{ 6, 4 },
	{ 3, 6 },
	{ 4, 6 },
	{ 1, 3 },
	{ 1, 2 },
	// Value of -3
	{ 1, 0 },
	{ 6, 0 },
	{ 0, 1 },
	{ 7, 1 },
	{ 0, 6 },
	{ 7, 6 },
	{ 1, 7 },
	{ 6, 7 },
	// Value of -4
	{ 2, 1 },
	{ 5, 1 },
	{ 1, 2 },
	{ 6, 2 },
	{ 1, 5 },
	{ 6, 5 },
	{ 2, 6 },
	{ 5, 6 },
	// Values of -7
	{ 1, 1 },
	{ 6, 1 },
	{ 1, 6 },
	{ 6, 6 }
};