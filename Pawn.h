class Pawn : public Piece {
public:
	Pawn(int x, int y, bool white, char type) :Piece(x, y, white, type) {}

	void generateMoves() {
		moves.clear();

		int k;

		if (!this->white) {
			k = -1;
		}
		else {
			k = 1;
		}

		// Pawn to queen
		if (this->white && this->y == 0 || !this->white && this->y == 7) {
			board[this->y][this->x] = new Queen(this->x, this->y, this->white, 'q');
		}

		if (this->y - 1 < 0 || this->y + 1 > 7) {
			return;
		}

		if (this->x - 1 >= 0 && board[this->y - 1 * k][this->x - 1]->type != '0' && board[this->y - 1 * k][this->x - 1]->white != this->white) {
			moves.push_back(Point{ this->x - 1, this->y - 1 * k });
		}
		if (this->x + 1 <= 7 && board[this->y - 1 * k][this->x + 1]->type != '0' && board[this->y - 1 * k][this->x + 1]->white != this->white) {
			moves.push_back(Point{ this->x + 1, this->y - 1 * k });
		}

		// King check verification
		auto king = this->white ? wKing : bKing;

		if (this->x - 1 >= 0) {
			if (this->white) {
				if (w_moves[this->y - 1 * k][this->x - 1]->type == '0') {
					w_moves[this->y - 1 * k][this->x - 1] = this;
				}
				// attack priority
				else if (king && (this->x == king->x || this->y == king->y || abs(this->x - king->x) == abs(this->y - king->y))) {
					w_moves[this->y - 1 * k][this->x - 1] = this;
				}
			}
			else {
				if (b_moves[this->y - 1 * k][this->x - 1]->type == '0') {
					b_moves[this->y - 1 * k][this->x - 1] = this;
				}
				else if (king && (this->x == king->x || this->y == king->y || abs(this->x - king->x) == abs(this->y - king->y))) {
					b_moves[this->y - 1 * k][this->x - 1] = this;
				}
			}
		}
		if (this->x + 1 <= 7) {
			if (this->white) {
				if (w_moves[this->y - 1 * k][this->x + 1]->type == '0') {
					w_moves[this->y - 1 * k][this->x + 1] = this;
				}
				else if (king && (this->x == king->x || this->y == king->y || abs(this->x - king->x) == abs(this->y - king->y))) {
					w_moves[this->y - 1 * k][this->x + 1] = this;
				}
			}
			else {
				if (b_moves[this->y - 1 * k][this->x + 1]->type == '0') {
					b_moves[this->y - 1 * k][this->x + 1] = this;
				}
				else if (king && (this->x == king->x || this->y == king->y || abs(this->x - king->x) == abs(this->y - king->y))) {
					b_moves[this->y - 1 * k][this->x + 1] = this;
				}
			}
		}
		
		// Move 1 field and 2 fields
		if (board[this->y - 1 * k][this->x]->type == '0') {
			this->moves.push_back(Point{ this->x, this->y - 1 * k });

			if (!this->moved && board[this->y - 2 * k][this->x]->type == '0') {
				this->moves.push_back(Point{ this->x, this->y - 2 * k });
			}
		}

		this->secureFromCheck();
		this->preventFromCheck();
		this->kingCheck();
	}
};