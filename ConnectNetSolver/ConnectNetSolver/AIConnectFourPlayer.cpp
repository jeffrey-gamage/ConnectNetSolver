#include "pch.h"
#include "AIConnectFourPlayer.h"
#include <vector>
#include <iostream>
#include "ConnectNeuralNet.h"

AIConnectFourPlayer::AIConnectFourPlayer()
{
	neuralNet = ConnectNeuralNet();
}


AIConnectFourPlayer::~AIConnectFourPlayer()
{
}

int AIConnectFourPlayer::SelectMove(ConnectFourGame * currentGame, int nthChoice)
{
	std::vector<float> preferences = neuralNet.GenerateMoves(currentGame);
	if (nthChoice >= 7) {
		std::cout << "all options rejected! Game should be over.\n";
		return 1;
	}
		//get the best reccomendation from the net
	std::vector<int> pickOrder = GetPickOrder(preferences);
	return pickOrder.at(nthChoice);
}

std::vector<int> AIConnectFourPlayer::GetPickOrder(std::vector<float> preferences)
{
	std::vector<int> pickOrder = std::vector<int>(7,0);
	for (int i = 0; i < 7; i++)
	{
		int minAddress = 0;
		int maxAddress = 0;
		for (int j = 1; j < 7; j++)
		{
			if (preferences[j] > preferences[maxAddress])
				maxAddress = j;			
			if (preferences[j] < preferences[minAddress])
				minAddress = j;
		}
		pickOrder[i] = maxAddress;
		preferences[maxAddress] = preferences[minAddress] - 0.000001f;
	}
	return pickOrder;
}
