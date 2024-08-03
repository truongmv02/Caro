#include "PlayState.h"
#include "TextureManager.h"
#include "Game.h"
#include "InputHandler.h"

const std::string PlayState::stateID = "PLAY";
int mode;
int curRow, curCol;
int endState;
int direction;

CaroChess* caroChess ;
Button* playAgainButton ;
Button* exitButton;

SDLGameObject* tTurn;

SDLGameObject* tTurnPlayerO;
SDLGameObject* tTurnPlayerX;

SDLGameObject* tPlayerOWin;
SDLGameObject* tPlayerXWin;

SDLGameObject* tDraw;


void PlayState::handleEvents() {
	if (InputHandler::Instance()->getMouseButtonState(InputHandler::LEFT) || InputHandler::Instance()->isMouseMove())
	{
		Vector2D mousePos = *InputHandler::Instance()->getMousePositon();
		if (mousePos.X > PADDING && mousePos.X < CHESS_BOX_SIZE * COLUMNS + PADDING && mousePos.Y > PADDING && mousePos.Y < CHESS_BOX_SIZE * ROWS + PADDING)
		{
			curCol = int((mousePos.X - PADDING) / CHESS_BOX_SIZE);
			curRow = int((mousePos.Y - PADDING) / CHESS_BOX_SIZE);
			if (InputHandler::Instance()->getMouseButtonState(InputHandler::LEFT))
			{
				caroChess->addNewChessBox(curRow, curCol);
			}
		}
	}
	else if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN) || InputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE))
	{
		caroChess->addNewChessBox(curRow, curCol);
	}
	else if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_A) || InputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT))
	{
		curCol--;
	}
	else if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_D) || InputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT))
	{
		curCol++;
	}
	else if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_W) || InputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP))
	{
		curRow--;
	}
	else if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_S) || InputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN))
	{
		curRow++;
	}
	curRow = (curRow < 0) ? ROWS - 1 : (curRow >= ROWS) ? 0 : curRow;
	curCol = (curCol < 0) ? COLUMNS - 1 : (curCol >= COLUMNS) ? 0 : curCol;
}


void PlayState::update() {
	if (!loadingComplete || exiting) { return; }

	playAgainButton->update();
	exitButton->update();
	if (endState != EndState::NONE) { return; }
	if (gameMode == PLAYER_VS_PLAYER) {
		handleEvents();
	}
	else {
		if (caroChess->isPlayO()) {
			handleEvents();
		}
		else {
			caroChess->findPosition(curRow, curCol);
			caroChess->addNewChessBox(curRow, curCol);
		}
	}
	direction = caroChess->checkEndGame(curRow, curCol);
	if (direction == 0) { endState = DRAW; }
	else if (direction > 0) {
		endState = (caroChess->isPlayO()) ? PLAYER_X_WIN : PLAYER_O_WIN;
	}
}

void PlayState::render() {
	if (!loadingComplete || exiting) { return; }
	TextureManager* instance = TextureManager::Instance();

	instance->draw("backgroundGame", 0, 0, 1140, 720, Game::Instance()->getRenderer());

	playAgainButton->draw();
	exitButton->draw();
	switch (endState)
	{
	case EndState::NONE:
		tTurn->draw();
		drawChessBoxChoose(curRow, curCol);
		if (caroChess->isPlayO()) {
			tTurnPlayerO->draw();
		}
		else {
			tTurnPlayerX->draw();
		}
		break;
	case EndState::PLAYER_O_WIN:
		drawChessBoxWin();
		tPlayerOWin->draw();
		break;
	case EndState::PLAYER_X_WIN:
		drawChessBoxWin();
		tPlayerXWin->draw();
		break;
	case EndState::DRAW:
		tDraw->draw();
		break;
	}
	drawBoard(caroChess->board);
}

void PlayState::drawBoard(char board[ROWS][COLUMNS]) {
	for (int row = 0; row < ROWS; row++)
	{
		for (int col = 0; col < COLUMNS; col++)
		{
			if (board[row][col] == 'O') {
				int x = col * CHESS_BOX_SIZE + PADDING;
				int y = row * CHESS_BOX_SIZE + PADDING;
				TextureManager::Instance()->draw("CaroO", x, y, 32, 32, Game::Instance()->getRenderer());
			}
			else if (board[row][col] == 'X') {
				int x = col * CHESS_BOX_SIZE + PADDING;
				int y = row * CHESS_BOX_SIZE + PADDING;
				TextureManager::Instance()->draw("CaroX", x, y, 32, 32, Game::Instance()->getRenderer());
			}
		}
	}
}


void PlayState::drawChessBoxChoose(int row, int col)
{
	SDL_Rect rect = { col * (CHESS_BOX_SIZE)+PADDING + 1, row * (CHESS_BOX_SIZE)+PADDING + 1, CHESS_BOX_SIZE - 1, CHESS_BOX_SIZE - 1 };
	SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 50, 255, 126, 255);
	SDL_RenderFillRect(Game::Instance()->getRenderer(), &rect);
	SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 0, 0, 0, 255);
}

void PlayState::drawChessBoxWin()
{
	int col = curCol;
	int row = curRow;
	char player = caroChess->board[row][col];
	switch (direction)
	{
	case 1:
		for (; col > 0 && caroChess->board[row][col] == player; col--)
		{
			drawChessBoxChoose(row, col);
		}
		for (col = curCol + 1; col < COLUMNS && caroChess->board[row][col] == player; col++)
		{
			drawChessBoxChoose(row, col);
		}
		break;

	case 2:
		for (; row > 0 && caroChess->board[row][col] == player; row--)
		{
			drawChessBoxChoose(row, col);
		}
		for (row = curRow + 1; row < ROWS && caroChess->board[row][col] == player; row++)
		{
			drawChessBoxChoose(row, col);
		}
		break;

	case 3:
		for (; col > 0 && row > 0 && caroChess->board[row][col] == player; row--, col--)
		{
			drawChessBoxChoose(row, col);
		}
		for (row = curRow + 1, col = curCol + 1; col < COLUMNS && row < ROWS && caroChess->board[row][col] == player; row++, col++)
		{
			drawChessBoxChoose(row, col);
		}
		break;
	case 4:
		for (; col < COLUMNS && row > 0 && caroChess->board[row][col] == player; row--, col++)
		{
			drawChessBoxChoose(row, col);
		}
		for (row = curRow + 1, col = curCol - 1; col > 0 && row < ROWS && caroChess->board[row][col] == player; row++, col--)
		{
			drawChessBoxChoose(row, col);
		}
		break;
	}
}

bool PlayState::onEnter() {
	TextureManager* instance = TextureManager::Instance();
	instance->load("assets/image/BackgroundGame.png", "backgroundGame", Game::Instance()->getRenderer());
	instance->load("assets/image/CaroO.png", "CaroO", Game::Instance()->getRenderer());
	instance->load("assets/image/CaroX.png", "CaroX", Game::Instance()->getRenderer());

	instance->load("assets/image/Exit2.png", "ExitButton2", Game::Instance()->getRenderer());
	instance->load("assets/image/PlayAgain.png", "PlayAgainButton", Game::Instance()->getRenderer());
	int x = (264 - 130) / 2 + 860;

	TTF_Font* font = TTF_OpenFont("assets/font/Roboto-Bold.ttf", 30);
	if (font == NULL) {
		SDL_Log("%s", TTF_GetError());
	}

	instance->load("Turn", "Turn", font, colorBlack, Game::Instance()->getRenderer());

	if (gameMode == PLAYER_VS_PLAYER) {

		instance->load("TurnPlayerO", "PLAYER O", font, colorRed, Game::Instance()->getRenderer());
		instance->load("TurnPlayerX", "PLAYER X", font, colorBlue, Game::Instance()->getRenderer());
		instance->load("OWin", "PLAYER O WIN", font, colorRed, Game::Instance()->getRenderer());
		instance->load("XWin", "PLAYER X WIN", font, colorBlue, Game::Instance()->getRenderer());
	}
	else {

		instance->load("TurnPlayerO", "YOU", font, colorRed, Game::Instance()->getRenderer());
		instance->load("TurnPlayerX", "COMPUTER", font, colorBlue, Game::Instance()->getRenderer());
		instance->load("OWin", "YOU WIN", font, colorRed, Game::Instance()->getRenderer());
		instance->load("XWin", "COMPUTER WIN", font, colorBlue, Game::Instance()->getRenderer());
	}

	instance->load("Draw", "DRAW", font, colorBlack, Game::Instance()->getRenderer());
	TTF_CloseFont(font);

	int w, h;

	SDL_QueryTexture(instance->getTexture("Turn"), NULL, NULL, &w, &h);
	tTurn = new SDLGameObject(std::unique_ptr<LoadParams>(new LoadParams((264 - w) / 2 + 860, 380, w, h, "Turn")));

	SDL_QueryTexture(TextureManager::Instance()->getTexture("TurnPlayerO"), NULL, NULL, &w, &h);
	tTurnPlayerO = new SDLGameObject(std::unique_ptr<LoadParams>(new LoadParams((264 - w) / 2 + 860, 420, w, h, "TurnPlayerO")));

	SDL_QueryTexture(TextureManager::Instance()->getTexture("TurnPlayerX"), NULL, NULL, &w, &h);
	tTurnPlayerX = new SDLGameObject(std::unique_ptr<LoadParams>(new LoadParams((264 - w) / 2 + 860, 420, w, h, "TurnPlayerX")));

	SDL_QueryTexture(TextureManager::Instance()->getTexture("OWin"), NULL, NULL, &w, &h);
	tPlayerOWin = new SDLGameObject(std::unique_ptr<LoadParams>(new LoadParams((264 - w) / 2 + 860, 400, w, h, "OWin")));

	SDL_QueryTexture(TextureManager::Instance()->getTexture("XWin"), NULL, NULL, &w, &h);
	tPlayerXWin = new SDLGameObject(std::unique_ptr<LoadParams>(new LoadParams((264 - w) / 2 + 860, 400, w, h, "XWin")));

	SDL_QueryTexture(TextureManager::Instance()->getTexture("Draw"), NULL, NULL, &w, &h);
	tDraw = new SDLGameObject(std::unique_ptr<LoadParams>(new LoadParams((264 - w) / 2 + 860, 400, w, h, "Draw")));

	x = (264 - 130) / 2 + 860;
	playAgainButton = new Button(std::unique_ptr<LoadParams>(new LoadParams(x, 525, 130, 55, "PlayAgainButton")), playAgain);
	exitButton = new Button(std::unique_ptr<LoadParams>(new LoadParams(x, 600, 130, 55, "ExitButton2")), backToMenu);

	caroChess = new CaroChess();
	mode = gameMode;
	endState = EndState::NONE;
	curRow = ROWS / 2;
	curCol = COLUMNS / 2;
	loadingComplete = true;

	return true;
}

bool PlayState::onExit() {
	exiting = true;
	delete caroChess;

	delete tTurn;
	delete tTurnPlayerO;
	delete tTurnPlayerX;
	delete tPlayerOWin;
	delete tPlayerXWin;
	delete tDraw;
	delete playAgainButton;
	delete exitButton;

	TextureManager::Instance()->clearFromTextureMap("backgroundGame");
	TextureManager::Instance()->clearFromTextureMap("CaroO");
	TextureManager::Instance()->clearFromTextureMap("CaroX");

	TextureManager::Instance()->clearFromTextureMap("PlayAgainButton");
	TextureManager::Instance()->clearFromTextureMap("ExitButton2");

	TextureManager::Instance()->clearFromTextureMap("Turn");

	TextureManager::Instance()->clearFromTextureMap("TurnPlayerO");
	TextureManager::Instance()->clearFromTextureMap("TurnPlayerX");
	TextureManager::Instance()->clearFromTextureMap("OWin");
	TextureManager::Instance()->clearFromTextureMap("XWin");

	TextureManager::Instance()->clearFromTextureMap("Draw");

	InputHandler::Instance()->reset();
	return true;
}

void PlayState::playAgain() {
	Game::Instance()->getGameStateMachine()->popState();
	Game::Instance()->getGameStateMachine()->changeState(new PlayState(mode));
}

void PlayState::backToMenu() {
	Game::Instance()->getGameStateMachine()->changeState(new MenuState());
}

