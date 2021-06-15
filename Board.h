#include <string>

void generateBoardMoves() {
	wCheck = 0, bCheck = 0;

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			board[i][j]->generateMoves();
		}
	}

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j]->type == 'k') {
				board[i][j]->generateMoves();
			}
			else {
				board[i][j]->attackPriority();
				board[i][j]->secureFromCheck();
				board[i][j]->preventFromCheck();
			}
		}
	}
}

void generateBoard(string fen) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			board[i][j] = new Piece('0');
		}
	}

	int x = 0, y = 0;

	for (int i = 0; i < fen.size(); i++) {
		if (tolower(fen[i]) == 'p') {
			board[y][x] = new Pawn(x, y, fen[i] == 'P', tolower(fen[i]));
		}
		if (tolower(fen[i]) == 'n') {
			board[y][x] = new Knight(x, y, fen[i] == 'N', tolower(fen[i]));
		}
		if (tolower(fen[i]) == 'b') {
			board[y][x] = new Bishop(x, y, fen[i] == 'B', tolower(fen[i]));
		}
		if (tolower(fen[i]) == 'r') {
			board[y][x] = new Rook(x, y, fen[i] == 'R', tolower(fen[i]));
		}
		if (tolower(fen[i]) == 'q') {
			board[y][x] = new Queen(x, y, fen[i] == 'Q', tolower(fen[i]));
		}
		if (tolower(fen[i]) == 'k') {
			board[y][x] = new King(x, y, fen[i] == 'K', tolower(fen[i]));
		}

		if (isdigit(fen[i])) {
			x += fen[i] - '0';
		}
		else if (fen[i] == '/') {
			y++;
			x = 0;
		}
		else {
			x++;
		}
	}

	generateBoardMoves();
}

void printBoard() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j]->type != '0') {
				if (board[i][j]->white) cout << "w";
				else cout << "b";

				cout
					<< (char)toupper(board[i][j]->type)
					<< "\t" << board[i][j]->x
					<< "\t" << board[i][j]->y
					<< endl;

				// Moves
				for (int k = 0; k < board[i][j]->moves.size(); k++) {
					cout << "\t\t\t-> " << board[i][j]->moves[k].x << " " << board[i][j]->moves[k].y << endl;
				}
			}
		}
	}
}