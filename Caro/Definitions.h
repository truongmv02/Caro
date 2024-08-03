#pragma once

#include <SDL.h>

#define PADDING 40
#define CHESS_BOX_SIZE 32
#define ROWS 20
#define COLUMNS 25

static SDL_Color colorRed = {255, 0, 4};
static SDL_Color colorWhite = {255, 255, 255};
static SDL_Color colorBlack = {0, 0, 0};
static SDL_Color colorGreen = {1, 255, 0};
static SDL_Color colorBlue = {0, 3, 255};

enum Player
{
	NONE,
	PLAYER_O,
	PLAYER_X
};