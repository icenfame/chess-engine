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
		if (this->x - 1 >= 0) {
			if (this->white) {
				w_moves[this->y - 1 * k][this->x - 1] = board[this->y][this->x];
			}
			else {
				b_moves[this->y - 1 * k][this->x - 1] = board[this->y][this->x];
			}
		}
		if (this->x + 1 <= 7) {
			if (this->white) {
				w_moves[this->y - 1 * k][this->x + 1] = board[this->y][this->x];
			}
			else {
				b_moves[this->y - 1 * k][this->x + 1] = board[this->y][this->x];
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
	}
};