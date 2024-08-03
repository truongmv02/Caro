#pragma once

#include "InputHandler.h"
#include "Game.h"
#include "TextureManager.h"
#include "Definitions.h"

class CaroChess
{
public:

	CaroChess();
	~CaroChess();

	bool addNewChessBox(int row, int col);

	void findPosition(int& row, int& col);
	bool isPlayO() { return turn == PLAYER_O; }
	int checkEndGame(int row, int col);

	char board[ROWS][COLUMNS];
private:
	int turn;

	int getAttackScore1(int row, int col);
	int getAttackScore2(int row, int col);
	int getAttackScore3(int row, int col);
	int getAttackScore4(int row, int col);

	int getDefenseScore1(int row, int col);
	int getDefenseScore2(int row, int col);
	int getDefenseScore3(int row, int col);
	int getDefenseScore4(int row, int col);
};
