#pragma once
#include "ConnectFourPlayer.h"
#include "AIConnectFourPlayer.h"
class GameModerator
{
public:
	GameModerator();
	~GameModerator();

	void PlayLearningGame(AIConnectFourPlayer* player1, AIConnectFourPlayer* player2);
	int GetPlayer1Score();
	int GetPlayer2Score();

private:
	int player1Score;
	int player2Score;

	struct scores {
		int p1Score;
		int p2Score;
	};

	scores GetScores(ConnectFourGame* game, int turnsTaken);
	void PlaySelectedNets(AIConnectFourPlayer* player1, AIConnectFourPlayer* player2,AIConnectFourPlayer::WhichNet p1net, AIConnectFourPlayer::WhichNet p2net);
};

