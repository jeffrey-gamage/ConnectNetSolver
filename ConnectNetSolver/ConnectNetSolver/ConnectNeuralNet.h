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

	void BecomeClone(ConnectNeuralNet netToClone);

	Perceptron outputLayer[14];
	Perceptron hiddenLayer[14];
	BaseLayerPerceptron baseLayer[14];
private:	
	ConnectFourGame* game;
	std::vector<BaseLayerPerceptron::gameCoords> GetBaseLayerInputs(int i);
};

