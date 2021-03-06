#pragma once
#include <vector>
class Perceptron
{
public:
	Perceptron();
	~Perceptron();
	static float RandomFloat();


	float GetOutput(std::vector<float> inputs);

	float GetWeight(int index);
	void SetWeight(float newWeight, int index);

private:
	std::vector<float> weights;
protected:
	void Initialize();
};

