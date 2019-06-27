#include "pch.h"
#include "AIConnectFourPlayer.h"
#include <list>
#include <iostream>

AIConnectFourPlayer::AIConnectFourPlayer()
{
}


AIConnectFourPlayer::~AIConnectFourPlayer()
{
}

int AIConnectFourPlayer::SelectMove(ConnectFourGame * currentGame, int nthChoice)
{
	std::list<float> preferences = neuralNet.GenerateMoves(currentGame);
	if (nthChoice >= 7) {
		std::cout << "all options rejected! Game should be over.\n";
		return 1;
	}
		//get the best reccomendation from the net
	std::list<int> pickOrder = GetPickOrder(preferences);
	while (nthChoice > 0)
	{
		nthChoice--;
		pickOrder.pop_front();
	}
	return pickOrder.front();
}

std::list<int> AIConnectFourPlayer::GetPickOrder(std::list<float> preferences)
{
	float preferenceArray[7];
	for (int i = 0; i < 7; i++)
	{
		preferenceArray[i] = preferences.front();
		std::cout << preferences.front() << " ";
		preferences.pop_front();
	}
	std::cout << "\n";
	int pickOrderArray[7];
	for (int i = 0; i < 7; i++)
	{
		int minAddress = 0;
		int maxAddress = 0;
		for (int j = 1; j < 7; j++)
		{
			if (preferenceArray[j] > preferenceArray[maxAddress])
				maxAddress = j;			
			if (preferenceArray[j] < preferenceArray[minAddress])
				minAddress = j;
		}
		pickOrderArray[i] = maxAddress;
		preferenceArray[maxAddress] = preferenceArray[minAddress] - 0.000001f;
	}
	std::list<int> pickOrder = std::list<int>();
	for (int i = 0; i < 7; i++)
	{
		pickOrder.push_back(pickOrderArray[i]);
	}
	return pickOrder;
}
