#include "Chess.h"
#include <iostream>
using namespace std;

int main() {
	string answer, ending;
	string wrongMoves[100];
	int wrongMovesIndex = 0;
	bool haveWrongMove = 0;
	string move;
	Chess game;
	game.newGame();
	cout << "Welcome to the chess moves validator! Player 1 is white (goes first) and Player 2 is black" << endl;
	do {
		cout << "This is the board right now:" << endl;
		game.displayBoard();

		do {
			cout << "Do you want to continue? (y/n) ";
			cin >> ending;
		} while (ending != "y" && ending != "n");

		if (ending == "y") {
			cout << "Player " << game.getCurrentPlayer() + 1 << " enter your move in the format [letter][digit]-[letter][digit] (e.g. b2-b3): ";
			cin >> move;
			if (game.validateMove(move) == 0) {
				wrongMoves[wrongMovesIndex] = move;
				wrongMovesIndex++;
				haveWrongMove++;
			}

			game.switchCurrentPlayer();
		}

		system("cls");
	} while (ending == "y");

	if (haveWrongMove == false)
		cout << "All moves are valid!" << endl;
	else {
		cout << "The invalid moves are: " << endl;
		for (int i = 0; i < wrongMovesIndex + 1; i++)
			cout << wrongMoves[i] << endl;
	}

	system("pause");
	return 0;
}