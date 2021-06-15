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

bool checkMate = false;

Piece* wKing;
Piece* bKing;

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

			cout << "Who make check: " << whoMakeCheck->type << endl;

			for (int i = 0; i < prevMoves.size(); i++) {
				Point startPoint = { whoUnderCheck->x, whoUnderCheck->y };

				int kx = 0, ky = 0;

				if (whoUnderCheck->x - whoMakeCheck->x < 0) kx = 1;
				if (whoUnderCheck->x - whoMakeCheck->x > 0) kx = -1;

				if (whoUnderCheck->y - whoMakeCheck->y < 0) ky = 1;
				if (whoUnderCheck->y - whoMakeCheck->y > 0) ky = -1;

				int num;

				// XY
				if (abs(whoMakeCheck->x - whoUnderCheck->x) == abs(whoMakeCheck->y - whoUnderCheck->y)) {
					num = (abs(whoMakeCheck->x - whoUnderCheck->x) + abs(whoMakeCheck->y - whoUnderCheck->y)) / 2;
				}
				// X
				else if (whoMakeCheck->x - whoUnderCheck->x != 0) {
					num = abs(whoMakeCheck->x - whoUnderCheck->x);
				}
				// Y
				else {
					num = abs(whoMakeCheck->y - whoUnderCheck->y);
				}

				for (int j = 1; j <= num; j++) {
					if (prevMoves[i].x == startPoint.x + (j * kx) && prevMoves[i].y == startPoint.y + (j * ky)) {
						/*cout << "Start point: " << startPoint.x << "  " << startPoint.y << endl;
						cout << "kx: " << kx << "  " << "ky: " << ky << endl;
						cout << "num: " << num << endl;

						cout << "moveX: " << prevMoves[i].x << endl;
						cout << "moveY: " << prevMoves[i].y << endl;*/

						this->moves.push_back(prevMoves[i]);
					}
					else if (prevMoves[i].x == whoMakeCheck->x && prevMoves[i].y == whoMakeCheck->y) {
						this->moves.push_back(prevMoves[i]);
					}
				}
			}
		}
	}

	void preventFromCheck() {
		auto king = this->white ? wKing : bKing;
		auto wb_moves = this->white ? b_moves : w_moves;

		auto prevMoves = this->moves;


		if (wb_moves[this->y][this->x]->type != '0' && wb_moves[this->y][this->x]->type != 'n' && wb_moves[this->y][this->x]->type != 'p' && wb_moves[this->y][this->x]->type != 'k') {
			if (wb_moves[this->y][this->x]->x == king->x || wb_moves[this->y][this->x]->y == king->y || abs(wb_moves[this->y][this->x]->x - king->x) == abs(wb_moves[this->y][this->x]->y - king->y)) {
					
				Point startPoint = { king->x, king->y };

				int kx = 0, ky = 0;

				if (king->x - wb_moves[this->y][this->x]->x < 0) kx = 1;
				if (king->x - wb_moves[this->y][this->x]->x > 0) kx = -1;

				if (king->y - wb_moves[this->y][this->x]->y < 0) ky = 1;
				if (king->y - wb_moves[this->y][this->x]->y > 0) ky = -1;

				int num;

				// XY
				if (abs(wb_moves[this->y][this->x]->x - king->x) == abs(wb_moves[this->y][this->x]->y - king->y)) {
					num = (abs(wb_moves[this->y][this->x]->x - king->x) + abs(wb_moves[this->y][this->x]->y - king->y)) / 2;
				}
				// X
				else if (wb_moves[this->y][this->x]->x - king->x != 0) {
					num = abs(wb_moves[this->y][this->x]->x - king->x);
				}
				// Y
				else {
					num = abs(wb_moves[this->y][this->x]->y - king->y);
				}

				int pieces = 0;

				for (int j = 1; j <= num; j++) {
					/*cout << "Start point: " << startPoint.x << "  " << startPoint.y << endl;
					cout << "kx: " << kx << "  " << "ky: " << ky << endl;
					cout << "num: " << num << endl;*/

					if (board[startPoint.y + (j * ky)][startPoint.x + (j * kx)]->type != '0') {
						pieces++;

						if (pieces >= 2) break;
					}

					if (board[startPoint.y + (j * ky)][startPoint.x + (j * kx)] == this) {
						this->moves.clear();

						for (int i = 0; i < prevMoves.size(); i++) {
							for (int k = 1; k <= num; k++) {
								if (prevMoves[i].x == startPoint.x + (k * kx) && prevMoves[i].y == startPoint.y + (k * ky)) {
									this->moves.push_back(prevMoves[i]);
								}
							}
						}

						break;
					}
				}
			}
		}
	}

	void attackPriority() {
		auto king = this->white ? wKing : bKing;
		auto wb_moves = this->white ? b_moves : w_moves;

		for (int i = 0; i < this->moves.size(); i++) {
			if (wb_moves[this->moves[i].y][this->moves[i].x]->type == '0') {
				if (this->white) {
					w_moves[this->moves[i].y][this->moves[i].x] = this;
				}
				else {
					b_moves[this->moves[i].y][this->moves[i].x] = this;
				}
			}
			else if (this->x == king->x || this->y == king->y || abs(this->x - king->x) == abs(this->y - king->y)) {
				if (this->white) {
					w_moves[this->moves[i].y][this->moves[i].x] = this;
				}
				else {
					b_moves[this->moves[i].y][this->moves[i].x] = this;
				}
			}
		}
	}
};