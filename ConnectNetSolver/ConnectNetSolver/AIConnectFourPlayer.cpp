#include "pch.h"
#include "AIConnectFourPlayer.h"
#include <vector>
#include <iostream>
#include <fstream>
#include "ConnectNeuralNet.h"

AIConnectFourPlayer::AIConnectFourPlayer()
{
	primeNet = ConnectNeuralNet();
}


AIConnectFourPlayer::~AIConnectFourPlayer()
{
}

void AIConnectFourPlayer::WriteToFile(std::string fileName)
{
	std::ofstream saveStateStream;
	saveStateStream.open(fileName,std::ios::trunc);
	for (int pIndex = 0; pIndex < 7; pIndex++)
	{
		for (int wIndex = 0; wIndex < 7; wIndex++)
		{
			saveStateStream << primeNet.baseLayer[pIndex].GetWeight(wIndex) << "\n";
			saveStateStream << primeNet.hiddenLayer[pIndex].GetWeight(wIndex) << "\n";
			saveStateStream << primeNet.outputLayer[pIndex].GetWeight(wIndex) << "\n";
		}
	}
	saveStateStream.close();
}

void AIConnectFourPlayer::ReadFromFile(std::string fileName)
{
	std::ifstream loadStateStream;
	loadStateStream.open(fileName);		
	if (loadStateStream.is_open())
	{
		for (int pIndex = 0; pIndex < 7; pIndex++)
		{

			for (int wIndex = 0; wIndex < 7; wIndex++)
			{
				std::string weightString;
				if (std::getline(loadStateStream, weightString))
				{
					primeNet.baseLayer[pIndex].SetWeight(std::stof(weightString), wIndex);
				}
				if (std::getline(loadStateStream, weightString))
				{
					primeNet.hiddenLayer[pIndex].SetWeight(std::stof(weightString), wIndex);
				}
				if (std::getline(loadStateStream, weightString))
				{
					primeNet.outputLayer[pIndex].SetWeight(std::stof(weightString), wIndex);
				}
			}
		}
	}
	loadStateStream.close();
}

void AIConnectFourPlayer::ResetScores()
{
	primeScore = 0;
	plusScore = 0;
	minusScore = 0;
}

int AIConnectFourPlayer::GetTotalScore()
{
	return primeScore + plusScore + minusScore;
}

void AIConnectFourPlayer::MultiplyNet()
{
	plusNet = ConnectNeuralNet();
	minusNet = ConnectNeuralNet();
	plusNet.BecomeClone(primeNet);
	minusNet.BecomeClone(primeNet);
	weightsToModify = selectWeightsToModify();
	for (AIConnectFourPlayer::PerceptronWeightSelector weightToModify : weightsToModify)
	{
		switch (weightToModify.layer)
		{
		case 0: //base layer
		{
			plusNet.baseLayer[weightToModify.index].SetWeight(plusNet.baseLayer[weightToModify.index].GetWeight(weightToModify.weight)+learningRate,weightToModify.weight);
			minusNet.baseLayer[weightToModify.index].SetWeight(minusNet.baseLayer[weightToModify.index].GetWeight(weightToModify.weight) - learningRate, weightToModify.weight);
			break;
		}		
		case 1: //hidden layer
		{
			plusNet.hiddenLayer[weightToModify.index].SetWeight(plusNet.hiddenLayer[weightToModify.index].GetWeight(weightToModify.weight) + learningRate, weightToModify.weight);
			minusNet.hiddenLayer[weightToModify.index].SetWeight(minusNet.hiddenLayer[weightToModify.index].GetWeight(weightToModify.weight) - learningRate, weightToModify.weight);
			break;
		}		
		case 2: //output layer
		{
			plusNet.outputLayer[weightToModify.index].SetWeight(plusNet.outputLayer[weightToModify.index].GetWeight(weightToModify.weight) + learningRate, weightToModify.weight);
			minusNet.outputLayer[weightToModify.index].SetWeight(minusNet.outputLayer[weightToModify.index].GetWeight(weightToModify.weight) - learningRate, weightToModify.weight);
			break;
		}
		}
	}
}

void AIConnectFourPlayer::RefineNet()
{
	if (plusScore > primeScore&&plusScore > minusScore)
	{
		primeNet = plusNet;
	}
	else if (minusScore > primeScore &&minusScore > plusScore)
	{
		primeNet = minusNet;
	}
	MultiplyNet();
}

void AIConnectFourPlayer::DisplayWeightsBeingUpdated()
{
	for (AIConnectFourPlayer::PerceptronWeightSelector weightToModify : weightsToModify)
	{
		std::cout << weightToModify.layer << " / " << weightToModify.index << " / " << weightToModify.weight << " : ";
		switch (weightToModify.layer)
		{
		case 0: //base layer
		{
			std::cout<<primeNet.baseLayer[weightToModify.index].GetWeight(weightToModify.weight)<<" ";
			break;
		}
		case 1: //hidden layer
		{

			std::cout << primeNet.hiddenLayer[weightToModify.index].GetWeight(weightToModify.weight) << " ";
			break;
		}
		case 2: //output layer
		{
			std::cout << primeNet.outputLayer[weightToModify.index].GetWeight(weightToModify.weight) << " ";
			break;
		}
		}
	}
	std::cout << "\n";
}

void AIConnectFourPlayer::BecomeMutatedClone(AIConnectFourPlayer playerToCopy)
{
	primeNet.BecomeClone(playerToCopy.primeNet);
	batchSize = playerToCopy.batchSize + (rand() % 3 )- 1;
	if (batchSize < 1) batchSize = 1;
	learningRate = playerToCopy.learningRate * (0.5f + Perceptron::RandomFloat());
	MultiplyNet();
}

int AIConnectFourPlayer::SelectMove(ConnectFourGame * currentGame, int nthChoice)
{
	std::vector<float> preferences;
	switch (activeNet) {
		case WhichNet::prime:{ 
			preferences = primeNet.GenerateMoves(currentGame); 
			break; 
		}
		case WhichNet::plus:{
			preferences = plusNet.GenerateMoves(currentGame);
			break;
		}
		case WhichNet::minus:{
			preferences = minusNet.GenerateMoves(currentGame);
			break; 
		}
	}
	if (nthChoice >= 7) {
		std::cout << "all options rejected! Game should be over.\n";
		return rand()%7;
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
		preferences[maxAddress] = preferences[minAddress] - 0.0001f;
	}
	return pickOrder;
}

std::vector<AIConnectFourPlayer::PerceptronWeightSelector> AIConnectFourPlayer::selectWeightsToModify()
{
	int numNodesToSelect = batchSize;
	std::vector<AIConnectFourPlayer::PerceptronWeightSelector> allNodes = GetAllNodes();
	if (numNodesToSelect > allNodes.size())
		numNodesToSelect = allNodes.size();
	std::vector<AIConnectFourPlayer::PerceptronWeightSelector>  selectedNodes = std::vector<AIConnectFourPlayer::PerceptronWeightSelector>(numNodesToSelect);
	int numRemainingNodes= allNodes.size();
	for (int i = 0; i < numNodesToSelect; i++)
	{
		int nodeAddrToSelect = rand() % numRemainingNodes;
		selectedNodes[i] = allNodes[nodeAddrToSelect];
		allNodes[nodeAddrToSelect] = allNodes[numRemainingNodes - 1];
		numRemainingNodes--;
	}
	return selectedNodes;
}

std::vector<AIConnectFourPlayer::PerceptronWeightSelector> AIConnectFourPlayer::GetAllNodes()
{
	std::vector<AIConnectFourPlayer::PerceptronWeightSelector> allNodes = std::vector<AIConnectFourPlayer::PerceptronWeightSelector>(147);
	for (int i = 0; i < 147; i++)
	{
		allNodes[i].index = (i/7) % 7;
		allNodes[i].layer = i / 49;
		allNodes[i].weight = i % 7;
	}
	return allNodes;
}

