#pragma once
#include "ConnectFourPlayer.h"
#include "AIConnectFourPlayer.h"
class GameModerator
{
public:
	GameModerator();
	~GameModerator();

	void PlayGame(AIConnectFourPlayer player1, AIConnectFourPlayer player2);
	int GetPlayer1Score();
	int GetPlayer2Score();

private:
	int player1Score;
	int player2Score;

	const int WinBaseScore = 100;
	const int LoseBaseScore = -100;
};

