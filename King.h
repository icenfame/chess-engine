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


		for (int i = 0; i < moves.size(); i++) {
			if (this->white) {
				w_moves[moves[i].y][moves[i].x] = board[this->y][this->x];
			}
			else {
				b_moves[moves[i].y][moves[i].x] = board[this->y][this->x];
			}
		}

		auto prevMoves = moves;
		moves.clear();

		for (int i = 0; i < prevMoves.size(); i++) {
			if (this->white) {
				if (b_moves[prevMoves[i].y][prevMoves[i].x]->type == '0') {
					this->moves.push_back(Point{ prevMoves[i].x, prevMoves[i].y });
				}
			}
			else {
				if (w_moves[prevMoves[i].y][prevMoves[i].x]->type == '0') {
					this->moves.push_back(Point{ prevMoves[i].x, prevMoves[i].y });
				}
			}
		}

		bool check = this->white ? wCheck : bCheck;
		auto wb_moves = this->white ? b_moves : w_moves;

		if (wb_moves[this->y][this->x]->type != '0') {
			if (this->white) wCheck = true;
			else bCheck = true;

			whoMakeCheck = wb_moves[this->y][this->x];
			whoUnderCheck = this;
		}
		else {
			if (this->white) wCheck = false;
			else bCheck = false;
		}

		if (this->white) {
			cout << "WHITE KING CHECK: " << check << endl;
		}
		else {
			cout << "BLACK KING CHECK: " << check << endl;
		}

		int checkMate = 0;

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (board[i][j]->type != '0' && board[i][j]->white == this->white) {
					if (board[i][j]->moves.size() > 0) {
						checkMate++;
					}
				}
			}
		}

		if (!checkMate) {
			cout << "VSIO NAGRAUSI\n";
		}

		// Castling
		if (!this->moved && board[this->y][this->x + 3]->type == 'r' && !board[this->y][this->x + 3]->moved && !check && wb_moves[this->y][this->x + 1]->type == '0' && wb_moves[this->y][this->x + 2]->type == '0') {
			if (board[this->y][this->x + 1]->type == '0' && board[this->y][this->x + 2]->type == '0') {
				moves.push_back(Point{ this->x + 2, this->y });
			}
		}

		if (!this->moved && board[this->y][this->x - 4]->type == 'r' && !board[this->y][this->x - 4]->moved && !check && wb_moves[this->y][this->x - 1]->type == '0' && wb_moves[this->y][this->x - 2]->type == '0') {
			if (board[this->y][this->x - 1]->type == '0' && board[this->y][this->x - 2]->type == '0' && board[this->y][this->x - 3]->type == '0') {
				moves.push_back(Point{ this->x - 2, this->y });
			}
		}

		//cout << w_moves[7][1]->type << "  " << w_moves[7][1]->white << endl;
	}

	void customMove(Point to) {
		if (this->white == whitePlay) {
			int prev_x = this->x;
			int prev_y = this->y;

			this->x = to.x;
			this->y = to.y;

			board[to.y][to.x] = board[prev_y][prev_x];
			board[prev_y][prev_x] = new Piece('0');

			/*for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					w_moves[i][j] = new Piece('0');
					b_moves[i][j] = new Piece('0');
				}
			}*/

			generateBoardMoves();
		}
	}

	void ifCheck() {
		bool check = this->white ? wCheck : bCheck;
		auto prevMove = Point{ this->x, this->y };

		for (int i = 0; i < this->moves.size(); i++) {
			if (board[this->moves[i].y][this->moves[i].x]->type == '0' && check) {
				cout << this->moves[i].x << "  " << this->moves[i].y << "\t" << "  MOVE FROM CHECK\n";

				board[this->y][this->x]->customMove(Point{ this->moves[i].x, this->moves[i].y });

				board[this->y][this->x]->customMove(Point{ prevMove.x, prevMove.y });

				//generateBoardMoves();
			}
		}
	}
};