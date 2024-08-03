#include "Button.h"
#include "InputHandler.h"
#include "SoundManager.h"

Button::Button(std::unique_ptr<LoadParams> const &params, void (*callBack)()) : SDLGameObject(params)
{
	this->call_back = callBack;
	released = true;
	currentFrame = MOUSE_OUT;
}

void Button::update()
{
	Vector2D mousePositon = *InputHandler::Instance()->getMousePositon();
	if (mousePositon.X >= positionFrame.X && mousePositon.X <= positionFrame.X + widthFrame &&
		mousePositon.Y >= positionFrame.Y && mousePositon.Y <= positionFrame.Y + heightFrame)
	{
		currentFrame = MOUSE_OVER;
		if (InputHandler::Instance()->getMouseButtonState(InputHandler::LEFT) && released)
		{
			SoundManager::Instance()->playSound("Click", 0);
			currentFrame = CLICKED;
			if (call_back != NULL)
			{

				call_back();
			}
			released = false;
		}
		else if (!InputHandler::Instance()->getMouseButtonState(InputHandler::LEFT))
		{
			released = true;
			currentFrame = MOUSE_OVER;
		}
	}
	else
	{
		released = false;
		currentFrame = MOUSE_OUT;
	}
}

void Button::draw()
{
	SDLGameObject::draw();
}
