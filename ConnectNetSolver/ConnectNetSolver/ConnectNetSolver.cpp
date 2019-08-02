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
#include <string>
#include <stdexcept>
std::string GetInput()
{
	std::string command = "";
	std::getline(std::cin, command);
	return command;
}
int main()
{
	srand(time(NULL));
	Teacher teacher = Teacher();
	std::string input;
	std::cout << "Welcome to ConnectNetSolver! Please choose an option:\n";
	do {
		std::cout << "train, compare, challenge, spectate, clone, help, or quit.\n";
		input = GetInput();
		if (input == "train")
		{
			std::cout << "enter the name of the AI you wish to train. If it does not exist, it will be created.\n Do not use names ending with a numeral.\n";
			std::string leagueName = GetInput();
			try {
				std::cout << "enter the number of generations to train: ";
				int numGenerations = std::stoi(GetInput());
				teacher.Generations(leagueName, numGenerations);
			}
			catch(const std::invalid_argument& invArg){
				std::cout << "invalid input!\n";
			}
		}
		else if (input == "compare")
		{
			std::cout << "enter the name of the first ai.\n";
			std::string league1Name = GetInput();
			std::cout << "enter the name of the second ai.\n";
			std::string league2Name = GetInput();
			teacher.InterLeagueTest(league1Name, league2Name);
		}
		else if (input == "challenge")
		{
			std::cout << "enter the name of the AI you want to challenge.\n";
			std::string leagueName = GetInput();
			teacher.Challenge(leagueName);
		}
		else if (input == "spectate")
		{
			std::cout << "enter the name of the AI you want to spectate.\n";
			std::string leagueName = GetInput();
			teacher.ExhibitionMatch(leagueName);
		}
		else if (input == "clone")
		{
			std::cout << "enter the name of the AI you want to copy.\n";
			std::string oldName = GetInput();
			std::cout << "enter a new name for the copy. Do not use names ending with a numeral.\n";
			std::string newName = GetInput();
			teacher.LoadLeague(oldName);
			teacher.SaveLeague(newName);
		}
		else if (input == "help")
		{
			std::cout << "train: allow the selected AI to practice against each other for n generations.\nIf no AI exists by that name, create a new one.";
			std::cout << "compare: have 2 AIs play against each other and print their aggreagate scores\n";
			std::cout << "challenge: play against the selected AI.\n"; 
			std::cout << "spectate: watch 2 AI from the selected group play against each other\n";
			std::cout << "clone: save a copy of the chosen AI with a new name\n";
		}
		else if (input != "quit")
		{
			std::cout << "command not recognized. Please try again.\n";
		}
	} while (input != "quit");
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
