#pragma once
#include "ConnectFourPlayer.h"
#include "ConnectNeuralNet.h"
#include <vector>
class ConnectFourGame;
class ConnectNeuralNet;

class AIConnectFourPlayer :
	public ConnectFourPlayer
{
public:
	AIConnectFourPlayer();
	~AIConnectFourPlayer();

private:
	virtual int SelectMove(ConnectFourGame* currentGame, int nthChoice) override;
	std::vector<int> GetPickOrder(std::vector<float> preferences);
	ConnectNeuralNet neuralNet;
};

