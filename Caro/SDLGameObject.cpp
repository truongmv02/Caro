#include "SDLGameObject.h"
#include "TextureManager.h"
#include "Game.h"

SDLGameObject::SDLGameObject() :GameObject(), positionFrame(0, 0)
{
	currentFrame = 0;
	currentRow = 1;
}

 SDLGameObject::SDLGameObject(std::unique_ptr<LoadParams> const& params):GameObject(params), positionFrame(params->getX(), params->getY()) {
	widthFrame = params->getWidth();
	heightFrame = params->getHeight();
	textureID = params->getTextureID();
	currentFrame = 0;
	currentRow = 1;
}

void SDLGameObject::update() {
	
}

void SDLGameObject::draw() {
	TextureManager::Instance()->drawFrame(textureID, positionFrame.X, positionFrame.Y,
		widthFrame, heightFrame, currentRow, currentFrame, Game::Instance()->getRenderer());
}

