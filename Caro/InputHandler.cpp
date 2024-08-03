#include "InputHandler.h"
#include "Game.h"

InputHandler* InputHandler::instance = NULL;

InputHandler::InputHandler() {
	for (int i = 0; i < 3; i++)
	{
		mouseButtonStates.push_back(false);
	}
	mousePosition = new Vector2D(0, 0);
	keyStates = NULL;
	mouseMove = false;
}

InputHandler* InputHandler::Instance() {
	return instance = (instance != NULL) ? instance : new InputHandler();
}

void InputHandler::onMouseButtonDown(SDL_Event &event) {
	switch (event.button.button)
	{
	case SDL_BUTTON_LEFT:
		mouseButtonStates[LEFT] = true;
		break;
	case SDL_BUTTON_MIDDLE:
		mouseButtonStates[MIDDLE] = true;
		break;
	case SDL_BUTTON_RIGHT:
		mouseButtonStates[RIGHT] = true;
		break;
	}
}

void InputHandler::onMouseButtonUp(SDL_Event &event) {
	switch (event.button.button)
	{
	case SDL_BUTTON_LEFT:
		mouseButtonStates[LEFT] = false;
		break;
	case SDL_BUTTON_MIDDLE:
		mouseButtonStates[MIDDLE] = false;
		break;
	case SDL_BUTTON_RIGHT:
		mouseButtonStates[RIGHT] = false;
		break;
	}
}

void InputHandler::onMouseMove(SDL_Event &event) {
	mousePosition->X = event.motion.x;
	mousePosition->Y = event.motion.y;
	mouseMove = true;
}

void InputHandler::onKeyDown() {
	keyStates = SDL_GetKeyboardState(0);
}

void InputHandler::onKeyUp() {
	keyStates = SDL_GetKeyboardState(0);
}


void InputHandler::update() {
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			Game::Instance()->quit();
			break;
		case SDL_MOUSEBUTTONDOWN:
			onMouseButtonDown(event);
			break;
		case SDL_MOUSEBUTTONUP:
			onMouseButtonUp(event);
			break;
		case SDL_MOUSEMOTION:
			onMouseMove(event);
			break;
		case SDL_KEYDOWN:
			onKeyDown();
			break;
		case SDL_KEYUP:
			onKeyUp();
			break;
		}
	}
}

bool InputHandler::isKeyDown(SDL_Scancode key) const {
	if (keyStates != NULL) {
		return keyStates[key] == 1;
	}
	return false;
}

void InputHandler::reset() {
	mouseButtonStates[LEFT] = false;
	mouseButtonStates[MIDDLE] = false;
	mouseButtonStates[RIGHT] = false;
	keyStates = NULL;
	mouseMove = false;
}

void InputHandler::clean() {
	delete keyStates;
	delete mousePosition;
}