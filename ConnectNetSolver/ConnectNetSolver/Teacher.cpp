#include "pch.h"
#include "Teacher.h"
#include "GameModerator.h"
#include <iostream>


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
	for (int i = 0; i < 7; i++)
	{
		league[i].WriteToFile(leagueName + std::to_string(i));
	}
}

void Teacher::ExhibitionMatch(std::string leagueName)
{
	//TODO --see header
}

void Teacher::Challenge(std::string leagueName)
{
	//TODO --see header
}

void Teacher::InterLeagueTest(std::string league1, std::string league2)
{
	LoadLeague(league1);
	AIConnectFourPlayer challengerLeague[7];	
	for (int i = 0; i < 7; i++)
	{
		challengerLeague[i] = AIConnectFourPlayer();
		challengerLeague[i].ReadFromFile(league2 + std::to_string(i));
	}
	GameModerator moderator = GameModerator();
	long league1score=0;
	long league2score = 0;
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
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
	GameModerator moderator = GameModerator();
	for (int i = 0; i < 7; i++)
	{
		league[i].ResetScores();
	}
	for (int player1Index = 0; player1Index < 6; player1Index++)
	{
		for (int player2Index = player1Index + 1; player2Index < 7; player2Index++)
		{
			moderator.PlayLearningGame(&league[player1Index], &league[player2Index]);
			league[player1Index].RefineNet();
			league[player2Index].RefineNet();
		}
	}
	Mutate();
}

void Teacher::LoadLeague(std::string leagueName)
{
	for (int i = 0; i < 7; i++)
	{
		league[i] = AIConnectFourPlayer();
		league[i].ReadFromFile(leagueName + std::to_string(i));
	}
}

void Teacher::Mutate()
{
	int minAddress = 0;
	int maxAddress = 0;
	for (int i = 1; i < 7; i++)
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
