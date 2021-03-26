#include "Chess.h"
#include <iostream>
using namespace std;

//newGame gets the board ready to be played, setting every piece in its starting place
//bp = black pawn, wr = white rook, bn = black knight, wb = white bishop, bq = black queen, wk = white king
//M = empty spot
void Chess::newGame() {
	fill(*board, *board + 8 * 8, "M");
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (i == seven)
				board[i][j] = "bp";
			if (i == two)
				board[i][j] = "wp";
			if (i == eight && (j == a || j == h))
				board[i][j] = "br";
			if (i == one && (j == a || j == h))
				board[i][j] = "wr";
			if (i == eight && (j == b || j == g))
				board[i][j] = "bn";
			if (i == one && (j == b || j == g))
				board[i][j] = "wn";
			if (i == eight && (j == c || j == f))
				board[i][j] = "bb";
			if (i == one && (j == c || j == f))
				board[i][j] = "wb";
			if (i == eight && j == d)
				board[i][j] = "bq";
			if (i == one && j == d)
				board[i][j] = "wq";
			if (i == eight && j == e)
				board[i][j] = "bk";
			if (i == one && j == e)
				board[i][j] = "wk";
		}
	}
}

void Chess::displayBoard() {
	cout << "  " << "a  b  c  d  e  f  g  h" << endl;
	for (int i = 0; i < 8; i++) {
		cout << 8 - i << " ";
		for (int j = 0; j < 8; j++) {
			if (board[i][j] == "M")
				cout << board[i][j] << "  ";
			else
				cout << board[i][j] << " ";
		}
		cout << 8 - i << endl;
	}
	cout << "  " << "a  b  c  d  e  f  g  h" << endl;
}

bool Chess::getCurrentPlayer() {
	return currentPlayer;
}

void Chess::switchCurrentPlayer() {
	currentPlayer = !currentPlayer;
}

bool Chess::inputErrorCheck(string move) {
	//97 - 104 range of 'a' to 'h' in ascii
	//49 - 56 range of '1' to '8' in ascii
	if (move[0] < 97 && move[0] > 104 && move[3] < 97 && move[3] > 104 && move[1] < 49 && move[1] > 56 && move[4] < 49 && move[4] > 56)
		return 1;
	else
		return 0;
}

void Chess::move(int sX, int sY, int tX, int tY) {
	string piece;
	piece = board[sY][sX];
	board[sY][sX] = "M";
	board[tY][tX] = piece;
}

bool Chess::validateMove(string move) {
	if (inputErrorCheck(move) == 1)
		return 0;
	else {
		char check;
		int sourceX = move[0] - 97, sourceY = -(move[1] - 56), targetX = move[3] - 97, targetY = -(move[4] - 56); //converting the string moves into integers for work with the board
		check = board[sourceY][sourceX][1]; //checking what's the letter for the piece's type
		switch (check) {
		case 'p':
			if (validatePawn(sourceX, sourceY, targetX, targetY) == 1)
				return 1;
			else return 0;
		case 'r':
			if (validateRook(sourceX, sourceY, targetX, targetY) == 1)
				return 1;
			else return 0;
		case 'n':
			if (validateKnight(sourceX, sourceY, targetX, targetY) == 1)
				return 1;
			else return 0;
		case 'b':
			if (validateBishop(sourceX, sourceY, targetX, targetY) == 1)
				return 1;
			else return 0;
		case 'q':
			if (validateQueen(sourceX, sourceY, targetX, targetY) == 1)
				return 1;
			else return 0;
		case 'k':
			if (validateKing(sourceX, sourceY, targetX, targetY) == 1)
				return 1;
			else return 0;
		}
	}
}

bool Chess::validateKing(int sX, int sY, int tX, int tY) {
	if (currentPlayer == 0 && board[sY][sX] == "wk" || currentPlayer == 1 && board[sY][sX] == "bk") { //if king corresponds to player color
		if (((tY == sY + 1 || tY == sY - 1) && tX == sX + 1 || tX == sX || tX == sX - 1) || (tY == sY && tX == sX + 1 || tX == sX - 1)) { //if king moves in either direction by 1
			if (board[tY][tX] == "M") { //if the king's target position is unoccupied
				move(sX, sY, tX, tY);
				return 1;
			}
		}
		else if ((tX < sX && currentPlayer == 0 && board[one][a] == "wr" || currentPlayer == 1 && board[eight][a] == "br") //if conditions meet for a left castling
			&& board[sY][b] == "M" && board[sY][c] == "M" && board[sY][d] == "M") {
			move(sX, sY, tX, tY);
			move(a, sY, tX + 1, tY);
			return 1;
		}
		else if (tX > sX && currentPlayer == 0 && board[one][h] == "wr" || currentPlayer == 1 && board[eight][h] == "br" //if conditions meet for a right castling
			&& board[sY][f] == "M" && board[sY][g] == "M") {
			move(sX, sY, tX, tY);
			move(h, sY, tX - 1, tY);
			return 1;
		}
		else return 0;
	}
	else return 0;
}

bool Chess::validateQueen(int sX, int sY, int tX, int tY) {
	if (currentPlayer == 0 && board[sY][sX][0] == 'w' || currentPlayer == 1 && board[sY][sX][0] == 'b') { //if the piece corresponds to the player's color

		if (tX == sX && sY != tY || tY == sY && sX != tX) { //if by given coords it'll make a vertival or horizontal move
			if (validateRook(sX, sY, tX, tY) == 1)
				return 1;
			else return 0;
		}
		else if (tY - sY == tX - sX && tY != sY && tX != sX) { //if by given coords it'll make a correct diagonal move
			if (validateBishop(sX, sY, tX, tY) == 1)
				return 1;
			else return 0;
		}
		else return 0;
	}
	else return 0;
}

bool Chess::validateRook(int sX, int sY, int tX, int tY) {
	bool pass = 1;
	if (currentPlayer == 0 && board[sY][sX][0] == 'w' || currentPlayer == 1 && board[sY][sX][0] == 'b') { //if the piece corresponds to the player's color

		if (tX == sX && sY != tY) { //is it a vertical move

			for (int i = 1; i < abs(tY - sY) - 1; i++) { //checking if there is any piece in the rook's way except the last tile where it'll land on
				if (tY > sY) { //movement down
					if (board[sY + i][sX] != "M" && tY != sY + 1) {
						pass = 0;
						break;
					}
				}
				else { //movement up
					if (board[sY - i][sX] != "M" && tY != sY - 1) {
						pass = 0;
						break;
					}
				}
			}
		}
		else if (tY == sY && sX != tX) { //is it a horizontal move

			for (int i = 1; i < abs(tX - sX) - 1; i++) { //checking if there is any piece in the rook's way except the last tile where it'll land on
				if (tX > sX) { //movement right
					if (board[sY][sX + i] != "M" && tX != sX + 1) {
						pass = 0;
						break;
					}
				}
				else { //movement left
					if (board[sY][sX - i] != "M" && tX != sX - 1) {
						pass = 0;
						break;
					}
				}
			}
		}
		if (pass == 1)
			move(sX, sY, tX, tY);
		return pass;
	}
	else return 0;
}

bool Chess::validateBishop(int sX, int sY, int tX, int tY) {
	bool pass = 1;
	if (currentPlayer == 0 && board[sY][sX][0] == 'w' || currentPlayer == 1 && board[sY][sX][0] == 'b') { //if the piece corresponds to the player's color

		if (tY - sY == tX - sX && tY != sY && tX != sX) { //if bishop will move in a correct diagonal manner

				for (int i = 1; i < abs(tY - sY) - 1; i++) {
					if (tY < sY) {
						if (board[sY - i][sX + i] != "M" && tX != sX - 1 && tY != sY + 1) { //right and up
							pass = 0;
							break;
						}
						else if (board[sY - i][sX - i] != "M" && tX != sX - 1 && tY != sY - 1) { // left and up
							pass = 0;
							break;
						}
					}
					else {
						if (board[sY + i][sX + i] != "M" && tX != sX + 1 && tY != sY + 1) { //right and down
							pass = 0;
							break;
						}
						else if (board[sY + i][sX - i] != "M" && tX != sX + 1 && tY != sY - 1) { //left and down
							pass = 0;
							break;
						}
					}
				}
				if (pass == 1)
					move(sX, sY, tX, tY);
				return pass;
		}
		else return 0;
	}
	else return 0;
}

bool Chess::validateKnight(int sX, int sY, int tX, int tY) {
	if (currentPlayer == 0 && board[sY][sX] == "wn" || currentPlayer == 1 && board[sY][sX] == "bn") { //if knight corresponds to current player
		if ((tY == sY - 2 || tY == sY + 2 && tX == sX - 1 || tX == sX + 1) || (tX == sX + 2 || tX == sX - 2 && tY == sY - 1 || tY == sY + 1)) { //checks all possible moves for knight
			if ((currentPlayer == 0 && board[tY][tX][0] == 'b' || currentPlayer == 1 && board[tY][tX][0] == 'w') && board[tY][tX][1] != 'k' || board[tY][tX] == "M") { //if targeted piece is enemy, not king, or an empty space
				move(sX, sY, tX, tY);
				return 1;
			}
		}
		else return 0;
	}
	else return 0;
}

bool Chess::validatePawn(int sX, int sY, int tX, int tY) {
	if (currentPlayer == 0 && board[sY][sX] == "wp" || currentPlayer == 1 && board[sY][sX] == "bp") { //if pawn corresponds to current player
		if (sX == tX) { //if pawn won't move left or right
			if (board[tY][tX] == "M" && (currentPlayer == 0 && sY == two && tY == sY - 1 || tY == sY - 2 && board[tY + 1][tX] == "M") //if it's the pawn's first move and the player is moving it by 1 or 2 tiles for white
				|| (currentPlayer == 1 && sY == seven && tY == sY + 1 || tY == sY + 2 && board[tY - 1][tX] == "M")) { //for black
				move(sX, sY, tX, tY);
				return 1;
			}
			else if (board[tY][tX] == "M" && (currentPlayer == 0 && sY != two && tY == sY - 1) //if it's not the pawn's first move and the player is moving it only by one tile for white
				|| (currentPlayer == 1 && sY != seven && tY == sY + 1)) { //for black
				move(sX, sY, tX, tY);
				return 1;
			}
			else return 0;
		}
		else if (board[tY][tX] == "M" && (currentPlayer == 0 && tX == sX + 1 || tX == sX - 1 && tY == sY - 1 && board[tY][tX][0] == 'b' && board[tY][tX][1] != 'k') //if player is moving pawn by one tile diagonally with an opponent pawn on his left or right inner side (EN PASSANT)
			|| (currentPlayer == 1 && tX == sX + 1 || tX == sX - 1 && tY == sY + 1 && board[tY][tX][0] == 'w' && board[tY][tX][1] != 'k')) { //for black
			move(sX, sY, tX, tY);
			board[sY][tX] == "M";
			return 1;
		}
		else if ((currentPlayer == 0 && tX == sX + 1 || tX == sX - 1 && tY == sY - 1 && board[tY][tX][0] == 'b' && board[tY][tX][1] != 'k') //CAPTURE for white
			|| (currentPlayer == 1 && tX == sX + 1 || tX == sX - 1 && tY == sY + 1 && board[tY][tX][0] == 'w' && board[tY][tX][1] != 'k')) { //for black
			move(sX, sY, tX, tY);
			return 1;
		}
		else if ((currentPlayer == 0 && tX == sX && sY == seven && tY == eight) //PROMOTION
			|| (currentPlayer == 1 && tX == sX && sY == two && tY == one)) { //for black
			int pr;
			move(sX, sY, tX, tY);
			cout << "What piece do you want to promote your pawn to?" << endl << "1 - Queen" << endl << "2 - Bishop" << endl << "3 - Knight" << endl << "4 - Rook" << endl;
			do {
				cin >> pr;
				switch (pr) {
				case 1:
					board[tY][tX] = "wq";
					break;
				case 2:
					board[tY][tX] = "wb";
					break;
				case 3:
					board[tY][tX] = "wn";
					break;
				case 4:
					board[tY][tX] = "wr";
					break;
				}
			} while (pr < 1 || pr > 4);
			return 1;
		}
		else return 0;
	}
	else return 0;
}