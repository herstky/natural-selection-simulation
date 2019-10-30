#include "CircleTrainingScenario.h"

#include <utility>

#include <QRandomGenerator>
#include <QPointF>

#include "Food.h"
#include "Simulation.h"
#include "NeuralNetwork.h"

CircleTrainingScenario::CircleTrainingScenario(Simulation* pSimulation, std::pair<NeuralNetwork, qreal> pBestNeuralNetwork)
	: CircleTraining(pSimulation, pBestNeuralNetwork)
{
	Organism::mStarvationPenalty = 100; // 5
	Organism::mOutOfBoundsPenalty = 0; // 0
	Organism::mNoScentsPenalty = 0; // 0
	Organism::mEnergyExpenditurePenalty = 0; // 200000000
	Organism::mFoodReward = 100; // 200
	Organism::mScentReward = 0; // 1
	Organism::mScentIncreaseReward = 0; // 10
	Organism::mScentDecreasePenalty = 0; // 20

	NeuralNetwork::mMutationChance = 20;
	NeuralNetwork::mSmallVarianceMagnitude = 1;
	NeuralNetwork::mLargeVarianceMagnitude = 100;
	NeuralNetwork::mLargeVarianceChance = 0;
}

NeuralNetwork CircleTrainingScenario::generateNeuralNetwork()
{
	NeuralNetwork neuralNetwork = NeuralNetwork::mutateWeights(mNextNeuralNetwork);
	return NeuralNetwork::mutateBasisWeights(neuralNetwork);
}

void CircleTrainingScenario::endRound() 
{
	for (auto group : mSimulation->organismGroups())
	{
		for (auto organism : group)
		{
			mGroupScores[organism->mKey].second += organism->score();
		}
	}

	for (auto pair : mKeyScore)
	{
		mGroupScores[pair.first].second += pair.second;
	}

	qreal sum = 0;
	for (auto group : mGroupScores)
	{
		sum += group.second;
	}

	std::sort(mGroupScores.begin(), mGroupScores.end(),
		[](const std::pair<int, qreal>& a, const std::pair<int, qreal>& b)
		{
			return (a.second > b.second);
		});

	std::cout << "-------------------------------------" << std::endl;
	std::cout << "Generation: " << mSimulation->generation() << std::endl;
	std::cout << "Current top score: " << mBestNeuralNetwork.second << std::endl;
	std::cout << "High score: " << mGroupScores[0].second << std::endl;
	std::cout << "Low score: " << mGroupScores[mGroupScores.size() - 1].second << std::endl;
	std::cout << "Average score: " << sum / mGroupScores.size() << std::endl;

	int first = mGroupScores[0].first;
	int second = mGroupScores.size() > 1 ? mGroupScores[1].first : -1;

	NeuralNetwork firstNN;
	NeuralNetwork secondNN;
	NeuralNetwork bestNN = mGroupMap[first];

	if (mGroupScores[0].second > mBestNeuralNetwork.second)
	{
		std::cout << "\nNew best neural network found!" << std::endl;
		mBestNeuralNetwork = std::pair<NeuralNetwork, qreal>(bestNN, mGroupScores[0].second);
		firstNN = bestNN;
		secondNN = second == -1 ? NeuralNetwork() : mGroupMap[second];
		int i = 0;
		for (auto weightMatrix : mBestNeuralNetwork.first.weights())
		{
			weightMatrix.save("data\\Theta" + std::to_string(i) + ".txt", arma::arma_ascii);
			i++;
		}
	}
	else
	{
		firstNN = mBestNeuralNetwork.first;
		secondNN = bestNN;
	}
	NeuralNetwork newNN = NeuralNetwork::crossoverWeights(firstNN, secondNN);
	newNN = NeuralNetwork::crossoverBasisWeights(newNN, secondNN);

	mNextNeuralNetwork = newNN;

	for (auto item : mSimulation->boardView().childItems())
	{
		item->deleteLater();
	}
	mSimulation->timer()->stop();
	mGroupScores.clear();
	mKeyScore.clear();
}