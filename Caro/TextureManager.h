#pragma once
#include <iostream>
#include <string>
#include <map>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class TextureManager
{
public:
	static TextureManager* Instance();
	bool load(std::string path, std::string id, SDL_Renderer* renderer);
	bool load(std::string id, std::string text, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer);
	void draw(std::string id, int x, int y, int width, int height, SDL_Renderer* renderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* renderer, double angle = 0, int alpha = 255, SDL_RendererFlip flip = SDL_FLIP_NONE);
	SDL_Texture* getTexture(std::string id);
	void clean();
	void clearFromTextureMap(std::string id);
	bool isExists(std::string id);

private:
	TextureManager() {}
	static TextureManager* instance;
	std::map<std::string, SDL_Texture*> textureMap;
};

