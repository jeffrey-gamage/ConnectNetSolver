#include "pch.h"
#include "Teacher.h"
#include "GameModerator.h"
#include <iostream>
#include <thread>

Teacher::Teacher()
{
}

Teacher::~Teacher()
{
}

void Teacher::Generations(std::string leagueName, int numGenerations)
{
	LoadLeague(leagueName);
	while (numGenerations > 0)
	{
		Generation();
		numGenerations--;
		std::cout << numGenerations<<"generations left \n";
	}
	for (int i = 0; i < LEAGUE_SIZE; i++)
	{
		league[i].WriteToFile(leagueName + std::to_string(i));
	}
}

void Teacher::ExhibitionMatch(std::string leagueName)
{
	LoadLeague(leagueName);
	GameModerator moderator = GameModerator();
	moderator.PlayExhibitionGame(&league[0], &league[1]);
}

void Teacher::Challenge(std::string leagueName)
{
	LoadLeague(leagueName);
	HumanConnectFourPlayer player = HumanConnectFourPlayer();
	GameModerator moderator = GameModerator();
	moderator.PlayVersusHuman(&player, &league[0]);
}

void Teacher::InterLeagueTest(std::string league1, std::string league2)
{
	LoadLeague(league1);
	AIConnectFourPlayer challengerLeague[8];	
	for (int i = 0; i < LEAGUE_SIZE; i++)
	{
		challengerLeague[i] = AIConnectFourPlayer();
		challengerLeague[i].ReadFromFile(league2 + std::to_string(i));
	}
	GameModerator moderator = GameModerator();
	long league1score=0;
	long league2score = 0;
	for (int i = 0; i < LEAGUE_SIZE; i++)
	{
		for (int j = 0; j < LEAGUE_SIZE; j++)
		{
			league[i].ResetScores();
			challengerLeague[j].ResetScores();
			moderator.PlayLearningGame(&league[i], &challengerLeague[j]);
			league1score += league[i].GetTotalScore();
			league2score += challengerLeague[j].GetTotalScore();
		}
	}
	std::cout << league1 << " score: " << league1score << "\n";
	std::cout << league2 << " score: " << league2score << "\n";
}

void Teacher::Generation()
{
	int pairings[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };
	for (int i = 0; i < LEAGUE_SIZE-1; i++)
	{
		league[i].ResetScores();
		std::thread table1(ScheduleLearningGame, &league[pairings[0]],&league[pairings[7]]);
		std::thread table2(ScheduleLearningGame, &league[pairings[1]], &league[pairings[6]]);
		std::thread table3(ScheduleLearningGame, &league[pairings[2]], &league[pairings[5]]);
		std::thread table4(ScheduleLearningGame, &league[pairings[3]], &league[pairings[4]]);

		//round robin scheduling shuffle
		int temp = pairings[1];
		for (int j = 2; j < LEAGUE_SIZE; j++)
			pairings[j - 1] = pairings[j];
		pairings[LEAGUE_SIZE - 1] = temp;

		table1.join();
		table2.join();
		table3.join();
		table4.join();
	}
	Mutate();
}

void Teacher::ScheduleLearningGame(AIConnectFourPlayer* player1, AIConnectFourPlayer* player2)
{
	GameModerator moderator = GameModerator();
	moderator.PlayLearningGame(player1,player2);
	player1->RefineNet();
	player2->RefineNet();
}

void Teacher::LoadLeague(std::string leagueName)
{
	for (int i = 0; i < LEAGUE_SIZE; i++)
	{
		league[i] = AIConnectFourPlayer();
		league[i].ReadFromFile(leagueName + std::to_string(i));
	}
}

void Teacher::Mutate()
{
	int minAddress = 0;
	int maxAddress = 0;
	for (int i = 1; i < LEAGUE_SIZE; i++)
	{
		if (league[i].GetTotalScore() > league[maxAddress].GetTotalScore())
			maxAddress = i;
		if (league[i].GetTotalScore() < league[minAddress].GetTotalScore())
			minAddress = i;
	}
	AIConnectFourPlayer mutatedClone = AIConnectFourPlayer();
	mutatedClone.BecomeMutatedClone(league[maxAddress]);
	league[minAddress] = mutatedClone;
}
