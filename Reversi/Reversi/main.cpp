/*
* main.cpp
*
* By Ryan Owens
*
* For CS438
*
* Created on 03/09/2018
*
* Calculates a 'move' for Reversi
*/
#include "Board.h"
#include "gamecomm.h"
#include "heuristics.h"
#include <fstream>
#include <iostream>
#include <time.h>

using namespace std;

bool pass = false;
const int maxsucc = 50;
const int maxturn = 1;
const int minturn = -1;
const int blank = 0;
const int VS = -1000000;
const int VL = 1000000;
int nodecount = 0;
#define DEBUG false

state_t best = NULL;

// Check if there are any possible moves
bool isterminal(state_t board) {
  return countOfValidMoves(board->turn, board) == 0;
}

// Get a 'score' for a board
int eval(state_t board) { return heuristic(board->turn, board); }

// Print the board to std::out
void printBoard(state_t board) {
  for (size_t i = 0; i < 8; i++) {
    for (size_t j = 0; j < 8; j++) {
      std::cout << board->m[i][j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << "r: " << board->r << " "
            << "c: " << board->c << std::endl;
}

void flipSpacesAround(state_t nBoard, int x, int y, Color turn) {
  nBoard->m[x][y] = turn;
  // All pieces straight up
  for (size_t i = 0; i < y; i++) {
    if (nBoard->m[x][i] == turn) {
      for (size_t j = i + 1; j < y; j++) {
        nBoard->m[x][j] = turn;
      }
      break;
    }
  }
  // All pieces straight down
  for (size_t i = 7; i > y; i--) {
    if (nBoard->m[x][i] == turn) {
      for (size_t j = i - 1; j > y; j--) {
        nBoard->m[x][j] = turn;
      }
      break;
    }
  }
  // All pieces straight left
  for (size_t i = 0; i < x; i++) {
    if (nBoard->m[i][y] == turn) {
      for (size_t j = i + 1; j < x; j++) {
        nBoard->m[j][y] = turn;
      }
      break;
    }
  }
  // All pieces straight right
  for (size_t i = 7; i > x; i--) {
    if (nBoard->m[i][y] == turn) {
      for (size_t j = i - 1; j > x; j--) {
        nBoard->m[j][y] = turn;
      }
      break;
    }
  }
}

// Get all of the possible moves for the 'turn'
void expand(state_t board, state_t successors[], int &numsuccessors,
            Color turn) {
  state_t nBoard;
  Color other = (turn == 1) ? -1 : 1;
  int i = 0, x, y;
  while (i < 60 && numsuccessors < maxsucc) {
    x = places[i][0];
    y = places[i][1];
    if (isValidMove(turn, board, x, y)) {
      nBoard = new Board(board->m, 8, 8, other);
      flipSpacesAround(nBoard, x, y, turn);
      nBoard->r = x;
      nBoard->c = y;
      successors[numsuccessors] = nBoard;
      numsuccessors++;
      nBoard = nullptr;
    }
    i++;
  }
}

int max(int a, int b) { return a > b ? a : b; }

int min(int a, int b) { return a > b ? b : a; }

int alphabeta(state_t board, int maxDepth, int curDepth, int alpha, int beta) {
  nodecount++;

  // If at CUTOFF
  if (curDepth == maxDepth || isterminal(board)) {
    int UtilV = eval(board);

    return UtilV;
  }

  state_t successors[maxsucc];
  int numsuccessors = 0, turn = 0;
  // Determine whos turn it is
  if (curDepth % 2 == 0) {
    turn = maxturn;
  } else {
    turn = minturn;
  }
  // Get all of the successors
  expand(board, successors, numsuccessors, turn);

  if (turn == maxturn) {
    alpha = VS;
    for (size_t i = 0; i < numsuccessors; i++) {
      int curvalue =
          alphabeta(successors[i], maxDepth, curDepth + 1, alpha, beta);
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
  } else {
    beta = VL;
    for (size_t i = 0; i < numsuccessors; i++) {
      int curvalue =
          alphabeta(successors[i], maxDepth, curDepth + 1, alpha, beta);
      beta = min(beta, curvalue);
      if (alpha >= beta) {
        return beta;
      }
    }
    return beta;
  }
}

void main() {
  int n[8][8];
  bool gotBoard = getGameBoard(n);
  if (!gotBoard) {
    std::cerr << "Unable to get board" << std::endl;
    system("pause");
    exit(1);
  }

  state_t board = new Board(n);
  alphabeta(board, 4, 0, VS, VL);
  if (best) {
    putMove(best->r, best->c);
  } else {
    std::cerr << "Unable to find move" << std::endl;
    system("pause");
    exit(1);
  }

  /*int R, C;
  cout << " Enter row and column of move\n";
  cin >> R >> C;
  putMove(R, C);*/
}
