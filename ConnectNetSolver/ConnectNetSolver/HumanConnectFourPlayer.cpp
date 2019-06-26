#include "pch.h"
#include "HumanConnectFourPlayer.h"
#include <iostream>
#include <string>



HumanConnectFourPlayer::HumanConnectFourPlayer()
{
}

HumanConnectFourPlayer::~HumanConnectFourPlayer()
{
}

int HumanConnectFourPlayer::SelectMove(ConnectFourGame * currentGame, int nthChoice)
{
	if (nthChoice > 0) std::cout << "that column is full. Please choose another.";
	else std::cout << "Which column would you like to play in (1-7)?\n";

	std::string ColInput;
	std::getline(std::cin, ColInput);
	return std::stof(ColInput)-1;
}
