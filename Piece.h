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
};