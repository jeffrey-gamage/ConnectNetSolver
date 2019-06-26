#pragma once
#include "ConnectFourPlayer.h"
class HumanConnectFourPlayer :
	public ConnectFourPlayer
{
public:
	HumanConnectFourPlayer();
	~HumanConnectFourPlayer();

private:
	virtual int SelectMove(ConnectFourGame* currentGame, int nthChoice) override;
};

