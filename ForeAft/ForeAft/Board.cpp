#include "Board.h"



Board::Board(int size)
{
	std::cout << "Board Size: " << size << std::endl;
	this->size = size;
	this->board = new char*[size];
	for (size_t i = 0; i < size; i++)
	{
		this->board[i] = new char[size];
	}

	int v_divide = (0.5 * (size + 1)) - 1;
	int h_divide = v_divide;
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			if (i < v_divide) {
				// Red Boundary
				if (j <= h_divide) {
					this->board[i][j] = RED;
				}
				else {
					this->board[i][j] = OUTOFBOUNDS;
				}
			}
			else if (i == v_divide) {
				if (j < h_divide) {
					this->board[i][j] = RED;
				}
				else if(j > h_divide){
					this->board[i][j] = BLACK;
				}
				else {
					this->board[i][j] = BLANK;
				}
			}
			else {
				// Black Boundary
				if (j >= h_divide) {
					this->board[i][j] = BLACK;
				}
				else {
					this->board[i][j] = OUTOFBOUNDS;
				}
			}
		}
	}
}

Board::Board(int size, char** board) {
	this->size = size;
	this->board = new char*[size];
	for (size_t i = 0; i < size; i++)
	{
		this->board[i] = new char[size];
	}

	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			this->board[i][j] = board[i][j];
		}
	}
}


Board::~Board()
{
	for (size_t i = 0; i < size; i++)
	{
		delete(this->board[i]);
	}
	delete(this->board);
	this->parent = nullptr;
	for each (auto iter in this->children)
	{
		delete(iter);
		iter = nullptr;
	}
}

std::string Board::serialize() {
	std::string result = "";
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			result = result + this->board[i][j];
		}
	}
	return result;
}

bool Board::solved() {
	int v_divide = (0.5 * (size + 1)) - 1;
	int h_divide = v_divide;
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			if (i < v_divide) {
				// Red Boundary
				if (j <= h_divide) {
					if (this->board[i][j] != BLACK) {
						return false;
					}
				}
				else {
					if (this->board[i][j] != OUTOFBOUNDS) {
						return false;
					}
				}
			}
			else if (i == v_divide) {
				if (j < h_divide) {
					if (this->board[i][j] != BLACK)
					{
						return false;
					}
				}
				else if (j > h_divide) {
					if (this->board[i][j] != RED) {
						return false;
					}
				}
			}
			else {
				// Black Boundary
				if (j >= h_divide) {
					if (this->board[i][j] != RED)
					{
						return false;
					}
				}
				else {
					if (this->board[i][j] != OUTOFBOUNDS) {
						return false;
					}
				}
			}
		}
	}
	return true;
}

std::vector<Board*> Board::getMoves() {
	std::vector<Board*> moves(5);
	int r = -1;
	int c = -1;
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			if (this->board[i][j] == BLANK) {
				r = i;
				c = j;
				break;
			}
		}
		if (r > -1) break;
	}
	
	Board* up = this->attemptUp(r, c);
	if (up != nullptr) {
		moves.push_back(up);
	}

	Board* down = this->attemptDown(r, c);
	if (down != nullptr) {
		moves.push_back(down);
	}

	Board* left = this->attemptLeft(r, c);
	if (left != nullptr) {
		moves.push_back(left);
	}

	Board* right = this->attemptRight(r, c);
	if (right != nullptr) {
		moves.push_back(right);
	}

	Board* jumpUp = this->attemptJumpUp(r, c);
	if (jumpUp != nullptr) {
		moves.push_back(jumpUp);
	}

	Board* jumpDown = this->attemptJumpDown(r, c);
	if (jumpDown != nullptr) {
		moves.push_back(jumpDown);
	}

	Board* jumpLeft = this->attemptJumpLeft(r, c);
	if (jumpLeft != nullptr) {
		moves.push_back(jumpLeft);
	}

	Board* jumpRight = this->attemptJumpRight(r, c);
	if (jumpRight != nullptr) {
		moves.push_back(jumpRight);
	}

	return moves;
}

Board* Board::attemptUp(int r, int c) {
	if (r > 0 && c > -1 && c < size && this->board[r-1][c] != OUTOFBOUNDS) {
		Board* temp = new Board(this->size, this->board);
		char t = temp->board[r - 1][c];
		temp->board[r-1][c] = temp->board[r][c];
		temp->board[r][c] = t;
		return temp;
	}
	return nullptr;
}

Board* Board::attemptDown(int r, int c) {
	if (r < size - 1 && c > -1 && c < size && this->board[r + 1][c] != OUTOFBOUNDS) {
		Board* temp = new Board(this->size, this->board);
		char t = temp->board[r + 1][c];
		temp->board[r + 1][c] = temp->board[r][c];
		temp->board[r][c] = t;
		return temp;
	}
	return nullptr;
}

Board* Board::attemptLeft(int r, int c) {
	if (r > -1 && r < size && c > 0 && this->board[r][c-1] != OUTOFBOUNDS) {
		Board* temp = new Board(this->size, this->board);
		char t = temp->board[r][c-1];
		temp->board[r][c-1] = temp->board[r][c];
		temp->board[r][c] = t;
		return temp;
	}
	return nullptr;
}

Board* Board::attemptRight(int r, int c) {
	if (r > -1 && r < size && c < size - 1 && this->board[r][c + 1] != OUTOFBOUNDS) {
		Board* temp = new Board(this->size, this->board);
		char t = temp->board[r][c + 1];
		temp->board[r][c + 1] = temp->board[r][c];
		temp->board[r][c] = t;
		return temp;
	}
	return nullptr;
}

Board* Board::attemptJumpUp(int r, int c) {
	if (r > 1 && c > -1 && c < size && this->board[r - 2][c] != OUTOFBOUNDS) {
		Board* temp = new Board(this->size, this->board);
		char t = temp->board[r-2][c];
		temp->board[r-2][c] = temp->board[r][c];
		temp->board[r][c] = t;
		return temp;
	}
	return nullptr;
}

Board* Board::attemptJumpDown(int r, int c) {
	if (r < size - 2  && c > -1 && c < size && this->board[r + 2][c] != OUTOFBOUNDS) {
		Board* temp = new Board(this->size, this->board);
		char t = temp->board[r + 2][c];
		temp->board[r + 2][c] = temp->board[r][c];
		temp->board[r][c] = t;
		return temp;
	}
	return nullptr;
}

Board* Board::attemptJumpLeft(int r, int c) {
	if (r > -1 && r < size && c > 1 && this->board[r][c - 2] != OUTOFBOUNDS) {
		Board* temp = new Board(this->size, this->board);
		char t = temp->board[r][c-2];
		temp->board[r][c-2] = temp->board[r][c];
		temp->board[r][c] = t;
		return temp;
	}
	return nullptr;
}

Board* Board::attemptJumpRight(int r, int c) {
	if (r > -1 && r < size && c < size - 2 && this->board[r][c + 2] != OUTOFBOUNDS) {
		Board* temp = new Board(this->size, this->board);
		char t = temp->board[r][c + 2];
		temp->board[r][c + 2] = temp->board[r][c];
		temp->board[r][c] = t;
		return temp; 
	}
	return nullptr;
}
