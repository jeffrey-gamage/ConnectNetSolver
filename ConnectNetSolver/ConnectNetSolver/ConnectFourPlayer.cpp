#include "pch.h"
#include "ConnectFourPlayer.h"
#include "ConnectFourGame.h"
#include <iostream>


ConnectFourPlayer::ConnectFourPlayer()
{
}

ConnectFourPlayer::~ConnectFourPlayer()
{
}

void ConnectFourPlayer::MakeMove(ConnectFourGame * currentGame, int numTries)
{
	int nextMove;
	nextMove = SelectMove(currentGame, numTries);
	{
		if (!currentGame->IsLegalMove(nextMove))
		{
			if (!currentGame->isGameOver)
				MakeMove(currentGame, numTries + 1);
			else std::cout << "Game is over!\n";
		}
		else
		{
			currentGame->PlayPiece(nextMove, isPlayerOne);
		}
	}
}

int ConnectFourPlayer::SelectMove(ConnectFourGame * currentGame, int nthChoice)
{
	//should always be overriden
	return 0;
}
