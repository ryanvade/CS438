#include <iostream>
#include <fstream>
#include <time.h>
#include "gamecomm.h"

#define EMPTY 0
#define RED 1
#define BLACK -1

using namespace std;


bool pass=false;
const int maxsucc=40;
const int maxturn=1;
const int minturn=-1;
const int blank=0;
const int VS=-1000000;
const int VL=1000000;
int nodecount = 0;

struct Board
{
	int m[8][8];	// 1, 0, -1
	int r,c, turn;	// the move that gets to this board
	Board(int n[][8],int row=8, int column=8, int t=1)
	{
		for (int k=0;k<8;k++)
			for (int l=0;l<8;l++)
				m[k][l]=n[k][l];
		r=row;c=column; turn=t;
	}
};

typedef Board* state_t;

state_t best = NULL;

// Check if there are any possible moves
bool isterminal(state_t board) {
	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			// If the space is available
			if (board->m[i][j] == EMPTY) {

			}
		}
	}
	return true;
}

// Get a 'score' for a board
int eval(state_t board) {

}

// Print the board to std::out
void printBoard(state_t board) {
	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			std::cout << board->m << " ";
		}
		std::cout << std::endl;
	}
}

// Get all of the possible moves for the 'turn'
void expand(state_t board, state_t successors[], int numsuccessors, int turn) {

}

int max(int a, int b) {
	return a > b ? a : b;
}

int min(int a, int b) {
	return a > b ? b : a;
}

int alphabeta(state_t board, int maxDepth, int curDepth, int alpha, int beta) {
	nodecount++;

	// If at CUTOFF
	if (curDepth == maxDepth || isterminal(board)) {
		int UtilV = eval(board);
		printBoard(board);
		return UtilV;
	}

	state_t successors[maxsucc];
	int numsuccessors = 0, turn = 0;
	// Determine whos turn it is
	if (curDepth % 2 == 0) {
		turn = maxturn;
	}
	else {
		turn = minturn;
	}
	// Get all of the successors
	expand(board, successors, numsuccessors, turn);

	if (turn == maxturn) {
		alpha = VS;
		for (size_t i = 0; i < numsuccessors; i++)
		{
			int curvalue = alphabeta(successors[i], maxDepth, curDepth + 1, alpha, beta);
			if (curvalue > alpha || curvalue == alpha && time(0) % 2 == 0) {
				alpha = curvalue;
				if (curDepth == 0) {
					best = successors[i];
				}
			}

			if (alpha >= beta) {
				return alpha;
			}
		}
		return alpha;
	}
	else {
		beta = VL;
		for (size_t i = 0; i < numsuccessors; i++)
		{
			int curvalue = alphabeta(successors[i], maxDepth, curDepth + 1, alpha, beta);
			beta = min(beta, curvalue);
			if (alpha >= beta) {
				return beta;
			}
		}
		return beta;
	}
}

void main()
{
	int n[8][8];
	bool gotBoard = getGameBoard(n);
	if (!gotBoard) {
		std::cerr << "Unable to get board";
		exit(1);
	}

	state_t board = new Board(n);
	alphabeta(board, 3, 0, VS, VL);	
	if (best) {
		putMove(best->r, best->c);
	}

	int R, C;
	cout << " Enter row and column of move\n";
	cin >> R >> C;
	putMove(R, C);
}