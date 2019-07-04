#pragma once
#include "ConnectFourPlayer.h"
#include "ConnectNeuralNet.h"
#include <vector>
#include <string>
class ConnectFourGame;
class ConnectNeuralNet;

class AIConnectFourPlayer :
	public ConnectFourPlayer
{
public:
	AIConnectFourPlayer();
	~AIConnectFourPlayer();

	float learningRate = 0.2f;
	int batchSize = 3;

	struct PerceptronWeightSelector
	{
		int layer;//0 for base, 1 for hidden, 2 for output
		int index;//address of perceptron
		int weight;//which weight of perceptron to tweak
	};

	void WriteToFile(std::string fileName);
	void ReadFromFile(std::string fileName);

	void MultiplyNet(); //select weights to tweak and test plus and minus, from prime. plus and minus nets will be overwritten
	void RefineNet(int plusScore, int primeScore, int minusScore); //the net with the best score becomes the prime net

	void MakeMovePlus(ConnectFourGame* currentGame, int numTries);//uses + modified version of net to generate move
	void MakeMoveMinus(ConnectFourGame* currentGame, int numTries);// uses - modified version of net to generate move

	void DisplayWeightsBeingUpdated(); //testing function to verify if weights are being updated correctly

private:
	virtual int SelectMove(ConnectFourGame* currentGame, int nthChoice) override;
	int SelectMovePlus(ConnectFourGame* currentGame, int nthChoice);
	int SelectMoveMinus(ConnectFourGame* currentGame, int nthChoice);
	std::vector<int> GetPickOrder(std::vector<float> preferences);
	ConnectNeuralNet primeNet;
	ConnectNeuralNet plusNet;
	ConnectNeuralNet minusNet;

	std::vector<PerceptronWeightSelector>  selectWeightsToModify(); 
	std::vector<AIConnectFourPlayer::PerceptronWeightSelector> weightsToModify;//added for testing;
	std::vector<PerceptronWeightSelector> GetAllNodes();
};

