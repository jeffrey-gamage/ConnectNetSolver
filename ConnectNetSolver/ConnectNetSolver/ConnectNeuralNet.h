#pragma once
#include <list>
class ConnectFourGame;
class ConnectNeuralNet
{
public:
	ConnectNeuralNet();
	~ConnectNeuralNet();

	std::list<float> GenerateMoves(ConnectFourGame* CurrentGame);

private:
	float RandomFloat();
};

