struct Point {
	int x, y;
};

class Piece;

void generateBoardMoves();

Piece* board[8][8];

Piece* w_moves[8][8];
Piece* b_moves[8][8];

bool whitePlay = true;

bool wCheck = false;
bool bCheck = false;

Piece* whoMakeCheck;
Piece* whoUnderCheck;

class Piece {
public:
	char type;
	int x, y;
	bool white, moved;

	vector<Point> moves;

	Piece() {}
	Piece(char type) {
		this->type = type;
	}
	Piece(int x, int y, bool white, char type) {
		this->x = x;
		this->y = y;
		this->white = white;
		this->moved = 0;
		this->type = type;

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				w_moves[i][j] = new Piece('0');
				b_moves[i][j] = new Piece('0');
			}
		}

		whoMakeCheck = new Piece('0');
		whoUnderCheck = new Piece('0');
	}

	virtual void generateMoves() {}
	virtual void ifCheck() {}
	virtual void customMove(Point to) {}

	void move(Point to) {
		if (this->white == whitePlay) {
			for (int i = 0; i < this->moves.size(); i++) {
				if (to.x == this->moves[i].x && to.y == this->moves[i].y) {
					int prev_x = this->x;
					int prev_y = this->y;

					if (this->type == 'k' && to.y == this->y) {
						if (to.x == this->x + 2) {
							board[this->y][7]->move(Point{ 5, this->y });
						}
						else if (to.x == this->x - 2) {
							board[this->y][0]->move(Point{ 3, this->y });
						}

						whitePlay = this->white;
					}

					this->x = to.x;
					this->y = to.y;

					board[this->y][this->x] = board[prev_y][prev_x];
					board[prev_y][prev_x] = new Piece('0');

					this->moved = true;

					for (int i = 0; i < 8; i++) {
						for (int j = 0; j < 8; j++) {
							w_moves[i][j] = new Piece('0');
							b_moves[i][j] = new Piece('0');
						}
					}

					generateBoardMoves();

					whitePlay = !whitePlay;

					break;
				}
			}
		}
	}

	void secureFromCheck() {
		bool check = this->white ? wCheck : bCheck;
		auto wb_moves = this->white ? b_moves : w_moves;

		if (check) {
			auto prevMoves = this->moves;
			this->moves.clear();

			//for (int i = 0; i < prevMoves.size(); i++) {
			//	Point startPoint = { whoUnderCheck->x, whoUnderCheck->y };

			//	int kx = 0, ky = 0;

			//	if (whoUnderCheck->x - whoMakeCheck->x < 0) kx = 1;
			//	if (whoUnderCheck->x - whoMakeCheck->x > 0) kx = -1;

			//	if (whoUnderCheck->y - whoMakeCheck->y < 0) ky = 1;
			//	if (whoUnderCheck->y - whoMakeCheck->y > 0) ky = -1;

			//	int num;

			//	// XY
			//	if (abs(whoMakeCheck->x - whoUnderCheck->x) == abs(whoMakeCheck->y - whoUnderCheck->y)) {
			//		num = (abs(whoMakeCheck->x - whoUnderCheck->x) + abs(whoMakeCheck->y - whoUnderCheck->y)) / 2;
			//	}
			//	// X
			//	else if (whoMakeCheck->x - whoUnderCheck->x != 0) {
			//		num = abs(whoMakeCheck->x - whoUnderCheck->x);
			//	}
			//	// Y
			//	else {
			//		num = abs(whoMakeCheck->y - whoUnderCheck->y);
			//	}

			//	for (int j = 1; j < num; j++) {
			//		if (prevMoves[i].x == startPoint.x + (j * kx) && prevMoves[i].y == startPoint.y + (j * ky)) {
			//			cout << "Start point: " << startPoint.x << "  " << startPoint.y << endl;
			//			cout << "kx: " << kx << "  " << "ky: " << ky << endl;
			//			cout << "num: " << num << endl;

			//			cout << "moveX: " << prevMoves[i].x << endl;
			//			cout << "moveY: " << prevMoves[i].y << endl;

			//			this->moves.push_back(prevMoves[i]);
			//		}
			//		else if (prevMoves[i].x == whoMakeCheck->x && prevMoves[i].y == whoMakeCheck->y) {
			//			this->moves.push_back(prevMoves[i]);
			//		}
			//	}
			//}





		for (int i = 0; i < prevMoves.size(); i++) {
			if ((whoMakeCheck->y == whoUnderCheck->y && whoMakeCheck->y == prevMoves[i].y) || (whoMakeCheck->x == whoUnderCheck->x && whoMakeCheck->x == prevMoves[i].x)) {
				if (wb_moves[prevMoves[i].y][prevMoves[i].x] == whoMakeCheck || board[prevMoves[i].y][prevMoves[i].x] == whoMakeCheck) {
					Point startPoint = { whoUnderCheck->x, whoUnderCheck->y };

					int kx = 0, ky = 0;

					if (whoUnderCheck->x - whoMakeCheck->x < 0) {
						kx = 1;
					}
					else if (whoUnderCheck->x - whoMakeCheck->x > 0) {
						kx = -1;
					}
					if (whoUnderCheck->y - whoMakeCheck->y < 0) {
						ky = 1;
					}
					else if (whoUnderCheck->y - whoMakeCheck->y > 0) {
						ky = -1;
					}

					cout << "Start point: " << startPoint.x << "  " << startPoint.y << endl;
					cout << "kx: " << kx << "  " << "ky: " << ky << endl;

					int num;

					if (whoMakeCheck->x - whoUnderCheck->x == 0) {
						num = abs(whoMakeCheck->y - whoUnderCheck->y);
					}
					else {
						num = abs(whoMakeCheck->x - whoUnderCheck->x);
					}
					
					for (int j = 1; j < num; j++) {
						if (prevMoves[i].x == startPoint.x + (j * kx) && prevMoves[i].y == startPoint.y + (j * ky)) {
							this->moves.push_back(prevMoves[i]);
						}
					}
				}
			}
			else if (abs(whoMakeCheck->x - whoUnderCheck->x) == abs(whoMakeCheck->y - whoUnderCheck->y)) {
				if (board[prevMoves[i].y][prevMoves[i].x] == whoMakeCheck) {
					this->moves.push_back(prevMoves[i]);
				}
				else {
					Point startPoint = { whoUnderCheck->x, whoUnderCheck->y };

					int kx = 0, ky = 0;

					if (whoUnderCheck->x - whoMakeCheck->x < 0) {
						kx = 1;
					}
					else {
						kx = -1;
					}
					if (whoUnderCheck->y - whoMakeCheck->y < 0) {
						ky = 1;
					}
					else {
						ky = -1;
					}

					cout << "Start point: " << startPoint.x << "  " << startPoint.y << endl;
					cout << "kx: " << kx << "  " << "ky: " << ky << endl;

					for (int j = 1; j < abs(whoMakeCheck->x - whoUnderCheck->x); j++) {
						/*cout << startPoint.x + (j * kx) << "|\t|" << startPoint.y + (j * ky) << endl;*/
						if (prevMoves[i].x == startPoint.x + (j * kx) && prevMoves[i].y == startPoint.y + (j * ky)) {
							this->moves.push_back(prevMoves[i]);
						}
					}
				}
			}
			else if (whoMakeCheck->type == 'n' && whoMakeCheck == board[prevMoves[i].y][prevMoves[i].x]) {
				this->moves.push_back(prevMoves[i]);
			}
		}
		}
	}

	void preventFromCheck() {
		bool check = this->white ? wCheck : bCheck;
		auto wb_moves = this->white ? b_moves : w_moves;

		if (wb_moves[this->y][this->x]->type != '0' && wb_moves[this->y][this->x]->type != 'n' && wb_moves[this->y][this->x]->type != 'p' && wb_moves[this->y][this->x]->type != 'k') {

		}
	}
};