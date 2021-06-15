class Queen : public Piece {
public:
	Queen(int x, int y, bool white, char type) :Piece(x, y, white, type) {}

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

		for (int x = this->x; x < 7; x++) {
			if (board[this->y][x + 1]->type == '0') {
				moves.push_back(Point{ x + 1, this->y });
			}
			else if (board[this->y][x + 1]->white == this->white) {
				if (this->white) {
					w_moves[this->y][x + 1] = this;
				}
				else {
					b_moves[this->y][x + 1] = this;
				}

				break;
			}
			else {
				moves.push_back(Point{ x + 1, this->y });
				break;
			}
		}

		for (int x = this->x; x > 0; x--) {
			if (board[this->y][x - 1]->type == '0') {
				moves.push_back(Point{ x - 1, this->y });
			}
			else if (board[this->y][x - 1]->white == this->white) {
				if (this->white) {
					w_moves[this->y][x - 1] = this;
				}
				else {
					b_moves[this->y][x - 1] = this;
				}

				break;
			}
			else {
				moves.push_back(Point{ x - 1, this->y });
				break;
			}
		}

		for (int y = this->y; y < 7; y++) {
			if (board[y + 1][this->x]->type == '0') {
				moves.push_back(Point{ this->x, y + 1 });
			}
			else if (board[y + 1][this->x]->white == this->white) {
				if (this->white) {
					w_moves[y + 1][this->x] = this;
				}
				else {
					b_moves[y + 1][this->x] = this;
				}

				break;
			}
			else {
				moves.push_back(Point{ this->x, y + 1 });
				break;
			}
		}

		for (int y = this->y; y > 0; y--) {
			if (board[y - 1][this->x]->type == '0') {
				moves.push_back(Point{ this->x, y - 1 });
			}
			else if (board[y - 1][this->x]->white == this->white) {
				if (this->white) {
					w_moves[y - 1][this->x] = this;
				}
				else {
					b_moves[y - 1][this->x] = this;
				}

				break;
			}
			else {
				moves.push_back(Point{ this->x, y - 1 });
				break;
			}
		}

		for (int i = 0; i < moves.size(); i++) {
			if (this->white) {
				w_moves[moves[i].y][moves[i].x] = this;
			}
			else {
				b_moves[moves[i].y][moves[i].x] = this;
			}
		}

		this->secureFromCheck();
		this->preventFromCheck();
	}
};