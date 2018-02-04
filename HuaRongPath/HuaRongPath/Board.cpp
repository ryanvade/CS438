#include "Board.h"



Board::Board()
{
}

Board::Board(Board* b) {
	for (size_t i = 0; i < 5; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			this->board[i][j] = b->board[i][j];
		}
	}
}


Board::~Board()
{
}


bool Board::instantiate(std::string filename) {
	for (size_t i = 0; i < 5; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			this->board[i][j] = 'b';
		}
	}

	size_t r = 0;
	size_t c = 0;
	char ch;
	std::fstream fin(filename, std::fstream::in);
	if (fin.is_open()) {
		while (fin >> std::noskipws >> ch) {
			if (ch != ' ' && ch != '\n') {
				this->board[r][c] = ch;
				c++;
				if (c == 4 && r < 5) {
					c = 0;
					r++;
				}
			}
			
			if (r == 5 && c == 4) {
				break;
			}
		}
		return true;
	}
	return false;
}

void Board::print(std::ostream& stream) {
	for (size_t i = 0; i < 5; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			stream << this->board[i][j] << " ";
		}
		stream << std::endl;
	}
}


bool Board::isSingle(int r, int c) {
	if (r >= 5 || c >= 4 || r < 0 || c < 0) {
		return false;
	}
	char curr = this->board[r][c];
	if (r > 0 && this->board[r-1][c] == curr) return false;
	if (r < 4 && this->board[r+1][c] == curr) return false;
	if (c > 0 && this->board[r][c-1] == curr) return false;
	if (c < 3 && this->board[r][c+1] == curr) return false;

	return true;
}

bool Board::isLeftOfHorizontalTwo(int r, int c) {
	if (r >= 5 || c >= 4 || r < 0 || c < 0) {
		return false;
	}
	char curr = this->board[r][c];
	if (c < 3 && this->board[r][c+1] == curr) return true;
	return false;
}

bool Board::isTopOfVerticalTwo(int r, int c) {
	if (r >= 5 || c >= 4 || r < 0 || c < 0) {
		return false;
	}
	char curr = this->board[r][c];
	if (r < 4 && this->board[r+1][c] != curr) return false;
	if (c > 0 && this->board[r + 1][c-1] == curr) return true;
	return true;
}

bool Board::isTopLeftOfQuad(int r, int c) {
	if (r > 3 || c > 2 || r < 0 || c < 0) {
		return false;
	}

	char curr = this->board[r][c];
	if (this->isLeftOfHorizontalTwo(r, c) && this->isTopOfVerticalTwo(r, c) && this->board[r+1][c+1] == curr) {
		return true;
	}
	return false;
}