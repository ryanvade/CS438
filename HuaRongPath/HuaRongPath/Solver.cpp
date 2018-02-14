#include "Solver.h"



Solver::Solver(Board* board)
{
	this->initial = new State(board);
}

Solver::~Solver()
{

}

bool Solver::dfs()
{
	std::stack<State*> open;
	open.push(this->initial);
	std::list<State> closed;
	while (!open.empty())
	{
		State* current = open.top();
		open.pop();
		if (open.size() > 500 || closed.size() > 500) {
			return false;
		}
		if (this->solved(current))
		{
			this->solution = current;
			return true;
		}

		current->children = this->calculateMoves(current);
		for (auto iter = current->children.begin(); iter != current->children.end(); iter++)
		{
			
			const State s = *(*iter);
			if (std::find(closed.begin(), closed.end(), s) == closed.end()) {
				open.push(*iter);
			}
		}
		closed.emplace_back(*current);
	}
	return true;
}


bool Solver::bfs()
{
	return true;
}

std::vector<State*> Solver::calculateMoves(State* current) {
	Board* board = current->result;
	Board* b;
	std::vector<State*> children;
	if (DEBUG) {
		std::cout << "Current Board: " << std::endl;
		board->print(std::cout);
		std::cout << std::endl << std::endl;
	}
	for (size_t r = 0; r < 5; r++)
	{
		for (size_t c = 0; c < 4; c++)
		{
			// for every space on the board
			// if the space is a blank
			if (board->board[r][c] == 'b') {
				if (board->isSingle(r, c)) {
					if (board->isSingle(r, c - 1)) {
						// move space left
						b = new Board(board);
						b->board[r][c] = b->board[r][c-1];
						b->board[r][c-1] = 'b';
						if (DEBUG) {
							b->print(std::cout);
							std::cout << std::endl;
						}
						children.push_back(new State(b, current));
						b = nullptr;
					}
					if (board->isSingle(r, c + 1)) {
						// move space right
						b = new Board(board);
						b->board[r][c] = b->board[r][c + 1];
						b->board[r][c + 1] = 'b';
						if (DEBUG) {
							b->print(std::cout);
							std::cout << std::endl;
						}
						children.push_back(new State(b, current));
						b = nullptr;
					}
					if (board->isSingle(r - 1, c)) {
						// move space up
						b = new Board(board);
						b->board[r][c] = b->board[r-1][c];
						b->board[r-1][c] = 'b';
						if (DEBUG) {
							b->print(std::cout);
							std::cout << std::endl;
						}
						children.push_back(new State(b, current));
						b = nullptr;
					}
					if (board->isSingle(r+1, c)) {
						// moce space down
						b = new Board(board);
						b->board[r][c] = b->board[r+1][c];
						b->board[r+1][c] = 'b';
						if (DEBUG) {
							b->print(std::cout);
							std::cout << std::endl;
						}
						children.push_back(new State(b, current));
						b = nullptr;
					}
					if (board->isLeftOfHorizontalTwo(r, c+1)) {
						// Move space right two
						b = new Board(board);
						b->board[r][c] = b->board[r][c+2];
						b->board[r][c + 2] = 'b';
						if (DEBUG) {
							b->print(std::cout);
							std::cout << std::endl;
						}
						children.push_back(new State(b, current));
						b = nullptr;
					}
					if (board->isLeftOfHorizontalTwo(r, c-2)) {
						// Move space left two
						b = new Board(board);
						b->board[r][c] = b->board[r][c - 2];
						b->board[r][c - 2] = 'b';
						if (DEBUG) {
							b->print(std::cout);
							std::cout << std::endl;
						}
						children.push_back(new State(b, current));
						b = nullptr;
					}
					if (board->isTopOfVerticalTwo(r - 2, c)) {
						// move space up
						b = new Board(board);
						b->board[r][c] = b->board[r-2][c];
						b->board[r-2][c] = 'b';
						if (DEBUG) {
							b->print(std::cout);
							std::cout << std::endl;
						}
						children.push_back(new State(b, current));
						b = nullptr;
					}
					if (board->isTopOfVerticalTwo(r + 1, c)) {
						// move space down
						b = new Board(board);
						b->board[r][c] = b->board[r + 1][c];
						b->board[r+2][c] = 'b';
						if (DEBUG) {
							b->print(std::cout);
							std::cout << std::endl;
						}
						children.push_back(new State(b, current));
						b = nullptr;
					}
				}
				if (board->isLeftOfHorizontalTwo(r, c)) {
					if (board->isLeftOfHorizontalTwo(r - 1, c)) {
						// move spaces up
						b = new Board(board);
						b->board[r][c] = b->board[r-1][c];
						b->board[r][c+1] = b->board[r - 1][c+1];
						b->board[r - 1][c] = 'b';
						b->board[r - 1][c + 1] = 'b';
						if (DEBUG) {
							b->print(std::cout);
							std::cout << std::endl;
						}
						children.push_back(new State(b, current));
						b = nullptr;
					}
					if (board->isLeftOfHorizontalTwo(r+1, c)) {
						// move spaces down
						b = new Board(board);
						b->board[r][c] = b->board[r + 1][c];
						b->board[r][c + 1] = b->board[r + 1][c + 1];
						b->board[r + 1][c] = 'b';
						b->board[r + 1][c + 1] = 'b';
						if (DEBUG) {
							b->print(std::cout);
							std::cout << std::endl;
						}
						children.push_back(new State(b, current));
						b = nullptr;
					}
					if (board->isLeftOfHorizontalTwo(r, c + 1)) {
						// move spaces right
						b = new Board(board);
						b->board[r][c] = b->board[r][c+1];
						b->board[r][c + 1] = b->board[r][c + 2];
						b->board[r][c+1] = 'b';
						b->board[r][c + 2] = 'b';
						if (DEBUG) {
							b->print(std::cout);
							std::cout << std::endl;
						}
						children.push_back(new State(b, current));
						b = nullptr;
					}
					if (board->isLeftOfHorizontalTwo(r, c - 1)) {
						// move spaces left
						b = new Board(board);
						b->board[r][c] = b->board[r][c - 1];
						b->board[r][c + 1] = b->board[r][c - 2];
						b->board[r][c - 1] = 'b';
						b->board[r][c - 2] = 'b';
						if (DEBUG) {
							b->print(std::cout);
							std::cout << std::endl;
						}
						children.push_back(new State(b, current));
						b = nullptr;
					}
				}
				// 
				if (board->isTopOfVerticalTwo(r, c)) {
					if (board->isTopOfVerticalTwo(r - 2, c)) {
						// move spaces up
						b = new Board(board);
						b->board[r][c] = b->board[r-2][c];
						b->board[r + 1][c] = b->board[r -1][c];
						b->board[r-2][c] = 'b';
						b->board[r-1][c] = 'b';
						if (DEBUG) {
							b->print(std::cout);
							std::cout << std::endl;
						}
						children.push_back(new State(b, current));
						b = nullptr;
					}
					if (board->isTopOfVerticalTwo(r + 2, c)) {
						// move spaces down
						b = new Board(board);
						b->board[r][c] = b->board[r + 2][c];
						b->board[r + 1][c] = b->board[r + 1][c];
						b->board[r + 2][c] = 'b';
						b->board[r + 1][c] = 'b';
						if (DEBUG) {
							b->print(std::cout);
							std::cout << std::endl;
						}
						children.push_back(new State(b, current));
						b = nullptr;
					}
					if (board->isTopOfVerticalTwo(r, c + 1)) {
						// move spaces right
						b = new Board(board);
						b->board[r][c] = b->board[r][c+1];
						b->board[r][c] = b->board[r+1][c+1];
						b->board[r][c] = 'b';
						b->board[r+1][c] = 'b';
						if (DEBUG) {
							b->print(std::cout);
							std::cout << std::endl;
						}
						children.push_back(new State(b, current));
						b = nullptr;
					}
					if (board->isTopOfVerticalTwo(r, c - 1)) {
						// move spaces left
						b = new Board(board);
						b->board[r][c] = b->board[r][c-1];
						b->board[r+1][c] = b->board[r + 1][c-1];
						b->board[r][c-1] = 'b';
						b->board[r+1][c-1] = 'b';
						if (DEBUG) {
							b->print(std::cout);
							std::cout << std::endl;
						}
						children.push_back(new State(b, current));
						b = nullptr;
					}
				}
				if (board->isTopLeftOfQuad(r, c)) {
					if (board->isTopLeftOfQuad(r, c - 2)) {
						// move spaces left
						b = new Board(board);
						b->board[r][c] = b->board[r][c - 1];
						b->board[r][c + 1] = b->board[r][c - 2];
						b->board[r][c - 1] = 'b';
						b->board[r][c - 2] = 'b';
						if (DEBUG) {
							b->print(std::cout);
							std::cout << std::endl;
						}
						children.push_back(new State(b, current));
						b = nullptr;
					}
					if (board->isTopLeftOfQuad(r, c + 2)) {
						// move spaces right
						b = new Board(board);
						b->board[r][c] = b->board[r][c - 1];
						b->board[r][c + 1] = b->board[r][c - 2];
						b->board[r][c - 1] = 'b';
						b->board[r][c - 2] = 'b';
						if (DEBUG) {
							b->print(std::cout);
							std::cout << std::endl;
						}
						children.push_back(new State(b, current));
						b = nullptr;
					}
					if (board->isTopLeftOfQuad(r - 2, c)) {
						// move spaces up
					}
					if (board->isTopLeftOfQuad(r + 2, c)) {
						// move spaces down
					}
				}
				
			}

		}
	}
	return children;
}

// Attempt to move the blank space left
State* Solver::left(Board* board, int r, int c) {
	if (c == 0) {
		return nullptr;
	}

}

bool Solver::solved(State* current) {
	Board* board = current->result;
	return board->board[3][1] == board->board[3][2] == board->board[4][1] == board->board[4][2];
}
