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
		
		//castling
		if (this->moved == false && board[this->y][this->x + 3]->moved == false && board[this->y][this->x + 3]->type == 'r') {
			if (board[this->y][this->x + 1]->type == '0' && board[this->y][this->x + 2]->type == '0') {
				moves.push_back(Point{ this->x + 2, this->y});
			}
		}

		if (this->moved == false && board[this->y][this->x - 4]->moved == false && board[this->y][this->x - 4]->type == 'r') {
			if (board[this->y][this->x - 1]->type == '0' && board[this->y][this->x - 2]->type == '0' && board[this->y][this->x - 3]->type == '0') {
				moves.push_back(Point{ this->x - 2, this->y});
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

		//wCheck = false;
		//bCheck = false;

		for (int i = 0; i < prevMoves.size(); i++) {
			if (this->white) {
				if (!b_moves[prevMoves[i].y][prevMoves[i].x]) {
					this->moves.push_back(Point{ prevMoves[i].x, prevMoves[i].y });
				}
				else {
					cout << "WHITE CHECK" << endl;
					cout << prevMoves[i].x << "  " << prevMoves[i].y << " | " << i << endl;

					//wCheck = true;
				}
			}
			else {
				if (!w_moves[prevMoves[i].y][prevMoves[i].x]) {
					this->moves.push_back(Point{ prevMoves[i].x, prevMoves[i].y });
				}
				else {
					cout << "BLACK CHECK" << endl;
					cout << prevMoves[i].x << "  " << prevMoves[i].y << " | " << i << endl;

					//bCheck = true;
				}
			}
		}

		//if (wCheck)
	}
};