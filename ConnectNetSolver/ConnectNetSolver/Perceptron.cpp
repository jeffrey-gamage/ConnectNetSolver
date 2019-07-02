#include "pch.h"
#include "Perceptron.h"
#include <iostream>

Perceptron::Perceptron()
{
	Initialize();
}


Perceptron::~Perceptron()
{
}

float Perceptron::RandomFloat()
{
	return  static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

void Perceptron::Initialize()
{
	weights = std::vector<float>(7, 0.f);
	for (int i=0;i<7;i++)
	{
		weights[i] = RandomFloat();
	}
}

float Perceptron::GetOutput(std::vector<float> inputs)
{
	float output = 0.f;
	int i = 0;
	for (int i=0;i<7;i++)
	{
		output += inputs[i]*weights[i];
		i++;
	}
	return output;
}

float Perceptron::GetWeight(int index)
{
	return weights[index];
}
