#pragma once
#include <iostream>
using namespace std;

enum coordDigits {
	eight, seven, six, five, four, three, two, one
};
enum coordChars {
	a, b, c, d, e, f, g, h
}; //enums will be used to more easily write code regarding the board as the Y axis is reversed (in c++ the first row is 0 while in chess it's 8)

class Chess {
private:
	string board[8][8];
	bool currentPlayer = 0;
public:
	void newGame();
	void displayBoard();
	bool getCurrentPlayer();
	void switchCurrentPlayer();
	bool validateMove(string move);
	bool inputErrorCheck(string move);
	bool validateKing(int sX, int sY, int tX, int tY);
	bool validateQueen(int sX, int sY, int tX, int tY);
	bool validateRook(int sX, int sY, int tX, int tY);
	bool validateBishop(int sX, int sY, int tX, int tY);
	bool validateKnight(int sX, int sY, int tX, int tY);
	bool validatePawn(int sX, int sY, int tX, int tY);
	void move(int sX, int sY, int tX, int tY);
};

