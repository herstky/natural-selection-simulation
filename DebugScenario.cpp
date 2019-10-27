#include "DebugScenario.h"

#include "Simulation.h"
#include "Creature.h"
#include "Food.h"

DebugScenario::DebugScenario(Simulation* pSimulation, std::pair<NeuralNetwork, qreal> pBestNeuralNetwork)
	: Scenario(pSimulation),
	mBestNeuralNetwork(pBestNeuralNetwork),
	mNextNeuralNetwork(mBestNeuralNetwork.first)
{
	mSimulation->mContainer.findChild<QQuickItem*>("progressColumn")->setVisible(false);
}

void DebugScenario::startRound()
{
	QPointF foodCenter = QPointF(mSimulation->board().widthP() / 2, mSimulation->board().heightP() / 2);
	std::shared_ptr<Food> food(new Food(*mSimulation, foodCenter));
	mSimulation->addFood(food);
	
	std::shared_ptr<Creature> creature(new Creature(QPointF(mSimulation->board().widthP() / 2 - 6,
		mSimulation->board().heightP() / 2)));

	mSimulation->addOrganism(creature);
}

void DebugScenario::endRound() {}

void DebugScenario::simulateStep() {}

void DebugScenario::simulateTick() {}

void DebugScenario::updateUI()
{
	QQuickItem* parent = static_cast<QQuickItem*>(mSimulation->mContainer.findChild<QObject*>("textRow"));
	QObject* creatureCountLabel = static_cast<QObject*>(parent->findChild<QObject*>("label1"));
	creatureCountLabel->setProperty("text", "Creatures: " + QString::number(Creature::count()));
	QObject* foodCountLabel = static_cast<QObject*>(parent->findChild<QObject*>("label2"));
	foodCountLabel->setProperty("text", "Food: " + QString::number(Food::count()));
	QObject* scoreLabel = static_cast<QObject*>(parent->findChild<QObject*>("label3"));
	scoreLabel->setProperty("text", "Score: " + QString::number(mSimulation->score()));
}

void DebugScenario::eat(Organism& pPredator, Entity& pPrey) {}

void DebugScenario::move(Organism& pOrganism) {}

void DebugScenario::eat(Organism& pOrganism) {}

