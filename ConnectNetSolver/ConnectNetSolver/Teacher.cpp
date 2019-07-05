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
	for (int i = 0; i < 7; i++)
	{
		league[i] = AIConnectFourPlayer();
		league[i].ReadFromFile(leagueName + std::to_string(i));
	}
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

void Teacher::Generation()
{
	GameModerator moderator = GameModerator();
	for (int i = 0; i < 7; i++)
	{
		scores[i] = 0;
	}
	for (int player1Index = 0; player1Index < 6; player1Index++)
	{
		for (int player2Index = player1Index + 1; player2Index < 7; player2Index++)
		{
			moderator.PlayGame(league[player1Index], league[player2Index]);
			scores[player1Index] += moderator.GetPlayer1Score();
			scores[player2Index] += moderator.GetPlayer2Score();
		}
	}
	Mutate();
}

void Teacher::Mutate()
{
	int minAddress = 0;
	int maxAddress = 0;
	for (int i = 1; i < 7; i++)
	{
		if (scores[i] > scores[maxAddress])
			maxAddress = i;
		if (scores[i] < scores[minAddress])
			minAddress = i;
	}
	AIConnectFourPlayer mutatedClone = AIConnectFourPlayer();
	mutatedClone.BecomeMutatedClone(league[maxAddress]);
	league[minAddress] = mutatedClone;
}
