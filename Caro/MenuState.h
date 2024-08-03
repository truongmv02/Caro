#pragma once

#include <vector>
#include "GameState.h"
#include "GameObject.h"

class MenuState : public GameState
{
public:
	virtual void update();
	virtual void render();
	virtual bool onEnter(); 
	virtual bool onExit();
	virtual std::string getStateID() { return stateID; }
private:
	const static std::string stateID;

	static void playPVP();
	static void playPVC();
	static void exitFromMenu();
};

