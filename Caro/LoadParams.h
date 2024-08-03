#pragma once
#include <string>

class LoadParams
{
public:
	LoadParams(int x, int y, int width, int height, std::string textureID) {
		this->x = x;
		this->y = y;
		
		this->width = width;
		this->height = height;

		this->textureID = textureID;
	}

	int getX() { return x; }
	int getY() { return y; }

	int getWidth() { return width; }
	int getHeight() { return height; }

	std::string getTextureID() { return textureID; }

private:
	int x, y;
	int width, height;
	std::string textureID;
};


