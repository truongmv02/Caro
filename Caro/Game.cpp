#include "Game.h"
#include "InputHandler.h"
#include "MenuState.h"
#include "SoundManager.h"
#include "TextureManager.h"

Game* Game::instance = NULL;

Game* Game::Instance()
{
	return instance = (instance != NULL) ? instance : new Game();
}

bool Game::init(const char* title, int x, int y, int width, int height, bool fullScreen)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << SDL_GetError();
		return false;
	}

	int flags = 0;
	if (fullScreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	window = SDL_CreateWindow(title, x, y, width, height, flags);
	if (window == NULL)
	{
		std::cout << SDL_GetError();
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		std::cout << SDL_GetError();
		return false;
	}
	if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
	{
		return false;
	}
	screenWidth = width;
	screenHeight = height;
	if (TTF_Init() == -1)
	{
		return false;
	}
	SDL_Surface* icon = IMG_Load("assets/image/icon.png");
	SDL_SetWindowIcon(window, icon);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SoundManager::Instance()->load("assets/sound/Click.wav", "Click", SOUND_SFX);
	SoundManager::Instance()->load("assets/sound/PlayChess.wav", "PlayChess", SOUND_SFX);
	gameStateMachine = new GameStateMachine();
	gameStateMachine->changeState(new MenuState());

	running = true;
	return true;
}

void Game::handleEvents()
{
	InputHandler::Instance()->update();
}

void Game::update()
{
	gameStateMachine->update();
}

void Game::render()
{
	SDL_RenderClear(renderer);
	gameStateMachine->render();
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	if (window != NULL)
	{
		SDL_DestroyWindow(window);
	}

	if (renderer != NULL)
	{
		SDL_DestroyRenderer(renderer);
	}
	TextureManager::Instance()->clean();
	SDL_Quit();
	IMG_Quit();
	TTF_Quit();
}
