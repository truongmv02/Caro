#include "GameStateMachine.h"

void GameStateMachine::update() {
	if (!gameStates.empty()) {
		gameStates.back()->update();
	}
}

void GameStateMachine::render() {
	if (!gameStates.empty()) {
		gameStates.back()->render();
	}
}

void GameStateMachine::pushState(GameState* state) {
	gameStates.push_back(state);
	gameStates.back()->onEnter();
}

void GameStateMachine::changeState(GameState* state) {
	if (!gameStates.empty()) {
		if (gameStates.back()->getStateID() == state->getStateID()) {
			return;
		}
		if (gameStates.back()->onExit()) {
			delete gameStates.back();
			gameStates.pop_back();
		}
	}
	gameStates.push_back(state);
	gameStates.back()->onEnter();
}

void GameStateMachine::popState() {
	if (!gameStates.empty()) {
		gameStates.back()->onExit();
		delete gameStates.back();
		gameStates.pop_back();
	}
}

 