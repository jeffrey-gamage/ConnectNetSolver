#include "pch.h"
#include "GameModerator.h"
#include "ConnectFourGame.h"
#include "AIConnectFourPlayer.h"


GameModerator::GameModerator()
{
}


GameModerator::~GameModerator()
{
}

int GameModerator::GetPlayer1Score()
{
	return player1Score;

}int GameModerator::GetPlayer2Score()
{
	return player2Score;
}

void GameModerator::PlayGame(AIConnectFourPlayer player1, AIConnectFourPlayer player2)
{
	ConnectFourGame game = ConnectFourGame();
	player1.isPlayerOne = true;
	player2.isPlayerOne = false;
	int turnsTaken = 0;
	while (!game.isGameOver)
	{
		player1.MakeMove(&game, 0);
		turnsTaken++;
		if (game.isGameOver)
		{
			player2.MakeMove(&game, 0);
			turnsTaken++;
		}
	}
	switch (game.GetWinner())
	{
	case ConnectFourGame::WhichPlayer::player1: {
		player1Score = 50 - turnsTaken;
		player2Score = turnsTaken - 50;
		break;
	}
	case ConnectFourGame::WhichPlayer::player2: {
		player1Score = turnsTaken - 50;
		player2Score = 50 - turnsTaken;
		break;
	}
	case ConnectFourGame::WhichPlayer::neither: {
		player1Score = -1;
		player2Score = -1;
		break;
	}
	}
}
