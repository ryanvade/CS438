#include "Board.h"


Board::Board() {

}

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
	this->outOfBounds_count = 0;
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
					this->outOfBounds_count++;
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
					this->blank_r = i;
					this->blank_c = i;
				}
			}
			else {
				// Black Boundary
				if (j >= h_divide) {
					this->board[i][j] = BLACK;
				}
				else {
					this->board[i][j] = OUTOFBOUNDS;
					this->outOfBounds_count++;
				}
			}
		}
	}
	this->serialized = "";
	this->hv = -1;
	this->gv = 0;

	/*this->black_max[5] = 15;
	this->black_max[7] = 36;
	this->black_max[9] = 70;
	this->black_max[11] = 120;
	this->red_max[5] = 33;
	this->red_max[7] = 56;
	this->red_max[9] = 170;
	this->red_max[11] = 300;*/

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
			if (board[i][j] == BLANK) {
				this->blank_r = i;
				this->blank_c = i;
			}
		}
	}
	this->serialized = "";
	this->hv = -1;
	this->gv = 0;
	
	/*this->black_max[7] = 36;
	this->black_max[9] = 70;
	this->black_max[11] = 120;
	this->red_max[5] = 33;
	this->red_max[7] = 56;
	this->red_max[9] = 170;
	this->red_max[11] = 300;*/
}


Board::~Board()
{
	if (this->board != nullptr)
	{
		for (size_t i = 0; i < this->size; i++)
		{
			delete(this->board[i]);
			this->board[i] == nullptr;
		}
		delete(this->board);
		this->board = nullptr;
	}
}

void Board::__serialize() {
	this->serialized.reserve(this->size * this->size);
	for (size_t i = 0; i < size; i++)
	{
		this->serialized.append(this->board[i], 0, this->size);
	}
}

std::string Board::serialize() {
	if (this->serialized == "") {
		this->__serialize();
	}
	return this->serialized;
}

void Board::print(std::ostream& out) {
	for (size_t i = 0; i < this->size; i++)
	{
		for (size_t j = 0; j < this->size; j++)
		{
			out << this->board[i][j] << " ";
		}
		out << std::endl;
	}
}

bool Board::solved() {
	std::string solved = "";
	if (this->size == 5) {
		solved = "BBB##BBB##BB RR##RRR##RRR";
	}
	else if (this->size == 7) {
		solved = "BBBB###BBBB###BBBB###BBB RRR###RRRR###RRRR###RRRR";
	}
	else if (this->size == 9){
		solved = "BBBBB####BBBBB####BBBBB####BBBBB####BBBB RRRR####RRRRR####RRRRR####RRRRR####RRRRR";
	}
	else {
		solved = "BBBBBB#####BBBBBB#####BBBBBB#####BBBBBB#####BBBBBB#####BBBBB RRRRR#####RRRRRR#####RRRRRR#####RRRRRR#####RRRRRR#####RRRRRR";
	}


	if (this->serialize() == solved) {
		std::cout << "Solved!" << std::endl;
		return true;
	}
	else {
		return false;
	}
}

std::vector<Board*> Board::getMoves() {
	int r = this->blank_r;
	int c = this->blank_c;
	std::vector<Board*> moves;

	Board* jumpUp = this->attemptJumpUp(r, c);
	if (jumpUp != nullptr) {
		moves.push_back(jumpUp);
	}
	
	Board* jumpDown = this->attemptJumpDown(r, c);
	if (jumpDown != nullptr) {
		moves.push_back(jumpDown);
	}

	Board* jumpRight = this->attemptJumpRight(r, c);
	if (jumpRight != nullptr) {
		moves.push_back(jumpRight);
	}

	Board* jumpLeft = this->attemptJumpLeft(r, c);
	if (jumpLeft != nullptr) {
		moves.push_back(jumpLeft);
	}

	Board* up = this->attemptUp(r, c);
	if (up != nullptr) {
		moves.push_back(up);
	}

	Board* down = this->attemptDown(r, c);
	if (down != nullptr) {
		moves.push_back(down);
	}

	Board* right = this->attemptRight(r, c);
	if (right != nullptr) {
		moves.push_back(right);
	}

	Board* left = this->attemptLeft(r, c);
	if (left != nullptr) {
		moves.push_back(left);
	}

	return moves;
}

Board* Board::attemptUp(int r, int c) {
	if (r > 0 && c > -1 && c < size && this->board[r-1][c] != OUTOFBOUNDS) {
		Board* temp(new Board(this->size, this->board));
		char t = temp->board[r - 1][c];
		temp->board[r-1][c] = temp->board[r][c];
		temp->board[r][c] = t;
		temp->parent = this;
		temp->blank_r = r - 1;
		temp->blank_c = c;
		return temp;
	}
	return nullptr;
}

Board* Board::attemptDown(int r, int c) {
	if (r < size - 1 && c > -1 && c < size && this->board[r + 1][c] != OUTOFBOUNDS) {
		Board* temp (new Board(this->size, this->board));
		char t = temp->board[r + 1][c];
		temp->board[r + 1][c] = temp->board[r][c];
		temp->board[r][c] = t;
		temp->parent = this;
		temp->blank_r = r + 1;
		temp->blank_c = c;
		return temp;
	}
	return nullptr;
}

Board* Board::attemptLeft(int r, int c) {
	if (r > -1 && r < size && c > 0 && this->board[r][c-1] != OUTOFBOUNDS) {
		Board* temp (new Board(this->size, this->board));
		char t = temp->board[r][c-1];
		temp->board[r][c-1] = temp->board[r][c];
		temp->board[r][c] = t;
		temp->parent = this;
		temp->blank_r = r;
		temp->blank_c = c - 1;
		return temp;
	}
	return nullptr;
}

Board* Board::attemptRight(int r, int c) {
	if (r > -1 && r < size && c < size - 1 && this->board[r][c + 1] != OUTOFBOUNDS) {
		Board* temp (new Board(this->size, this->board));
		char t = temp->board[r][c + 1];
		temp->board[r][c + 1] = temp->board[r][c];
		temp->board[r][c] = t;
		temp->parent = this;
		temp->blank_r = r;
		temp->blank_c = c + 1;
		return temp;
	}
	return nullptr;
}

Board* Board::attemptJumpUp(int r, int c) {
	if (r > 1 && c > -1 && c < size && this->board[r - 2][c] != OUTOFBOUNDS) {
		Board* temp (new Board(this->size, this->board));
		char t = temp->board[r-2][c];
		temp->board[r-2][c] = temp->board[r][c];
		temp->board[r][c] = t;
		temp->parent = this;
		temp->blank_r = r - 2;
		temp->blank_c = c;
		return temp;
	}
	return nullptr;
}

Board* Board::attemptJumpDown(int r, int c) {
	if (r < size - 2  && c > -1 && c < size && this->board[r + 2][c] != OUTOFBOUNDS) {
		Board* temp(new Board(this->size, this->board));
		char t = temp->board[r + 2][c];
		temp->board[r + 2][c] = temp->board[r][c];
		temp->board[r][c] = t;
		temp->parent = this;
		temp->blank_r = r + 2;
		temp->blank_c = c;
		return temp;
	}
	return nullptr;
}

Board* Board::attemptJumpLeft(int r, int c) {
	if (r > -1 && r < size && c > 1 && this->board[r][c - 2] != OUTOFBOUNDS) {
		Board* temp(new Board(this->size, this->board));
		char t = temp->board[r][c-2];
		temp->board[r][c-2] = temp->board[r][c];
		temp->board[r][c] = t;
		temp->parent = this;
		temp->blank_r = r;
		temp->blank_c = c-2;
		return temp;
	}
	return nullptr;
}

Board* Board::attemptJumpRight(int r, int c) {
	if (r > -1 && r < size && c < size - 2 && this->board[r][c + 2] != OUTOFBOUNDS) {
		Board* temp(new Board(this->size, this->board));
		char t = temp->board[r][c + 2];
		temp->board[r][c + 2] = temp->board[r][c];
		temp->board[r][c] = t;
		temp->parent = this;
		temp->blank_r = r;
		temp->blank_c = c+2;
		return temp; 
	}
	return nullptr;
}

bool Board::operator>(Board*  rhs) const
{
	return this->fv < rhs->fv;
}

float Board::hValue() {
	if (this->hv == -1) {
		double h = 0.0;
		
		/*std::string ser = this->serialize();
		int len = this->size * this->size;
		for (size_t i = 0; i < len; i++)
		{
				if (ser[i] == BLACK && i < len / 2) {
					h += 1.0;
				}
				else if (ser[i] == RED && i >= len / 2) {
					h += 1.0;
				}
				else if (ser[i] == BLANK && i != len / 2) {
					h += 1.0;
				}
		}
		if (DEBUG) {
			std::cout << ser << std::endl;
			std::cout << h << std::endl << std::endl;
		}
		*/
		int total_distance, red_distance, black_distance;
		int blackRowGoal, blackColGoal;
		int r = 0, c = 0;
		int value;
		int totalValue = 0;
		int halfSize = (this->size - 1) / 2;
		for (int i = 0; i <= halfSize; i++)
		{
			for (int j = 0; j <= halfSize; j++)
			{
				r += i;
				c += j;
			}
		}
		r - halfSize - 1;
		c - halfSize - 1;
		blackRowGoal = r;
		blackColGoal = c;
		int blackRowCurr, blackColCurr;
		r = 0, c = 0;
		for (int i = 0; i < this->size; i++)
		{
			for (int j = 0; j < this->size; j++)
			{
				if (this->board[i][j] == BLACK)
				{
					r += i;
					c += j;
				}
			}
		}
		blackRowCurr = r; 
		blackColCurr = c;
		black_distance = abs(blackRowGoal - blackRowCurr) + abs(blackColGoal - blackColCurr);
		int redRowGoal, redColGoal;
		r = 0, c = 0;
		totalValue = 0;
		for (int i = halfSize; i < this->size; i++)
		{
			for (int j = halfSize; j < this->size; j++)
			{
				r += i;
				c += j;
			}
		}
		r - halfSize;
		c - halfSize;
		redRowGoal = r; 
		redColGoal = c;
		int redRowCurr, redColCurr;
		 r = 0, c = 0;
		for (int i = 0; i < this->size; i++)
		{
			for (int j = 0; j < this->size; j++)
			{
				if (this->board[i][j] == RED)
				{
					r += i;
					c += j;
				}
			}
		}
		redRowCurr = r; redColCurr = c;
		//get the total black distance
		red_distance = abs(redRowGoal - redRowCurr) + abs(redColGoal - redColCurr);

		//get the total distance of black and red pieces
		total_distance = red_distance + black_distance;
		this->hv = total_distance * C;
	}
	return this->hv;
}
