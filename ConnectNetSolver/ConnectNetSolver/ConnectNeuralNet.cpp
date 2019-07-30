#include "pch.h"
#include "ConnectNeuralNet.h"
#include <cstdlib>
#include "Perceptron.h"
#include "BaseLayerPerceptron.h"
#include <vector>
#include <iostream>


ConnectNeuralNet::ConnectNeuralNet()
{
	for (int i = 0; i < 14; i++)
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
	std::vector<float> baseOutputs= std::vector<float>(14,0);
	game = currentGame;
	for (int i = 0; i < 14; i++)
	{
		baseLayer[i].SetInputs(GetBaseLayerInputs(i), game);
		baseOutputs[i] = (baseLayer[i].GetOutput());
	}
	std::vector<float> hiddenOutputs = std::vector<float>(14, 0);
	for (int j = 0; j < 14; j++)
	{
		hiddenOutputs[j] = (hiddenLayer[j].GetOutput(baseOutputs));
	}	std::vector<float> finalOutputs = std::vector<float>(14, 0);
	for (int k = 0; k < 7; k++)
	{
		finalOutputs[k] = outputLayer[k].GetOutput(hiddenOutputs)+outputLayer[k+7].GetOutput(hiddenOutputs);
	}
	return finalOutputs;
}

void ConnectNeuralNet::BecomeClone(ConnectNeuralNet netToClone)
{
	for (int perceptronIndex = 0; perceptronIndex < 14; perceptronIndex++)
	{
		for (int weightIndex = 0; weightIndex < 14; weightIndex++)
		{
			baseLayer[perceptronIndex].SetWeight(netToClone.baseLayer[perceptronIndex].GetWeight(weightIndex),weightIndex);
			hiddenLayer[perceptronIndex].SetWeight(netToClone.hiddenLayer[perceptronIndex].GetWeight(weightIndex), weightIndex);
			outputLayer[perceptronIndex].SetWeight(netToClone.outputLayer[perceptronIndex].GetWeight(weightIndex), weightIndex);
		}
	}
}

std::vector<BaseLayerPerceptron::gameCoords> ConnectNeuralNet::GetBaseLayerInputs(int i)
{
	std::vector<BaseLayerPerceptron::gameCoords> inputCoords = std::vector<BaseLayerPerceptron::gameCoords>(7);
	if (i < 7)
	{
		for (int j = 0; j < 7; j++)
		{
			inputCoords[i].column = i;
			inputCoords[i].row = j;
		}
	}
	else
	{
		for (int j = 0; j < 7; j++)
		{
			inputCoords[i-7].row = i-7;
			inputCoords[i-7].column = j;
		}
	}
	return inputCoords;
}
