#include "CaroChess.h"
#include "SoundManager.h"

CaroChess::CaroChess()
{
	turn = Player::PLAYER_O;
	for (int row = 0; row < ROWS; row++)
	{
		for (int col = 0; col < COLUMNS; col++)
		{
			board[row][col] = ' ';
		}
	}
}

CaroChess::~CaroChess()
{
}

bool CaroChess::addNewChessBox(int row, int col)
{
	if (board[row][col] != ' ') { return false; }

	switch (turn)
	{
	case Player::PLAYER_O:
		board[row][col] = 'O';
		turn = Player::PLAYER_X;
		break;

	case Player::PLAYER_X:
		board[row][col] = 'X';
		turn = Player::PLAYER_O;
		break;
	}
	SoundManager::Instance()->playSound("PlayChess", 0);
	return true;
}

int CaroChess::checkEndGame(int row, int col)
{
	int count = 0;
	char player = board[row][col];
	if (player == ' ') { return -1; }
	// hoa
	for (int _row = 0; _row < ROWS; _row++)
	{
		for (int _col = 0; _col < COLUMNS; _col++)
		{
			if (board[_row][_col] == ' ')
			{
				count++;
				break;
			}
		}
		if (count != 0)
		{
			break;
		}
	}
	if (count == 0)
	{
		return 0;
	}
	// hang ngang
	count = 0;
	for (int _col = col + 1; _col < COLUMNS && board[row][_col] == player; _col++)
	{
		count++;
	}

	for (int _col = col - 1; _col >= 0 && board[row][_col] == player; _col--)
	{
		count++;
	}

	if (count >= 4)
	{
		return 1;
	}

	// Hang doc
	count = 0;
	for (int _row = row + 1; _row < ROWS && board[_row][col] == player; _row++)
	{
		count++;
	}
	for (int _row = row - 1; _row >= 0 && board[_row][col] == player; _row--)
	{
		count++;
	}
	if (count >= 4)
	{
		return 2;
	}

	//Hang cheo\
	
	count = 0;
	for (int _row = row + 1, _col = col + 1; _row < ROWS && _col < COLUMNS && board[_row][_col] == player; _row++, _col++)
	{
		count++;
	}

	for (int _row = row - 1, _col = col - 1; _row >= 0 && _col >= 0 && board[_row][_col] == player; _row--, _col--)
	{
		count++;
	}
	if (count >= 4)
	{
		return 3;
	}

	// kiem tra duong cheo /
	count = 0;

	for (int _row = row + 1, _col = col - 1; _row < ROWS && _col >= 0 && board[_row][_col] == player; _row++, _col--)
	{
		count++;
	}
	for (int _row = row - 1, _col = col + 1; _row >= 0 && _col < COLUMNS && board[_row][_col] == player; _row--, _col++)
	{
		count++;
	}

	if (count >= 4)
	{
		return 4;
	}

	return -1;
}

int attackScores[] = { 0, 9, 54, 162, 1458, 13112, 118008 };
int defenseScores[] = { 0, 3, 27, 99, 729, 6561, 59049 };

void CaroChess::findPosition(int& row, int& col)
{
	int scoreMax = 0;
	for (int _row = 0; _row < ROWS; _row++)
	{
		for (int _col = 0; _col < COLUMNS; _col++)
		{
			if (board[_row][_col] == ' ')
			{
				int attackScore = getAttackScore1(_row, _col) + getAttackScore2(_row, _col) + getAttackScore3(_row, _col) + getAttackScore4(_row, _col);
				int defenseScore = getDefenseScore1(_row, _col) + getDefenseScore2(_row, _col) + getDefenseScore3(_row, _col) + getDefenseScore4(_row, _col);
				int result = (attackScore > defenseScore) ? attackScore : defenseScore;
				if (result >= scoreMax)
				{
					scoreMax = result;
					row = _row;
					col = _col;
				}
			}
		}
	}
}

int CaroChess::getAttackScore1(int row, int col)
{
	int score = 0;
	int countO = 0;
	int countX = 0;
	for (int i = 1; i < 5 && col + i < COLUMNS; i++)
	{
		if (board[row][col + i] == 'X')
		{
			countX++;
		}
		else if (board[row][col + i] == 'O')
		{
			score -= 9;
			countO++;
			break;
		}
		else
		{
			break;
		}
	}

	for (int i = 1; i < 5 && col - i >= 0; i++)
	{
		if (board[row][col - i] == 'X')
		{
			countX++;
		}
		else if (board[row][col - i] == 'O')
		{
			countO++;
			score -= 9;
			break;
		}
		else
		{
			break;
		}
	}
	if (countO == 2 && countX < 4)
	{
		return 0;
	}
	score += attackScores[countX];
	score -= defenseScores[countO];
	return score;
}

int CaroChess::getAttackScore2(int row, int col)
{
	int score = 0;
	int countO = 0;
	int countX = 0;
	for (int i = 1; i < 5 && row + i < ROWS; i++)
	{
		if (board[row + i][col] == 'X')
		{
			countX++;
		}
		else if (board[row + i][col] == 'O')
		{
			countO++;
			score -= 9;
			break;
		}
		else
		{
			break;
		}
	}

	for (int i = 1; i < 5 && row - i >= 0; i++)
	{
		if (board[row - i][col] == 'X')
		{
			countX++;
		}
		else if (board[row - i][col] == 'O')
		{
			countO++;
			score -= 9;
			break;
		}
		else
		{
			break;
		}
	}
	if (countO == 2 && countX < 4)
	{
		return 0;
	}
	score += attackScores[countX];
	score -= defenseScores[countO];
	return score;
}

int CaroChess::getAttackScore3(int row, int col)
{
	int score = 0;
	int countO = 0;
	int countX = 0;
	for (int i = 1; i < 5 && col + i < COLUMNS && row + i < ROWS; i++)
	{
		if (board[row + i][col + i] == 'X')
		{
			countX++;
		}
		else if (board[row + i][col + i] == 'O')
		{
			countO++;
			score -= 9;
			break;
		}
		else
		{
			break;
		}
	}

	for (int i = 1; i < 5 && row - i >= 0 && col - i >= 0; i++)
	{
		if (board[row - i][col - i] == 'X')
		{
			countX++;
		}
		else if (board[row - i][col - i] == 'O')
		{
			countO++;
			score -= 9;
			break;
		}
		else
		{
			break;
		}
	}
	if (countO == 2 && countX < 4)
	{
		return 0;
	}
	score += attackScores[countX];
	score -= defenseScores[countO];
	return score;
}

int CaroChess::getAttackScore4(int row, int col)
{
	int score = 0;
	int countO = 0;
	int countX = 0;
	for (int i = 1; i < 5 && (row - i >= 0) && (col + i < COLUMNS); i++)
	{
		if (board[row - i][col + i] == 'X')
		{
			countX++;
		}
		else if (board[row - i][col + i] == 'O')
		{
			score -= 9;
			countO++;
			break;
		}
		else
		{
			break;
		}
	}

	for (int i = 1; i < 5 && row + i < ROWS && col - i >= 0; i++)
	{
		if (board[row + i][col - i] == 'X')
		{
			countX++;
		}
		else if (board[row + i][col - i] == 'O')
		{
			countO++;
			score -= 9;
			break;
		}
		else
		{
			break;
		}
	}
	if (countO == 2 && countX < 4)
	{
		return 0;
	}
	score += attackScores[countX];
	score -= defenseScores[countO];
	return score;
}

int CaroChess::getDefenseScore1(int row, int col)
{
	int score = 0;
	int countO = 0;
	int countX = 0;
	for (int i = 1; i < 5 && col + i < COLUMNS; i++)
	{
		if (board[row][col + i] == 'X')
		{
			countX++;
			break;
		}
		else if (board[row][col + i] == 'O')
		{
			countO++;
		}
		else
		{
			break;
		}
	}

	for (int i = 1; i < 5 && col - i >= 0; i++)
	{
		if (board[row][col - i] == 'X')
		{
			countX++;
			break;
		}
		else if (board[row][col - i] == 'O')
		{
			countO++;
		}
		else
		{
			break;
		}
	}
	if (countX == 2 && countO < 4)
	{
		return 0;
	}
	score -= attackScores[countX];
	score += defenseScores[countO];
	return score;
}

int CaroChess::getDefenseScore2(int row, int col)
{
	int score = 0;
	int countO = 0;
	int countX = 0;
	for (int i = 1; i < 5 && row + i < ROWS; i++)
	{
		if (board[row + i][col] == 'X')
		{
			countX++;
			break;
		}
		else if (board[row + i][col] == 'O')
		{
			countO++;
		}
		else
		{
			break;
		}
	}

	for (int i = 1; i < 5 && row - i >= 0; i++)
	{
		if (board[row - i][col] == 'X')
		{
			countX++;
			break;
		}
		else if (board[row - i][col] == 'O')
		{
			countO++;
		}
		else
		{
			break;
		}
	}
	if (countX == 2 && countO < 4)
	{
		return 0;
	}
	score += defenseScores[countO];
	score -= attackScores[countX];
	return score;
}

int CaroChess::getDefenseScore3(int row, int col)
{
	int score = 0;
	int countO = 0;
	int countX = 0;
	for (int i = 1; i < 5 && col + i < COLUMNS && row + i < ROWS; i++)
	{
		if (board[row + i][col + i] == 'X')
		{
			countX++;
			break;
		}
		else if (board[row + i][col + i] == 'O')
		{
			countO++;
		}
		else
		{
			break;
		}
	}

	for (int i = 1; i < 5 && row - i >= 0 && col - i >= 0; i++)
	{
		if (board[row - i][col - i] == 'X')
		{
			countX++;
			break;
		}
		else if (board[row - i][col - i] == 'O')
		{
			countO++;
		}
		else
		{
			break;
		}
	}
	if (countX == 2 && countO < 4)
	{
		return 0;
	}
	score -= attackScores[countX];
	score += defenseScores[countO];
	return score;
}

int CaroChess::getDefenseScore4(int row, int col)
{
	int score = 0;
	int countO = 0;
	int countX = 0;
	for (int i = 1; i < 5 && row - i >= 0 && col + i < COLUMNS; i++)
	{
		if (board[row - i][col + i] == 'X')
		{
			countX++;
			break;
		}
		else if (board[row - i][col + i] == 'O')
		{
			countO++;
		}
		else
		{
			break;

		}
	}

	for (int i = 1; i < 5 && row + i < ROWS && col - i >= 0; i++)
	{
		if (board[row + i][col - i] == 'X')
		{
			countX++;
			break;
		}
		else if (board[row + i][col - i] == 'O')
		{
			countO++;
		}
		else
		{
			break;
		}
	}
	if (countX == 2 && countO < 4)
	{
		return 0;
	}
	score -= attackScores[countX];
	score += defenseScores[countO];
	return score;
}
