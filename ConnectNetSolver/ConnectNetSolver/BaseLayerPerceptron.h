#pragma once
#include "Perceptron.h"
#include "ConnectFourGame.h"
#include <vector>
class BaseLayerPerceptron :
	public Perceptron
{
public:
	BaseLayerPerceptron();
	~BaseLayerPerceptron();

	struct gameCoords {
		int row;
		int column;
	};

	std::vector<gameCoords> myCoordinates;
	void SetInputs(std::vector<gameCoords> coords, ConnectFourGame* game);
	float GetOutput();
	bool isPlayerOne;

private:
	ConnectFourGame* game;
	float ConvertToFloat(ConnectFourGame::WhichPlayer piece);
};

