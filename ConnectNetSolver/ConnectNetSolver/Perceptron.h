#pragma once
#include <vector>
class Perceptron
{
public:
	Perceptron();
	~Perceptron();
	float RandomFloat();


	float GetOutput(std::vector<float> inputs);

	float GetWeight(int index);

private:
	std::vector<float> weights;
protected:
	void Initialize();
};

