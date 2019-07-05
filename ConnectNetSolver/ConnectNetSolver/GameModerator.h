#pragma once
#include "ConnectFourPlayer.h"
class GameModerator
{
public:
	GameModerator();
	~GameModerator();

	void PlayGame(ConnectFourPlayer player1, ConnectFourPlayer player2);
	int GetPlayer1Score();
	int GetPlayer2Score();

private:
	int player1Score;
	int player2Score;

	const int WinBaseScore = 100;
	const int LoseBaseScore = -100;
};

