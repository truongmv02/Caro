#pragma once

#include <vector>
#include "GameState.h"
#include "Button.h"
#include "CaroChess.h"

class PlayState : public GameState
{
public:
	enum EndState
	{
		NONE,
		PLAYER_O_WIN,
		PLAYER_X_WIN,
		DRAW
	};
	enum GameMode
	{
		PLAYER_VS_PLAYER,
		PLAYER_VS_COMPUTER
	};

	PlayState(int gameMode) :GameState() { this->gameMode = gameMode; }

	void update();
	void render();

	bool onEnter();
	bool onExit();

	std::string getStateID() { return stateID; }

private:
	const static std::string stateID;
	int gameMode;
	void drawBoard(char board[ROWS][COLUMNS]);
	void handleEvents();
	void drawChessBoxChoose(int row, int col);
	void drawChessBoxWin();
	static void playAgain();
	static void backToMenu();
};

