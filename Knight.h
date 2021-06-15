class Knight : public Piece {
public:
	Knight(int x, int y, bool white, char type) :Piece(x, y, white, type) {}

	void generateMoves() {
		moves.clear();

		int k;

		if (!this->white) {
			k = -1;
		}
		else {
			k = 1;
		}

		// Y +- 2; X +- 1
		if (this->y - 2 * k >= 0 && this->y - 2 * k <= 7 && this->x + 1 <= 7) {
			if (board[this->y - 2 * k][this->x + 1]->type == '0' || board[this->y - 2 * k][this->x + 1]->white != this->white) {
				moves.push_back(Point{ this->x + 1, this->y - 2 * k });
			}
			else {
				if (this->white) {
					w_moves[this->y - 2 * k][this->x + 1] = this;
				}
				else {
					b_moves[this->y - 2 * k][this->x + 1] = this;
				}
			}
		}
		if (this->y - 2 * k >= 0 && this->y - 2 * k <= 7 && this->x - 1 >= 0) {
			if (board[this->y - 2 * k][this->x - 1]->type == '0' || board[this->y - 2 * k][this->x - 1]->white != this->white) {
				moves.push_back(Point{ this->x - 1, this->y - 2 * k });
			}
			else {
				if (this->white) {
					w_moves[this->y - 2 * k][this->x - 1] = this;
				}
				else {
					b_moves[this->y - 2 * k][this->x - 1] = this;
				}
			}
		}

		if (this->y + 2 * k >= 0 && this->y + 2 * k <= 7 && this->x + 1 <= 7) {
			if (board[this->y + 2 * k][this->x + 1]->type == '0' || board[this->y + 2 * k][this->x + 1]->white != this->white) {
				moves.push_back(Point{ this->x + 1, this->y + 2 * k });
			}
			else {
				if (this->white) {
					w_moves[this->y + 2 * k][this->x + 1] = this;
				}
				else {
					b_moves[this->y + 2 * k][this->x + 1] = this;
				}
			}
		}
		if (this->y + 2 * k >= 0 && this->y + 2 * k <= 7 && this->x - 1 >= 0) {
			if (board[this->y + 2 * k][this->x - 1]->type == '0' || board[this->y + 2 * k][this->x - 1]->white != this->white) {
				moves.push_back(Point{ this->x - 1, this->y + 2 * k });
			}
			else {
				if (this->white) {
					w_moves[this->y + 2 * k][this->x - 1] = this;
				}
				else {
					b_moves[this->y + 2 * k][this->x - 1] = this;
				}
			}
		}

		// Y +- 1; X +- 2
		if (this->y - 1 * k >= 0 && this->y - 1 * k <= 7 && this->x + 2 <= 7) {
			if (board[this->y - 1 * k][this->x + 2]->type == '0' || board[this->y - 1 * k][this->x + 2]->white != this->white) {
				moves.push_back(Point{ this->x + 2, this->y - 1 * k });
			}
			else {
				if (this->white) {
					w_moves[this->y - 1 * k][this->x + 2] = this;
				} else {
					b_moves[this->y - 1 * k][this->x + 2] = this;
				}
			}
		}
		if (this->y - 1 * k >= 0 && this->y - 1 * k <= 7 && this->x - 2 >= 0) {
			if (board[this->y - 1 * k][this->x - 2]->type == '0' || board[this->y - 1 * k][this->x - 2]->white != this->white) {
				moves.push_back(Point{ this->x - 2, this->y - 1 * k });
			}
			else {
				if (this->white) {
					w_moves[this->y - 1 * k][this->x - 2] = this;
				} else {
					b_moves[this->y - 1 * k][this->x - 2] = this;
				}
			}
		}

		if (this->y + 1 * k >= 0 && this->y + 1 * k <= 7 && this->x + 2 <= 7) {
			if (board[this->y + 1 * k][this->x + 2]->type == '0' || board[this->y + 1 * k][this->x + 2]->white != this->white) {
				moves.push_back(Point{ this->x + 2, this->y + 1 * k });
			}
			else {
				if (this->white) {
					w_moves[this->y + 1 * k][this->x + 2] = this;
				} else {
					b_moves[this->y + 1 * k][this->x + 2] = this;
				}
			}
		}
		if (this->y + 1 * k >= 0 && this->y + 1 * k <= 7 && this->x - 2 >= 0) {
			if (board[this->y + 1 * k][this->x - 2]->type == '0' || board[this->y + 1 * k][this->x - 2]->white != this->white) {
				moves.push_back(Point{ this->x - 2, this->y + 1 * k });
			}
			else {
				if (this->white) {
					w_moves[this->y + 1 * k][this->x - 2] = this;
				} else {
					b_moves[this->y + 1 * k][this->x - 2] = this;
				}
			}
		}

		this->attackPriority();
		this->secureFromCheck();
		this->preventFromCheck();
	}
};