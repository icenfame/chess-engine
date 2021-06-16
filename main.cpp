#include <SFML/Graphics.hpp>
#include <windows.h>

#include <iostream>
#include <vector>

using namespace std;
using namespace sf;

#include "Piece.h"

#include "Queen.h"
#include "Pawn.h"
#include "Knight.h"
#include "Bishop.h"
#include "Rook.h"
#include "King.h"

#include "Board.h"

int main()
{
	RenderWindow window(VideoMode(800, 800), "Chess", Style::Titlebar | Style::Close);
	window.setFramerateLimit(60);

	Texture t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13;

	t1.loadFromFile("res/board.png");
	t2.loadFromFile("res/wP.png");
	t3.loadFromFile("res/bP.png");
	t4.loadFromFile("res/wB.png");
	t5.loadFromFile("res/bB.png");
	t6.loadFromFile("res/wN.png");
	t7.loadFromFile("res/bN.png");
	t8.loadFromFile("res/wR.png");
	t9.loadFromFile("res/bR.png");
	t10.loadFromFile("res/wQ.png");
	t11.loadFromFile("res/bQ.png");
	t12.loadFromFile("res/wK.png");
	t13.loadFromFile("res/bK.png");

	Sprite board_img(t1);
	Sprite wP(t2);
	Sprite bP(t3);
	Sprite wB(t4);
	Sprite bB(t5);
	Sprite wN(t6);
	Sprite bN(t7);
	Sprite wR(t8);
	Sprite bR(t9);
	Sprite wQ(t10);
	Sprite bQ(t11);
	Sprite wK(t12);
	Sprite bK(t13);

	CircleShape legalMove(15);
	legalMove.setFillColor(Color(58, 98, 171));

	RectangleShape attackMove(Vector2f(100, 100));
	attackMove.setFillColor(Color(181, 48, 48));

	Font font;
	if (!font.loadFromFile("res/arial.ttf")) {
		cout << "NEMA FONT\a";
	}

	Text text;
	text.setFont(font);

	int clickX = 0;
	int clickY = 0;

	bool clicked = false;

	generateBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");

	// Test FEN's

	//generateBoard("4r2k/b7/8/4r3/6N1/3q4/8/2B1K3");
	//generateBoard("7k/b7/8/8/8/3q4/8/4K1r1");

	//generateBoard("8/6p1/2p3kp/P1Np1p2/3P3P/2P3P1/5q1K/1Q2n3");

	printBoard();

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::MouseButtonPressed) {
				int prevX = clickX;
				int prevY = clickY;

				clickX = Mouse::getPosition(window).x / 100;
				clickY = Mouse::getPosition(window).y / 100;

				clicked = true;

				if (board[prevY][prevX]->type != '0') {
					board[prevY][prevX]->move(Point{ clickX, clickY });
				}
			}
		}

		window.clear();
		window.draw(board_img);

		if (clicked) {
			int mouseX = clickX;
			int mouseY = clickY;

			if (board[mouseY][mouseX]->type != '0' && board[mouseY][mouseX]->white == whitePlay) {
				for (int i = 0; i < board[mouseY][mouseX]->moves.size(); i++) {
					if (board[board[mouseY][mouseX]->moves[i].y][board[mouseY][mouseX]->moves[i].x]->type != '0' && board[board[mouseY][mouseX]->moves[i].y][board[mouseY][mouseX]->moves[i].x]->white != whitePlay) {
						attackMove.setPosition(board[mouseY][mouseX]->moves[i].x * 100, board[mouseY][mouseX]->moves[i].y * 100);
						window.draw(attackMove);
					}
					else {
						legalMove.setPosition(board[mouseY][mouseX]->moves[i].x * 100 + 35, board[mouseY][mouseX]->moves[i].y * 100 + 35);
						window.draw(legalMove);
					}
				}
			}
		}

		for (int i = 0; i < 8; i++) {
			text.setPosition(Vector2f(1, 100 * i));
			text.setString(to_string(8 - i));
			text.setCharacterSize(15);
			text.setFillColor(i % 2 == 0 ? Color(181, 136, 99) : Color(240, 217, 181));
			text.setStyle(Text::Bold);

			window.draw(text);

			text.setPosition(Vector2f(100 - 12 + 100 * i, 700));
			text.setString((char)('A' + i));
			text.setCharacterSize(14);
			text.setFillColor(i % 2 ? Color(181, 136, 99) : Color(240, 217, 181));
			text.setStyle(Text::Bold);

			window.draw(text);

			for (int j = 0; j < 8; j++) {
				if (board[i][j]->type == 'p') {
					if (board[i][j]->white) {
						wP.setPosition(j * 100, i * 100);
						window.draw(wP);
					}
					else {
						bP.setPosition(j * 100, i * 100);
						window.draw(bP);
					}
				}
				if (board[i][j]->type == 'n') {
					if (board[i][j]->white) {
						wN.setPosition(j * 100, i * 100);
						window.draw(wN);
					}
					else {
						bN.setPosition(j * 100, i * 100);
						window.draw(bN);
					}
				}
				if (board[i][j]->type == 'b') {
					if (board[i][j]->white) {
						wB.setPosition(j * 100, i * 100);
						window.draw(wB);
					}
					else {
						bB.setPosition(j * 100, i * 100);
						window.draw(bB);
					}
				}
				if (board[i][j]->type == 'r') {
					if (board[i][j]->white) {
						wR.setPosition(j * 100, i * 100);
						window.draw(wR);
					}
					else {
						bR.setPosition(j * 100, i * 100);
						window.draw(bR);
					}
				}
				if (board[i][j]->type == 'q') {
					if (board[i][j]->white) {
						wQ.setPosition(j * 100, i * 100);
						window.draw(wQ);
					}
					else {
						bQ.setPosition(j * 100, i * 100);
						window.draw(bQ);
					}
				}
				if (board[i][j]->type == 'k') {
					if (board[i][j]->white) {
						wK.setPosition(j * 100, i * 100);
						window.draw(wK);
					}
					else {
						bK.setPosition(j * 100, i * 100);
						window.draw(bK);
					}
				}
			}
		}

		window.display();

		// CHECKMATE
		if (checkMate || pat) {
			string whoWin;

			if (checkMate) {
				whoWin = !whitePlay ? "Білі виграли! Хочете зіграти ще раз?" : "Чорні виграли! Хочете зіграти ще раз?";
			}
			else if (pat) {
				whoWin = "Нічия! Хочете зіграти ще раз?";
			}
			
			int choice = MessageBoxA(NULL, whoWin.c_str(), "Кінець гри", MB_YESNO);

			if (choice == IDYES) {
				generateBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");

				checkMate = false;
				pat = false;

				wCheck = 0;
				bCheck = 0;

				whitePlay = true;
				clicked = false;
			}
			else {
				exit(0);
			}
		}
	}

	return 0;
}