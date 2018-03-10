#pragma once
#include "Board.h"

// Reference: https://courses.cs.washington.edu/courses/cse573/04au/Project/mini1/RUSSIA/Final_Paper.pdf

bool isValidMove(Color color, state_t board, int x, int y) {

}

int countOfValidMoves(Color color, state_t board) {
	int count = 0;
	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; i < 8; i++)
		{
			if (isValidMove(color, board, i, j)) {
				count++;
			}
		}
	}
	return count;
}

double heuristic(Color current, state_t board) {
	int red_score = 0, black_score = 0;
	int red_front_count = 0, black_front_count = 0;
	int red_squares = 0, black_squares = 0;
	int red_corners = 0, black_corners = 0;
	int red_corner_adjacent = 0, black_corner_adjacent = 0;
	int red_move_count = 0, black_move_count = 0;

	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			// Calculate weights from static scores
			if (board->m[i][j] == RED) {
				red_score += staticScores[i][j];
				red_squares++;
			}
			else if (board->m[i][j] == BLACK) {
				black_score += staticScores[i][j];
				black_squares++;
			}

			// Font Calculations
			if (board->m[i][j] != EMPTY) {
				// Top Left of current
				if (i - 1 > 0 && j - 1 > 0) {
					if (board->m[i - 1][j - 1] == RED) {
						red_front_count++;
					}
					else if (board->m[i - 1][j - 1] == BLACK) {
						black_front_count++;
					}
				}

				// Top Of Current
				if (i - 1 > 0) {
					if (board->m[i - 1][j] == RED) {
						red_front_count++;
					}
					else if (board->m[i - 1][j] == BLACK) {
						black_front_count++;
					}
				}
				// Top Right of current
				if (i - 1 > 0 && j + 1 < 8) {
					if (board->m[i - 1][j + 1] == RED) {
						red_front_count++;
					}
					else if (board->m[i - 1][j + 1] == BLACK) {
						black_front_count++;
					}
				}
				// Right of Current
				if (j + 1 < 8) {
					if (board->m[i][j + 1] == RED) {
						red_front_count++;
					}
					else if (board->m[i][j + 1] == BLACK) {
						black_front_count++;
					}
				}
				// Bottom Right of Current
				if (i + 1 < 8 && j + 1 < 8) {
					if (board->m[i +  1][j + 1] == RED) {
						red_front_count++;
					}
					else if (board->m[i + 1][j + 1] == BLACK) {
						black_front_count++;
					}
				}
				// Bottom of Current
				if (j + 1 < 8) {
					if (board->m[i][j + 1] == RED) {
						red_front_count++;
					}
					else if (board->m[i][j + 1] == BLACK) {
						black_front_count++;
					}
				}
				// Bottom Left of current {
				if (i - 1 > 0 && j + 1 < 8) {
					if (board->m[i][j] == RED) {
						red_front_count++;
					}
					else if (board->m[i][j] == BLACK) {
						black_front_count++;
					}
				}
				// Left of Current
				if (j - 1 > 0) {
					if (board->m[i][j - 1] == RED) {
						red_front_count++;
					}
					else if (board->m[i][j - 1] == BLACK) {
						black_front_count++;
					}
				}
			}
		}
	}

	// Corner Counts
	// Top Left
	if (board->m[0][0] == RED) {
		red_corners++;
	}
	else if (board->m[0][0] == BLACK) {
		black_corners++;
	}
	// Top Right
	if (board->m[0][7] == RED) {
		red_corners++;
	}
	else if (board->m[0][7] == BLACK) {
		black_corners++;
	}
	// Bottom Left
	if (board->m[7][0] == RED) {
		red_corners++;
	}
	else if (board->m[7][0] == BLACK) {
		black_corners++;
	}
	// Bottom Right
	if (board->m[7][7] == RED) {
		red_corners++;
	}
	else if (board->m[7][7] == BLACK) {
		black_corners++;
	}

	// Corner Adjacencies
	// Top Left
	if (board->m[0][0] == EMPTY) {
		if (board->m[0][1] == RED) {
			red_corner_adjacent++;
		}
		else if (board->m[0][1] == BLACK) {
			black_corner_adjacent++;
		}

		if (board->m[1][1] == RED) {
			red_corner_adjacent++;

		}
		else if (board->m[1][1] == BLACK) {
			black_corner_adjacent++;

		}

		if (board->m[1][0] == RED) {
			red_corner_adjacent++;

		}
		else if (board->m[1][0] == BLACK) {
			black_corner_adjacent++;

		}
	}

	// Top Right
	if (board->m[0][7] == EMPTY) {
		if (board->m[0][6] == RED) {
			red_corner_adjacent++;

		}
		else if (board->m[0][6] == BLACK) {
			black_corner_adjacent++;

		}

		if (board->m[1][6] == RED) {
			red_corner_adjacent++;

		}
		else if (board->m[1][6] == BLACK) {
			black_corner_adjacent++;

		}

		if (board->m[1][7] == RED) {
			red_corner_adjacent++;

		}
		else if (board->m[1][7] == BLACK) {
			black_corner_adjacent++;

		}
	}

	// Bottom Left
	if (board->m[7][0] == EMPTY) {
		if (board->m[6][0] == RED) {
			red_corner_adjacent++;

		}
		else if (board->m[6][0] == BLACK) {
			black_corner_adjacent++;

		}

		if (board->m[6][1] == RED) {
			red_corner_adjacent++;

		}
		else if (board->m[6][1] == BLACK) {
			black_corner_adjacent++;

		}

		if (board->m[7][1] == RED) {
			red_corner_adjacent++;

		}
		else if (board->m[7][1] == BLACK) {
			black_corner_adjacent++;

		}
	}

	// Bottom Right
	if (board->m[7][7] == EMPTY) {
		if (board->m[6][7] == RED) {
			red_corner_adjacent++;
		}
		else if (board->m[6][7] == BLACK) {
			black_corner_adjacent++;

		}

		if (board->m[6][6] == RED) {
			red_corner_adjacent++;
		}
		else if (board->m[6][6] == BLACK) {
			black_corner_adjacent++;

		}

		if (board->m[7][6] == RED) {
			red_corner_adjacent++;
		}
		else if (board->m[7][6] == BLACK) {
			black_corner_adjacent++;

		}
	}
	red_move_count = countOfValidMoves(RED, board);
	black_move_count = countOfValidMoves(BLACK, board);
	
	double p = 0.0;
	double d = 0.0;
	double f = 0.0;
	double c = 0.0;
	double l = 0.0;
	double m = 0.0;

	if (current == RED) {

		if (red_squares > black_squares) {
			p = (100.0 * red_squares) / (red_squares + black_squares);

		}
		else if (red_squares < black_squares) {
			p = -(100.0 * black_squares) / (red_squares + black_squares);
		}

		if (red_front_count > black_front_count)

			f = -(100.0 * red_front_count) / (red_front_count + black_front_count);

		else if (red_front_count < black_front_count)

			f = (100.0 * black_front_count) / (red_front_count + black_front_count);


		c = 25.0 * (red_corners - black_corners);

		l = -12.5 * (red_corner_adjacent - black_corner_adjacent);

		if (red_move_count > black_move_count) {

			m = (100.0 * red_corner_adjacent) / (red_corner_adjacent + black_corner_adjacent);
		}
		else if (red_move_count < black_move_count) {
			m = -(100.0 * black_corner_adjacent) / (red_corner_adjacent + black_corner_adjacent);

		}

		d = (red_score - black_score);
	}
	else {
		if (black_squares > red_squares) {
			p = (100.0 * black_squares) / (black_squares + red_squares);

		}
		else if (black_squares < red_squares) {
			p = -(100.0 * red_squares) / (black_squares + red_squares);
		}

		if (black_front_count > red_front_count)

			f = -(100.0 * black_front_count) / (black_front_count + red_front_count);

		else if (black_front_count < red_front_count)

			f = (100.0 * red_front_count) / (black_front_count + red_front_count);


		c = 25.0 * (black_corners - red_corners);

		l = -12.5 * (black_corner_adjacent - red_corner_adjacent);

		if (black_move_count > red_move_count) {

			m = (100.0 * black_corner_adjacent) / (black_corner_adjacent + red_corner_adjacent);
		}
		else if (black_move_count < red_move_count) {
			m = -(100.0 * red_corner_adjacent) / (black_corner_adjacent + red_corner_adjacent);

		}

		d = (black_score - red_score);
	}

	return (10 * p) + (801.724 * c) + (382.026 * l) + (78.922 * m) + (74.396 * f) + (10 * d);
}