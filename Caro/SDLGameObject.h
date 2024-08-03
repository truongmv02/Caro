#pragma once

#include <string>
#include "GameObject.h"
#include "Vector2D.h"

class SDLGameObject: public GameObject
{
public:
	SDLGameObject();
	SDLGameObject(std::unique_ptr<LoadParams> const& params);
	virtual void update();
	virtual void draw();
	virtual void clean() {}

protected:
	Vector2D positionFrame;

	int widthFrame, heightFrame;
	int currentFrame, currentRow;

	std::string textureID;
};

