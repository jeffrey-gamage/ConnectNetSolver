// ConnectNetSolver.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "ConnectFourGame.h"
#include "HumanConnectFourPlayer.h"
#include "ConnectFourPlayer.h"
#include "AIConnectFourPlayer.h"
#include <time.h>
#include "Teacher.h"

int main()
{
	srand(time(NULL));/*
	ConnectFourGame testGame = ConnectFourGame();
	HumanConnectFourPlayer player1 = HumanConnectFourPlayer();
	player1.isPlayerOne = true;
	AIConnectFourPlayer player2 = AIConnectFourPlayer();
	player2.isPlayerOne = false;
    std::cout << "Welcome to ConnectNetSolver!\n"; */

	////machine learning function test
	//player2.MultiplyNet();
	//std::cout << "prime has best score \n";
	//player2.RefineNet(12,13,-1);

	//std::cout << "plus has best score\n";
	//player2.RefineNet(-12, -13, -19);

	//std::cout << "minus has best score\n";
	//player2.RefineNet(19, 13, 49);
	////above should identify and select net with highest score
	////should select: prime, plus, minus

	Teacher teacher = Teacher();
	//teacher.InterLeagueTest("champion", "functionalTest2");
	teacher.Generations("parallelTest2", 200);
	//teacher.Challenge("champion");

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
