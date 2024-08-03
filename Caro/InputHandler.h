#pragma once

#include <SDL.h>
#include <vector>
#include "Vector2D.h"

class InputHandler
{
public:
	enum MouseButton
	{
		LEFT,
		MIDDLE,
		RIGHT
	};

	static InputHandler* Instance();

	bool isMouseMove() { return mouseMove; }
	bool isKeyDown(SDL_Scancode key) const;
	bool getMouseButtonState(int button) const { return mouseButtonStates[button]; }

	Vector2D* getMousePositon()const { return mousePosition; }
	void reset();
	void update();
	void clean();

private:
	InputHandler();

	void onMouseButtonDown(SDL_Event &event);
	void onMouseButtonUp(SDL_Event &event);

	void onMouseMove(SDL_Event &event);

	void onKeyDown();
	void onKeyUp();

	bool mouseMove;
	static InputHandler* instance;
	Vector2D* mousePosition;
	std::vector<bool> mouseButtonStates;
	const Uint8* keyStates;
};

