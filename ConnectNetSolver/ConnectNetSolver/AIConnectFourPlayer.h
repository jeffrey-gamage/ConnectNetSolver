#pragma once
#include "ConnectFourPlayer.h"
#include "ConnectNeuralNet.h"
#include <list>
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
	std::list<int> GetPickOrder(std::list<float> preferences);
	ConnectNeuralNet neuralNet;
};

