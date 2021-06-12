struct Point {
	int x, y;
};

bool uniquepred(const Point& p1, const Point& p2) {
	return p1.x == p2.x && p1.y == p2.y;
}

class Piece;
void generateBoardMoves();

Piece* board[8][8];

int w_moves[8][8];
int b_moves[8][8];

bool whitePlay = true;

bool wCheck = false;
bool bCheck = false;

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
	}

	virtual void generateMoves() {}
	virtual void ifCheck() {}

	void move(Point to) {
		if (this->white == whitePlay) {
			for (int i = 0; i < this->moves.size(); i++) {
				if (to.x == this->moves[i].x && to.y == this->moves[i].y) {
					int prev_x = this->x;
					int prev_y = this->y;

					this->x = to.x;
					this->y = to.y;

					board[to.y][to.x] = board[prev_y][prev_x];
					board[prev_y][prev_x] = new Piece('0');

					this->moved = true;

					for (int i = 0; i < 8; i++) {
						for (int j = 0; j < 8; j++) {
							w_moves[i][j] = 0;
							b_moves[i][j] = 0;
						}
					}

					generateBoardMoves();

					whitePlay = !whitePlay;

					break;
				}
			}
		}
	}

	void customMove(Point to) {
		int prev_x = this->x;
		int prev_y = this->y;

		this->x = to.x;
		this->y = to.y;

		board[to.y][to.x] = board[prev_y][prev_x];
		board[prev_y][prev_x] = new Piece('0');

		//generateBoardMoves();

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				w_moves[i][j] = 0;
				b_moves[i][j] = 0;
			}
		}

		/*for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (i != prev_y && j != prev_x) {
					board[i][j]->generateMoves();
				}
			}
		}*/

		generateBoardMoves();

	}

	void moveCheck() {
		auto prevMove = Point{ this->x, this->y };

		//vector<Point> escapeCheckMoves;

		for (int i = 0; i < this->moves.size(); i++) {
			cout << this->moves[i].x << "  " << this->moves[i].y << endl;

			if (board[this->moves[i].y][this->moves[i].x]->type == '0') {
				//cout << "PAWN\n";
				//this->customMove(Point{ this->moves[i].x, this->moves[i].y });
				board[this->y][this->x]->move(Point{ this->moves[i].x, this->moves[i].y });
				this->moved = false;

				whitePlay = this->white;

				//board[this->moves[i].y][this->moves[i].x]->move(Point{ prevMove.x, prevMove.y });

				

				//bool check = this->white ? wCheck : bCheck;

				//if (!wCheck) {
				//	//escapeCheckMoves.push_back(Point{ this->moves[i].x, this->moves[i].y });
				//	cout << "ESCAPE CHECK\n";
				//}
				
				//cout << "CHECK: " << check << "\n\n";
				
				this->customMove(Point{ prevMove.x, prevMove.y });
			}
		}

		//if (check) {
			//this->moves = escapeCheckMoves;
		//}
	}
};