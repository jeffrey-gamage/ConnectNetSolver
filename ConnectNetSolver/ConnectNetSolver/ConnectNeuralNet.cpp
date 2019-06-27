#include "pch.h"
#include "ConnectNeuralNet.h"
#include <cstdlib>


ConnectNeuralNet::ConnectNeuralNet()
{
}


ConnectNeuralNet::~ConnectNeuralNet()
{
}

std::list<float> ConnectNeuralNet::GenerateMoves(ConnectFourGame * CurrentGame)
{
	std::list<float> movesList = std::list<float>();
	for (int i = 0; i < 7; i++)
	{
		movesList.push_front(RandomFloat());
	}
	return movesList;
}

float ConnectNeuralNet::RandomFloat()
{
	return  static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}
