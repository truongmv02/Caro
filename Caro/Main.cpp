#include "Game.h"
const int FPS = 60;
const int DELAY_TIME = 1000 / FPS;

int main(int argc, char *arvg[])
{
	if (!Game::Instance()->init("Caro", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1140, 720, false))
	{
		return 0;
	}
	int frameStart, frameTime;
	while (Game::Instance()->isRunning())
	{
		frameStart = SDL_GetTicks();
		Game::Instance()->handleEvents();
		Game::Instance()->update();
		Game::Instance()->render();
		InputHandler::Instance()->reset();
		frameTime = SDL_GetTicks() - frameStart;
		if (frameTime < DELAY_TIME)
		{
			SDL_Delay(DELAY_TIME - frameTime);
		}
	}

	Game::Instance()->clean();

	return 0;
}