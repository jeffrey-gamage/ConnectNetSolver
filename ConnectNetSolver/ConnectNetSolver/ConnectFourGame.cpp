#include "pch.h"
#include "ConnectFourGame.h"
#include <iostream>


ConnectFourGame::ConnectFourGame()
{
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			board[i][j] = WhichPlayer::neither;
		}
	}
}


ConnectFourGame::~ConnectFourGame()
{
}

bool ConnectFourGame::IsLegalMove(int columnToPlay)
{
	return board[columnToPlay][6] == WhichPlayer::neither;
}

void ConnectFourGame::PlayPiece(int columnToPlay, bool isPlayerOne)
{
	int row = 0;
	while (board[columnToPlay][row] != WhichPlayer::neither) { row++; }
	if (isPlayerOne) { 
		board[columnToPlay][row] = WhichPlayer::player1;
		CheckForGameOver(WhichPlayer::player1, columnToPlay, row);
	}
	else { 
		board[columnToPlay][row] = WhichPlayer::player2;
		CheckForGameOver(WhichPlayer::player2, columnToPlay, row);
	}
}

void ConnectFourGame::DisplayBoard()
{
	for (int i = 6; i >= 0; i--)
	{
		DisplayRow(i);
	}
	std::cout << "\n";
}

void ConnectFourGame::DisplayRow(int row)
{
	for (int i = 0; i < 7; i++)
	{
		switch (board[i][row])
		{
		case WhichPlayer::neither :{ std::cout << "- "; break; }
		case WhichPlayer::player1:{ std::cout << "X "; break; }
		case WhichPlayer::player2:{ std::cout << "O "; break; }
		}
	}
	std::cout << "\n";
}

int ConnectFourGame::DetectConnectLength(WhichPlayer lastPlayed,  int col, int row, int lengthDetected, ConnectFourGame::ConnectDirection direction)
{
	if (IsConnectionEnded( col, row, direction,lastPlayed))
	{
		return lengthDetected;
	}
	switch (direction)
	{
	case ConnectFourGame::ConnectDirection::up: {
		return DetectConnectLength(lastPlayed,  col, row - 1, lengthDetected + 1, direction);}
	case ConnectFourGame::ConnectDirection::up_right: {
		return DetectConnectLength(lastPlayed,  col+1, row - 1, lengthDetected + 1, direction);}
	case ConnectFourGame::ConnectDirection::right: {
		return DetectConnectLength(lastPlayed,  col+1, row, lengthDetected + 1, direction); }
	case ConnectFourGame::ConnectDirection::down_right: {
		return DetectConnectLength(lastPlayed,  col+1, row + 1, lengthDetected + 1, direction); }
	case ConnectFourGame::ConnectDirection::down: {
		return DetectConnectLength(lastPlayed,  col, row + 1, lengthDetected + 1, direction); }
	case ConnectFourGame::ConnectDirection::down_left: {
		return DetectConnectLength(lastPlayed,  col -1, row + 1, lengthDetected + 1, direction); }
	case ConnectFourGame::ConnectDirection::left: {
		return DetectConnectLength(lastPlayed,  col-1, row, lengthDetected + 1, direction); }
	case ConnectFourGame::ConnectDirection::up_left: {
		return DetectConnectLength(lastPlayed,  col-1, row - 1, lengthDetected + 1, direction); }
	}
	return 0;
}

bool ConnectFourGame::HasConnectedFourHere( int col, int row, WhichPlayer lastPlayed)
{
	if (board[col][row] == lastPlayed)
	{
		if (DetectConnectLength(lastPlayed, col, row, 1, ConnectFourGame::ConnectDirection::up) >= 4)
			return true; 
		if (DetectConnectLength(lastPlayed,  col, row, 1, ConnectFourGame::ConnectDirection::up_right) >= 4)
			return true;
		if (DetectConnectLength(lastPlayed,  col, row, 1, ConnectFourGame::ConnectDirection::right) >= 4)
			return true;
		if (DetectConnectLength(lastPlayed,  col, row, 1, ConnectFourGame::ConnectDirection::down_right) >= 4)
			return true;
		if (DetectConnectLength(lastPlayed, col, row, 1, ConnectFourGame::ConnectDirection::down) >= 4)
			return true;
		if (DetectConnectLength(lastPlayed, col, row, 1, ConnectFourGame::ConnectDirection::down_left) >= 4)
			return true;
		if (DetectConnectLength(lastPlayed, col, row, 1, ConnectFourGame::ConnectDirection::left) >= 4)
			return true;
		if (DetectConnectLength(lastPlayed, col, row, 1, ConnectFourGame::ConnectDirection::up_left) >= 4)
			return true;
		return false;
	}
	else
	{
		std::cout << "did not match space! \n";
		return false;
	}
}

bool ConnectFourGame::AreAllColumnsFull()
{
	for (int col = 0; col < 7; col++)
	{
		if (IsLegalMove(col))
			return true;
	}
	return false;
}

bool ConnectFourGame::IsConnectionEnded( int col, int row ,ConnectDirection direction, WhichPlayer lastPlayed)
{
	switch (direction)
	{
	case ConnectFourGame::ConnectDirection::up: {
		return row - 1 < 0 || board[col][row-1] != lastPlayed; }
	case ConnectFourGame::ConnectDirection::up_right: {
		return row - 1 < 0 || col + 1 > 6 || board[col+1][row-1] != lastPlayed; }
	case ConnectFourGame::ConnectDirection::right: {
		return col + 1 > 6 || board[col+1][row] != lastPlayed; }
	case ConnectFourGame::ConnectDirection::down_right: {
		return row + 1 > 6 || col + 1 > 6 || board[col+1][row+1] != lastPlayed; }
	case ConnectFourGame::ConnectDirection::down: {
		return row + 1 > 6, col || board[col][row+1] != lastPlayed; }
	case ConnectFourGame::ConnectDirection::down_left: {
		return row + 1 > 6 || col - 1 < 0 || board[col-1][row+1] != lastPlayed; }
	case ConnectFourGame::ConnectDirection::left: {
		return col - 1 < 0 || board[col-1][row] != lastPlayed; }
	case ConnectFourGame::ConnectDirection::up_left: {
		return row - 1 < 0 || col - 1 < 0 || board[col-1][row-1] != lastPlayed; }
	}
}

bool ConnectFourGame::CheckForGameOver(WhichPlayer lastPlayed, int col,int row)
{
	if (HasConnectedFourHere(col,row, lastPlayed))
	{
		winner = lastPlayed;
		if (lastPlayed == WhichPlayer::player1)
			std::cout << "player 1 wins!\n";
		else std::cout << "player 2 wins!\n";
		return true;
	}
	return AreAllColumnsFull();
}

ConnectFourGame::WhichPlayer ConnectFourGame::GetWinner()
{
	return winner;
}
