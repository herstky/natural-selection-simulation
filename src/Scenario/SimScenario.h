#pragma once

#include "Scenario/Scenario.h"

#include "NeuralNetwork.h"

class Simulation;

class SimScenario : public Scenario
{
public:
	SimScenario(Simulation* pSimulation, std::pair<NeuralNetwork, qreal> pBestNeuralNetwork);

	virtual void startRound() override;
	virtual void endRound() override;
	virtual void simulateStep() override;
	virtual void updateUI() override;

private:
	std::pair<NeuralNetwork, qreal> mBestNeuralNetwork;
	NeuralNetwork mNextNeuralNetwork;
};

