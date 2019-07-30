#pragma once
#include "ConnectFourPlayer.h"
#include "AIConnectFourPlayer.h"
#include "HumanConnectFourPlayer.h"
class GameModerator
{
public:
	GameModerator();
	~GameModerator();

	void PlayLearningGame(AIConnectFourPlayer* player1, AIConnectFourPlayer* player2);
	void PlayVersusHuman(HumanConnectFourPlayer* player1, AIConnectFourPlayer* player2);
	void PlayExhibitionGame(AIConnectFourPlayer* player1, AIConnectFourPlayer* player2);
	int GetPlayer1Score();
	int GetPlayer2Score();

private:
	int player1Score;
	int player2Score;

	struct scores {
		int p1Score;
		int p2Score;
	};

	static scores GetScores(ConnectFourGame* game, int turnsTaken);
	static void PlaySelectedNets(AIConnectFourPlayer* player1, AIConnectFourPlayer* player2,AIConnectFourPlayer::WhichNet p1net, AIConnectFourPlayer::WhichNet p2net);
};

