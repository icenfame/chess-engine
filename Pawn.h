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
		if (board[this->y - 1 * k][this->x - 1]->type == '0') {
			if (this->white) {
				w_moves[this->y - 1 * k][this->x - 1] = 1;
			}
			else {
				b_moves[this->y - 1 * k][this->x - 1] = 1;
			}
		}
		if (board[this->y - 1 * k][this->x + 1]->type == '0') {
			if (this->white) {
				w_moves[this->y - 1 * k][this->x + 1] = 1;
			}
			else {
				b_moves[this->y - 1 * k][this->x + 1] = 1;
			}
		}

		if (board[this->y - 1 * k][this->x]->type == '0') {
			moves.push_back(Point{ this->x, this->y - 1 * k });

			if (!this->moved && board[this->y - 2 * k][this->x]->type == '0') {
				moves.push_back(Point{ this->x, this->y - 2 * k });
			}
		}
	}
};