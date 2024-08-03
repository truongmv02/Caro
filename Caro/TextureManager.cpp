#include "TextureManager.h"

TextureManager* TextureManager::instance = NULL;

TextureManager* TextureManager::Instance() {
	return instance = (instance != NULL) ? instance : new TextureManager();
}

bool TextureManager::load(std::string path, std::string id, SDL_Renderer* renderer) {
	SDL_Surface* surface = IMG_Load(path.c_str());
	if (surface == NULL) {
		std::cout << IMG_GetError();
		return false;
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == NULL) { return false; }
	textureMap[id] = texture;
	SDL_FreeSurface(surface);
	return textureMap[id] != NULL;
}

bool TextureManager::load(std::string id, std::string text, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer) {
	SDL_Surface* surface = TTF_RenderUTF8_Solid(font, text.c_str(), color);
	if (surface == NULL) { return false; }
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	textureMap[id] = texture;
	SDL_FreeSurface(surface);
	return textureMap[id] != NULL;
}

void TextureManager::draw(std::string id, int x, int y, int width, int height, SDL_Renderer* renderer, SDL_RendererFlip flip) {
	if (!isExists(id)) { return; }

	SDL_Rect srcRect = { 0, 0, width, height };
	SDL_Rect dstRect = { x, y, width, height };

	SDL_RenderCopyEx(renderer, textureMap[id], &srcRect, &dstRect, 0, NULL, flip);
}

void TextureManager::drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* renderer, double angle, int alpha, SDL_RendererFlip flip) {
	if (!isExists(id)) { return; }
	SDL_Rect srcRect = { width * currentFrame, height * (currentRow - 1), width, height };
	SDL_Rect dstRect = { x, y, width, height };

	SDL_SetTextureAlphaMod(textureMap[id], alpha);
	SDL_RenderCopyEx(renderer, textureMap[id], &srcRect, &dstRect, angle, NULL, flip);

}

SDL_Texture *TextureManager::getTexture(std::string id) {
	if (!isExists(id)) { return NULL; }
	return textureMap[id];

}

void TextureManager::clearFromTextureMap(std::string id) {
	if (isExists(id)) {
		SDL_DestroyTexture(textureMap[id]);
		textureMap.erase(id);
	}
}

bool TextureManager::isExists(std::string id) {
	std::map<std::string, SDL_Texture*>::iterator it = textureMap.find(id);
	return it != textureMap.end();
}
void TextureManager::clean() {
	std::map <std::string, SDL_Texture*>::iterator it;
	for (it = textureMap.begin(); it != textureMap.end(); it++)
	{
		SDL_DestroyTexture(it->second);
	}
	textureMap.clear();
}

