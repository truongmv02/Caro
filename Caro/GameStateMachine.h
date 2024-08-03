#pragma once

#include <vector>
#include "GameState.h"

class GameStateMachine
{
public:
	void update();
	void render();

	void pushState(GameState* state);
	void changeState(GameState* state);
	void popState();

private:
	std::vector<GameState*> gameStates;
};