#pragma once

class ConnectFourGame;
class ConnectFourPlayer
{
public:
	ConnectFourPlayer();
	~ConnectFourPlayer();

	void MakeMove(ConnectFourGame* currentGame, int numTries);
	bool isPlayerOne;

private:
	virtual int SelectMove(ConnectFourGame* currentGame, int nthChoice);
};

