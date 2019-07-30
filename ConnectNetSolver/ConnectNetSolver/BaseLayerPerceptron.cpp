#include "pch.h"
#include "BaseLayerPerceptron.h"
#include "ConnectFourGame.h"
#include <iostream>
#include <vector>


BaseLayerPerceptron::BaseLayerPerceptron()
{
	Initialize();
}


BaseLayerPerceptron::~BaseLayerPerceptron()
{
}

void BaseLayerPerceptron::SetInputs(std::vector<BaseLayerPerceptron::gameCoords> coords, ConnectFourGame * game)
{
	myCoordinates = coords;
	this->game = game;
}

float BaseLayerPerceptron::GetOutput()
{
	float output = 0.f;
	for (int i = 0; i < 7; i++)
	{
		output += this->GetWeight(i)*ConvertToFloat(game->board[myCoordinates[i].column][ myCoordinates[i].row]);
	}
	return output;
}

float BaseLayerPerceptron::ConvertToFloat(ConnectFourGame::WhichPlayer piece)
{
	float fVal = 0.f;
	if (piece == ConnectFourGame::WhichPlayer::player1)
		fVal = 1.f;
	else if (piece == ConnectFourGame::WhichPlayer::player2)
		fVal = -1.f;
	if (!isPlayerOne)
		fVal =  fVal *-1.f;
	return fVal;
}
