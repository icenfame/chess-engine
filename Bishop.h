class Bishop : public Piece {
public:
	Bishop(int x, int y, bool white, char type) :Piece(x, y, white, type) {}

	void generateMoves() {
		moves.clear();

		for (int x = this->x, y = this->y; x < 7 && y < 7; x++, y++) {
			if (board[y + 1][x + 1]->type == '0') {
				moves.push_back(Point{ x + 1, y + 1 });
			}
			else if (board[y + 1][x + 1]->white == this->white) {
				if (this->white) {
					w_moves[y + 1][x + 1] = this;
				}
				else {
					b_moves[y + 1][x + 1] = this;
				}

				break;
			}
			else {
				moves.push_back(Point{ x + 1, y + 1 });
				break;
			}
		}

		for (int x = this->x, y = this->y; x > 0 && y > 0; x--, y--) {
			if (board[y - 1][x - 1]->type == '0') {
				moves.push_back(Point{ x - 1, y - 1 });
			}
			else if (board[y - 1][x - 1]->white == this->white) {
				if (this->white) {
					w_moves[y - 1][x - 1] = this;
				}
				else {
					b_moves[y - 1][x - 1] = this;
				}

				break;
			}
			else {
				moves.push_back(Point{ x - 1, y - 1 });
				break;
			}
		}

		for (int x = this->x, y = this->y; x > 0 && y < 7; x--, y++) {
			if (board[y + 1][x - 1]->type == '0') {
				moves.push_back(Point{ x - 1, y + 1 });
			}
			else if (board[y + 1][x - 1]->white == this->white) {
				if (this->white) {
					w_moves[y + 1][x - 1] = this;
				}
				else {
					b_moves[y + 1][x - 1] = this;
				}

				break;
			}
			else {
				moves.push_back(Point{ x - 1, y + 1 });
				break;
			}
		}

		for (int x = this->x, y = this->y; x < 7 && y > 0; x++, y--) {
			if (board[y - 1][x + 1]->type == '0') {
				moves.push_back(Point{ x + 1, y - 1 });
			}
			else if (board[y - 1][x + 1]->white == this->white) {
				if (this->white) {
					w_moves[y - 1][x + 1] = this;
				}
				else {
					b_moves[y - 1][x + 1] = this;
				}

				break;
			}
			else {
				moves.push_back(Point{ x + 1, y - 1 });
				break;
			}
		}

		this->attackPriority();
		this->secureFromCheck();
		this->preventFromCheck();
		this->kingCheck();
	}
};