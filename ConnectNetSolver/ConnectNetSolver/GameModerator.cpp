#include "pch.h"
#include "GameModerator.h"
#include "ConnectFourGame.h"
#include "AIConnectFourPlayer.h"
#include <iostream>
#include <thread>


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

GameModerator::scores GameModerator::GetScores(ConnectFourGame* game, int turnsTaken)
{
	scores scores;
	switch (game->GetWinner())
	{
		case ConnectFourGame::WhichPlayer::player1: {
			scores.p1Score = 50 - turnsTaken;
			scores.p2Score = turnsTaken - 50;
			break;
		}
		case ConnectFourGame::WhichPlayer::player2: {
			scores.p1Score = turnsTaken - 50;
			scores.p2Score = 50 - turnsTaken;
			break;
		}
		case ConnectFourGame::WhichPlayer::neither: {
			scores.p1Score = -1;
			scores.p2Score = -1;
			break;
		}
	}
	return scores;
}

void GameModerator::PlaySelectedNets(AIConnectFourPlayer* player1, AIConnectFourPlayer* player2,AIConnectFourPlayer::WhichNet p1net, AIConnectFourPlayer::WhichNet p2net)
{
	ConnectFourGame game = ConnectFourGame();
	int turnsTaken = 0;
	while (!game.isGameOver)
	{
		player1->MakeMove(&game, 0,p1net);
		turnsTaken++;
		if (!game.isGameOver)
		{
			player2->MakeMove(&game, 0,p2net);
			turnsTaken++;
		}
	}
	scores scores = GetScores(&game, turnsTaken);
	switch (p1net) {
	case AIConnectFourPlayer::WhichNet::prime: {player1->primeScore += scores.p1Score; break; }
	case AIConnectFourPlayer::WhichNet::plus: {player1->plusScore += scores.p1Score; break; }
	case AIConnectFourPlayer::WhichNet::minus: {player1->minusScore += scores.p1Score; break; }
	}
	switch (p2net) {
	case AIConnectFourPlayer::WhichNet::prime: {player2->primeScore += scores.p2Score; break; }
	case AIConnectFourPlayer::WhichNet::plus: {player2->plusScore += scores.p2Score; break; }
	case AIConnectFourPlayer::WhichNet::minus: {player2->minusScore += scores.p2Score; break; }
	}
}

void GameModerator::PlayLearningGame(AIConnectFourPlayer* player1, AIConnectFourPlayer* player2)
{
	if (rand() % 2 == 0)//randomize starting player
	{
		AIConnectFourPlayer* temp = player1;
		player1 = player2;
		player2 = temp;
	}
	player1->isPlayerOne = true;
	player2->isPlayerOne = false;

	std::thread game1(PlaySelectedNets, player1, player2, AIConnectFourPlayer::WhichNet::prime, AIConnectFourPlayer::WhichNet::prime);
	std::thread game2(PlaySelectedNets, player1, player2, AIConnectFourPlayer::WhichNet::plus, AIConnectFourPlayer::WhichNet::plus);
	std::thread game3(PlaySelectedNets, player1, player2, AIConnectFourPlayer::WhichNet::minus, AIConnectFourPlayer::WhichNet::minus);
	
	game1.join();
	game2.join();
	game3.join();
	
	std::thread game4(PlaySelectedNets, player1, player2, AIConnectFourPlayer::WhichNet::prime, AIConnectFourPlayer::WhichNet::plus);
	std::thread game5(PlaySelectedNets, player1, player2, AIConnectFourPlayer::WhichNet::plus, AIConnectFourPlayer::WhichNet::minus);
	std::thread game6(PlaySelectedNets, player1, player2, AIConnectFourPlayer::WhichNet::minus, AIConnectFourPlayer::WhichNet::prime);
	
	game4.join();
	game5.join();
	game6.join();
	
	std::thread game7(PlaySelectedNets, player1, player2, AIConnectFourPlayer::WhichNet::prime, AIConnectFourPlayer::WhichNet::minus);
	std::thread game8(PlaySelectedNets, player1, player2, AIConnectFourPlayer::WhichNet::plus, AIConnectFourPlayer::WhichNet::prime);
	std::thread game9(PlaySelectedNets, player1, player2, AIConnectFourPlayer::WhichNet::minus, AIConnectFourPlayer::WhichNet::plus);

	game7.join();
	game8.join();
	game9.join();
}

void GameModerator::PlayVersusHuman(HumanConnectFourPlayer * player1, AIConnectFourPlayer * player2)
{
	ConnectFourGame game = ConnectFourGame();
	player1->isPlayerOne = true;
	player2->isPlayerOne = false;
	if (rand() % 2 == 0)
	{
		player1->isPlayerOne = false;
		player2->isPlayerOne = true;
		player2->MakeMove(&game, 0, AIConnectFourPlayer::WhichNet::prime);
		game.DisplayBoard();
	}
	while (!game.isGameOver)
	{
		player1->MakeMove(&game, 0);
		game.DisplayBoard();
		if (!game.isGameOver)
		{
			player2->MakeMove(&game, 0, AIConnectFourPlayer::WhichNet::prime);
			game.DisplayBoard();
		}
	}
}

void GameModerator::PlayExhibitionGame(AIConnectFourPlayer * player1, AIConnectFourPlayer * player2)
{
	ConnectFourGame game = ConnectFourGame();
	player1->isPlayerOne = true;
	player2->isPlayerOne = false;
	if (rand() % 2 == 0)
	{
		player1->isPlayerOne = false;
		player2->isPlayerOne = true;
		player2->MakeMove(&game, 0, AIConnectFourPlayer::WhichNet::prime);
		game.DisplayBoard();
	}
	while (!game.isGameOver)
	{
		player1->MakeMove(&game, 0, AIConnectFourPlayer::WhichNet::prime);
		game.DisplayBoard();
		system("PAUSE");
		if (!game.isGameOver)
		{
			player2->MakeMove(&game, 0, AIConnectFourPlayer::WhichNet::prime);
			game.DisplayBoard();
			system("PAUSE");
		}
	}
}
