#pragma once

class ConnectFourGame
{
public:
	ConnectFourGame();
	~ConnectFourGame();
	enum class WhichPlayer {
		player1, player2, neither
	};
	bool IsLegalMove(int columnToPlay);
	void PlayPiece(int columnToPlay, bool isPlayerOne);
	void DisplayBoard();
	bool CheckForGameOver(WhichPlayer LastPlayed, int row, int col);
	WhichPlayer GetWinner();

private:	
	enum class ConnectDirection {
	up, up_right, right, down_right, down, down_left,left,up_left
	};
	WhichPlayer board [7] [7];
	WhichPlayer winner = WhichPlayer::neither;
	void DisplayRow(int row);
	int DetectConnectLength(WhichPlayer lastPiece, int row, int col, int lengthDetected, ConnectDirection direction);
	bool HasConnectedFourHere( int col, int row, WhichPlayer lastPlayed);
	bool AreAllColumnsFull();
	bool IsConnectionEnded( int col, int row, ConnectDirection direction, WhichPlayer lastPlayed);
};

