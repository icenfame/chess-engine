class King : public Piece {
public:
	King(int x, int y, bool white, char type) :Piece(x, y, white, type) {}

	void generateMoves() {
		moves.clear();

		if (this->y - 1 >= 0 && this->x - 1 >= 0) {
			if (board[this->y - 1][this->x - 1]->type == '0' || board[this->y - 1][this->x - 1]->white != this->white) {
				moves.push_back(Point{ this->x - 1, this->y - 1 });
			}
		}
		if (this->y - 1 >= 0) {
			if (board[this->y - 1][this->x]->type == '0' || board[this->y - 1][this->x]->white != this->white) {
				moves.push_back(Point{ this->x, this->y - 1 });
			}
		}
		if (this->y - 1 >= 0 && this->x + 1 <= 7) {
			if (board[this->y - 1][this->x + 1]->type == '0' || board[this->y - 1][this->x + 1]->white != this->white) {
				moves.push_back(Point{ this->x + 1, this->y - 1 });
			}
		}

		if (this->x + 1 <= 7) {
			if (board[this->y][this->x + 1]->type == '0' || board[this->y][this->x + 1]->white != this->white) {
				moves.push_back(Point{ this->x + 1, this->y });
			}
		}
		if (this->x - 1 >= 0) {
			if (board[this->y][this->x - 1]->type == '0' || board[this->y][this->x - 1]->white != this->white) {
				moves.push_back(Point{ this->x - 1, this->y });
			}
		}

		if (this->y + 1 <= 7 && this->x + 1 <= 7) {
			if (board[this->y + 1][this->x + 1]->type == '0' || board[this->y + 1][this->x + 1]->white != this->white) {
				moves.push_back(Point{ this->x + 1, this->y + 1 });
			}
		}
		if (this->y + 1 <= 7) {
			if (board[this->y + 1][this->x]->type == '0' || board[this->y + 1][this->x]->white != this->white) {
				moves.push_back(Point{ this->x, this->y + 1 });
			}
		}
		if (this->y + 1 <= 7 && this->x - 1 >= 0) {
			if (board[this->y + 1][this->x - 1]->type == '0' || board[this->y + 1][this->x - 1]->white != this->white) {
				moves.push_back(Point{ this->x - 1, this->y + 1 });
			}
		}
		
		// Castling
		if (!this->moved && board[this->y][this->x + 3]->type == 'r' && !board[this->y][this->x + 3]->moved) {
			if (board[this->y][this->x + 1]->type == '0' && board[this->y][this->x + 2]->type == '0') {
				moves.push_back(Point{ this->x + 2, this->y });
			}
		}

		if (!this->moved && board[this->y][this->x - 4]->type == 'r' && !board[this->y][this->x - 4]->moved) {
			if (board[this->y][this->x - 1]->type == '0' && board[this->y][this->x - 2]->type == '0' && board[this->y][this->x - 3]->type == '0') {
				moves.push_back(Point{ this->x - 2, this->y });
			}
		}

		for (int i = 0; i < moves.size(); i++) {
			if (this->white) {
				w_moves[moves[i].y][moves[i].x] = 1;
			}
			else {
				b_moves[moves[i].y][moves[i].x] = 1;
			}
		}

		auto prevMoves = moves;
		moves.clear();

		for (int i = 0; i < prevMoves.size(); i++) {
			if (this->white) {
				if (!b_moves[prevMoves[i].y][prevMoves[i].x]) {
					this->moves.push_back(Point{ prevMoves[i].x, prevMoves[i].y });
				}
				else {
					//cout << "WHITE BLOCK" << endl;
				}
			}
			else {
				if (!w_moves[prevMoves[i].y][prevMoves[i].x]) {
					this->moves.push_back(Point{ prevMoves[i].x, prevMoves[i].y });
				}
				else {
					//cout << "BLACK BLOCK" << endl;
				}
			}
		}

		auto wb_moves = this->white ? b_moves : w_moves;

		if (wb_moves[this->y][this->x]) {
			if (this->white) wCheck = true;
			else bCheck = true;
		}
		else {
			if (this->white) wCheck = false;
			else bCheck = false;
		}

		if (this->white) {
			cout << "KING CHECK: " << wCheck << endl;
		}
	}

	void ifCheck() {
		bool check = this->white ? wCheck : bCheck;
		auto prevMove = Point{ this->x, this->y };

		for (int i = 0; i < this->moves.size(); i++) {
			if (board[this->moves[i].y][this->moves[i].x]->type == '0' && check) {
				cout << this->moves[i].x << "  " << this->moves[i].y << "\t" << "  MOVE FROM CHECK\n";

				board[this->y][this->x]->move(Point{ this->moves[i].x, this->moves[i].y });

				whitePlay = this->white;

				int prev_x = this->x;
				int prev_y = this->y;

				this->x = prevMove.x;
				this->y = prevMove.y;

				board[prevMove.y][prevMove.x] = board[prev_y][prev_x];
				board[prev_y][prev_x] = new Piece('0');

				generateBoardMoves();
			}
		}
	}
};