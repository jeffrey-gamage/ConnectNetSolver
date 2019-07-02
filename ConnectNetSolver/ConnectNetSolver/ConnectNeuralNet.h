#pragma once
#include <vector>
#include "Perceptron.h"
#include "BaseLayerPerceptron.h"
class ConnectFourGame;
class ConnectNeuralNet
{
public:
	ConnectNeuralNet();
	~ConnectNeuralNet();

	std::vector<float> GenerateMoves(ConnectFourGame* CurrentGame);


private:	
	Perceptron outputLayer[7];
	Perceptron hiddenLayer[7];
	BaseLayerPerceptron baseLayer[7];
	ConnectFourGame* game;
};

