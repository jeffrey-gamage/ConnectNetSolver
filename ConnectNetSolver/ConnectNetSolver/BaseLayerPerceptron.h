#pragma once
#include "Perceptron.h"
#include "ConnectFourGame.h"
class BaseLayerPerceptron :
	public Perceptron
{
public:
	BaseLayerPerceptron();
	~BaseLayerPerceptron();

	void SetInputs(int column, ConnectFourGame* game);
	float GetOutput();
	bool isPlayerOne;

private:
	ConnectFourGame* game;
	int myColumn;
	float ConvertToFloat(ConnectFourGame::WhichPlayer piece);
};

