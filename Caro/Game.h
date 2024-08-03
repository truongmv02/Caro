#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "GameStateMachine.h"
#include "MenuState.h"

class Game
{
public:
	static Game* Instance();
	bool init(const char* title, int x, int y, int width, int height, bool fullScreen);
	bool isRunning() { return running; }

	void render();
	void update();
	void handleEvents();

	int getWidth() { return screenWidth; }
	int getHeight() { return screenHeight; }
	
	SDL_Renderer* getRenderer() { return renderer; }
	GameStateMachine* getGameStateMachine() { return gameStateMachine; }

	void clean();
	void quit() { running = false; }
private:
	Game() {}
	static	Game* instance;
	
	GameStateMachine* gameStateMachine;

	SDL_Window* window;
	SDL_Renderer* renderer;

	int screenWidth;
	int screenHeight;

	bool running;
};
