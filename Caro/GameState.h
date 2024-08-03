#pragma once
#include <string>
#include "InputHandler.h"

class GameState
{
public:
	virtual void update() = 0;
	virtual void render() = 0;
	virtual bool onEnter() = 0;
	virtual bool onExit() = 0;
	virtual std::string getStateID() =0;

protected:
	GameState():loadingComplete(false), exiting(false){}
	bool loadingComplete;
	bool exiting;
};

