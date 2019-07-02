#include "pch.h"
#include "ConnectNeuralNet.h"
#include <cstdlib>
#include "Perceptron.h"
#include "BaseLayerPerceptron.h"
#include <vector>
#include <iostream>
#include <time.h>


ConnectNeuralNet::ConnectNeuralNet()
{
	srand(time(NULL));
	for (int i = 0; i < 7; i++)
	{
		baseLayer[i] = BaseLayerPerceptron();
		hiddenLayer[i] = Perceptron();
		outputLayer[i] = Perceptron();
	}
}


ConnectNeuralNet::~ConnectNeuralNet()
{
}

std::vector<float> ConnectNeuralNet::GenerateMoves(ConnectFourGame * currentGame)
{
	std::vector<float> baseOutputs= std::vector<float>(7,0);
	game = currentGame;
	for (int i = 0; i < 7; i++)
	{
		baseLayer[i].SetInputs(i, game);
		baseOutputs[i] = (baseLayer[i].GetOutput());
	}
	std::vector<float> hiddenOutputs = std::vector<float>(7, 0);
	for (int j = 0; j < 7; j++)
	{
		hiddenOutputs[j] = (hiddenLayer[j].GetOutput(baseOutputs));
	}	std::vector<float> finalOutputs = std::vector<float>(7, 0);
	for (int k = 0; k < 7; k++)
	{
		finalOutputs[k] = (outputLayer[k].GetOutput(baseOutputs));
	}
	return finalOutputs;
}