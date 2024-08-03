#pragma once
#include "LoadParams.h"
#include <memory>
class GameObject
{
public:
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void clean() = 0;

protected:
	GameObject(std::unique_ptr<LoadParams> const &params) {}
	GameObject() {}
};
