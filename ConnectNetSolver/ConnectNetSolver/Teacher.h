#pragma once
#include "AIConnectFourPlayer.h"
#include "HumanConnectFourPlayer.h"
#include <string>
class Teacher
{
public:
	const int LEAGUE_SIZE = 8;
	Teacher();
	~Teacher();

	void Generations(std::string leagueName, int numGenerations); //train a league of nets for n generations. 
	//LeagueName will be prefixed to names of all nets. If team does not exist, it will be created.
	//once training is complete, networks are saved to file.

	void ExhibitionMatch(std::string leagueName); // have the two top-ranked nets in the league play a game with the board state piped
	//to stdout

	void Challenge(std::string leagueName); // play a game against a net in the selected league

	void InterLeagueTest(std::string league1, std::string league2); //have each net in league1 play each net in league2, 
	//then output the aggregate scores of each league to stdout


private:
	void Generation(); // all nets play a game against each other network in the league then the 
	//net with the lowest score is replaced by a mutated copy of the net with the highest score

	static void ScheduleLearningGame(AIConnectFourPlayer* player1, AIConnectFourPlayer* player2); //helper function to schedule league learning games asynchronously

	void LoadLeague(std::string leagueName);

	void Mutate(); // creates a copy of the most successful net, varying the batch size and learning
	//rate of the copy

	AIConnectFourPlayer league[8];

};

