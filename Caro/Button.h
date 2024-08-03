#pragma once

#include "SDLGameObject.h"

class Button : public SDLGameObject
{
public:
	Button(std::unique_ptr<LoadParams> const& params, void (*callBack)());
	~Button(){}
	void update();
	void draw();
	void clean() { SDLGameObject::clean(); }

private:
	enum  ButtonState
	{
		MOUSE_OUT,
		MOUSE_OVER,
		CLICKED
	};

	bool released;
	void(*call_back)();
};

