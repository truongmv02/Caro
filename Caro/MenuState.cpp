#include "MenuState.h"
#include "TextureManager.h"
#include "Game.h"
#include "Button.h"
#include "PlayState.h"
#include "InputHandler.h"

const std::string MenuState::stateID = "MENU";

SDLGameObject* background = NULL;
Button* PVPBtn = NULL;
Button* PVCBtn = NULL;
Button* exitBtn = NULL;

void MenuState::update()
{
	if (!loadingComplete || exiting) { return; }
	if (PVPBtn != NULL) { PVPBtn->update(); }
	if (PVCBtn != NULL) { PVCBtn->update(); }
	if (exitBtn != NULL) { exitBtn->update(); }
}

void MenuState::render()
{
	if (!loadingComplete || exiting) { return; }
	if (background != NULL) { background->draw(); }
	if (PVPBtn != NULL) { PVPBtn->draw(); }
	if (PVCBtn != NULL) { PVCBtn->draw(); }
	if (exitBtn != NULL) { exitBtn->draw(); }
}

bool MenuState::onEnter()
{
	TextureManager::Instance()->load("assets/image/PlayerVsPlayer.png", "PVPButton", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/image/PlayerVsComputer.png", "PVCButton", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/image/Exit1.png", "ExitButton1", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("assets/image/BackgroundMenu.png", "backgroundMenu", Game::Instance()->getRenderer());

	int x = (Game::Instance()->getWidth() - 400) / 2;
	int y = (Game::Instance()->getHeight() - 100) / 2;

	background = new SDLGameObject(std::unique_ptr<LoadParams>(new LoadParams(0, 0, 1140, 720, "backgroundMenu")));
	PVPBtn = new Button(std::unique_ptr<LoadParams>(new LoadParams(x, y, 400, 100, "PVPButton")), playPVP);
	PVCBtn = new Button(std::unique_ptr<LoadParams>(new LoadParams(x, y + 130, 400, 100, "PVCButton")), playPVC);
	exitBtn = new Button(std::unique_ptr<LoadParams>(new LoadParams(x, y + 130 * 2, 400, 100, "ExitButton1")), exitFromMenu);

	loadingComplete = true;
	return true;
}

bool MenuState::onExit()
{
	exiting = true;
	delete background;
	delete exitBtn;
	delete PVCBtn;
	delete PVPBtn;
	background = NULL;
	exitBtn = NULL;
	PVCBtn = NULL;
	PVPBtn = NULL;
	TextureManager::Instance()->clearFromTextureMap("backgroundMenu");
	TextureManager::Instance()->clearFromTextureMap("PVPButton");
	TextureManager::Instance()->clearFromTextureMap("PVCButton");
	TextureManager::Instance()->clearFromTextureMap("ExitButton1");
	InputHandler::Instance()->reset();
	return true;
}

void MenuState::playPVP()
{
	Game::Instance()->getGameStateMachine()->changeState(new PlayState(PlayState::GameMode::PLAYER_VS_PLAYER));
}

void MenuState::playPVC()
{
	Game::Instance()->getGameStateMachine()->changeState(new PlayState(PlayState::GameMode::PLAYER_VS_COMPUTER));
}

void MenuState::exitFromMenu()
{
	Game::Instance()->quit();
}