/*
* heuristics.h
*
* By Ryan Owens
*
* For CS438
*
* Created on 03/09/2018
*
* Used to calculate heuristics for a Reversi Board
*/
#pragma once
#include "Board.h"

// Reference:
// https://courses.cs.washington.edu/courses/cse573/04au/Project/mini1/RUSSIA/Final_Paper.pdf

bool validIndex(int x, int y) { return x < 8 && x >= 0 && y < 8 && y >= 0; }

bool isValidMove(Color color, state_t board, int x, int y) {
  if (board->m[x][y] != EMPTY)
    return false;
  Color opposite = color * -1;
  // Check if 'Up' contains the opposite color
  int cx = x - 1;
  int cy = y;
  while (validIndex(cx, cy) && board->m[cx][cy] == opposite) {
    cx--;
  }
  if (cx != x - 1 && board->m[cx][cy] == color) {
    return true;
  }

  // Check if 'Down' contains the opposite color
  cx = x + 1;
  cy = y;
  while (validIndex(cx, cy) && board->m[cx][cy] == opposite) {
    cx++;
  }
  if (cx != x + 1 && board->m[cx][cy] == color) {
    return true;
  }

  // Check if 'Left' contains the opposite color
  cx = x;
  cy = y - 1;
  while (validIndex(cx, cy) && board->m[cx][cy] == opposite) {
    cy--;
  }
  if (cy != y - 1 && board->m[cx][cy] == color) {
    return true;
  }

  // Check if 'Right' contains the opposite color
  cx = x;
  cy = y + 1;
  while (validIndex(cx, cy) && board->m[cx][cy] == opposite) {
    cx++;
  }
  if (cx != y + 1 && board->m[cx][cy] == color) {
    return true;
  }
  return false;
}

int countOfValidMoves(Color color, state_t board) {
  int count = 0;
  for (size_t i = 0; i < 8; i++) {
    for (size_t j = 0; j < 8; j++) {
      if (isValidMove(color, board, i, j)) {
        count++;
      }
    }
  }
  return count;
}

double heuristic(Color current, state_t board) {
	int color_utility = 0, opp_utility = 0;
	int color_front_count = 0, opp_front_count = 0;
	int dx, dy;
  int color_corner_count = 0, opp_corner_count = 0;
  int color_corner_adjacent_count = 0, color_opp_corner_adjacent_count = 0;

  double coinParity = 0.0;
  double cornerEmphasis = 0.0;
  double cornerAdjacencyEmphasis = 0.0;
  double mobility = 0.0;
  double front = 0.0;
  double stability = 0.0;

  Color color = board->turn;
  Color opp_color = color * -1;

  int color_move_count = countOfValidMoves(color, board);
  int opp_move_count = countOfValidMoves(opp_color, board);

  if (color_move_count > opp_move_count) {
    mobility = (100.0 * color_move_count) / (color_move_count + opp_move_count);
  } else if (color_move_count < opp_move_count) {
    mobility = -(100.0 * opp_move_count) / (color_move_count + opp_move_count);
  }

  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 8; j++) {
      if (board->m[i][j] == color) {
        stability += staticScores[i][j];
        color_utility++;
      } else if (board->m[i][j] == opp_color) {
        stability -= staticScores[i][j];
        opp_utility++;
      }
      if (board->m[i][j] != EMPTY) {
        for (int k = 0; k < 8; k++) {
          dx = i + distance_rotations_in_X[k];
          dy = j + distance_rotations_in_Y[k];
          if (validIndex(dx, dy) && board->m[dx][dy] == EMPTY) {
            if (board->m[i][j] == color)
              color_front_count++;
            else
              opp_front_count++;
            break;
          }
        }
      }
    }

  if (color_utility > opp_utility) {
    coinParity = (100.0 * color_utility) / (color_utility + opp_utility);
  } else if (color_utility < opp_utility) {
    coinParity = -(100.0 * opp_utility) / (color_utility + opp_utility);
  }

  if (color_front_count > opp_front_count) {
    front =
        -(100.0 * color_front_count) / (color_front_count + opp_front_count);
  } else if (color_front_count < opp_front_count) {
    front = (100.0 * opp_front_count) / (color_front_count + opp_front_count);
  }

  if (board->m[0][0] == color) {
    color_corner_count++;
  } else if (board->m[0][0] == opp_color) {
    opp_corner_count++;
  }
  if (board->m[0][7] == color) {
    color_corner_count++;
  } else if (board->m[0][7] == opp_color) {
    opp_corner_count++;
  }
  if (board->m[7][0] == color) {
    color_corner_count++;
  } else if (board->m[7][0] == opp_color) {
    opp_corner_count++;
  }
  if (board->m[7][7] == color) {
    color_corner_count++;
  } else if (board->m[7][7] == opp_color) {
    opp_corner_count++;
  }
  cornerEmphasis = 25 * (color_corner_count - opp_corner_count);

  if (board->m[0][0] == EMPTY) {
    if (board->m[0][1] == color) {
      color_corner_adjacent_count++;
    } else if (board->m[0][1] == opp_color) {
      color_opp_corner_adjacent_count++;
    }
    if (board->m[1][1] == color) {
      color_corner_adjacent_count++;
    } else if (board->m[1][1] == opp_color) {
      color_opp_corner_adjacent_count++;
    }
    if (board->m[1][0] == color) {
      color_corner_adjacent_count++;
    } else if (board->m[1][0] == opp_color) {
      color_opp_corner_adjacent_count++;
    }
  }
  if (board->m[0][7] == EMPTY) {
    if (board->m[0][6] == color) {
      color_corner_adjacent_count++;
    } else if (board->m[0][6] == opp_color) {
      color_opp_corner_adjacent_count++;
    }
    if (board->m[1][6] == color) {
      color_corner_adjacent_count++;
    } else if (board->m[1][6] == opp_color) {
      color_opp_corner_adjacent_count++;
    }
    if (board->m[1][7] == color) {
      color_corner_adjacent_count++;
    } else if (board->m[1][7] == opp_color) {
      color_opp_corner_adjacent_count++;
    }
  }
  if (board->m[7][0] == EMPTY) {
    if (board->m[7][1] == color) {
      color_corner_adjacent_count++;
    } else if (board->m[7][1] == opp_color) {
      color_opp_corner_adjacent_count++;
    }
    if (board->m[6][1] == color) {
      color_corner_adjacent_count++;
    } else if (board->m[6][1] == opp_color) {
      color_opp_corner_adjacent_count++;
    }
    if (board->m[6][0] == color) {
      color_corner_adjacent_count++;
    } else if (board->m[6][0] == opp_color) {
      color_opp_corner_adjacent_count++;
    }
  }
  if (board->m[7][7] == EMPTY) {
    if (board->m[6][7] == color) {
      color_corner_adjacent_count++;
    } else if (board->m[6][7] == opp_color) {
      color_opp_corner_adjacent_count++;
    }
    if (board->m[6][6] == color) {
      color_corner_adjacent_count++;
    } else if (board->m[6][6] == opp_color) {
      color_opp_corner_adjacent_count++;
    }
    if (board->m[7][6] == color) {
      color_corner_adjacent_count++;
    } else if (board->m[7][6] == opp_color) {
      color_opp_corner_adjacent_count++;
    }
  }
  cornerAdjacencyEmphasis =
      -12.5 * (color_corner_adjacent_count - color_opp_corner_adjacent_count);
  return (10 * coinParity) + (600 * cornerEmphasis) +
         (200 * cornerAdjacencyEmphasis) + (100 * mobility) + (90 * front) +
         (30 * stability);
}
