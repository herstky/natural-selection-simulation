#include "simulation.h"
#include <QtWidgets/QLabel>

#include <iostream>

#include "entity.h"
#include "red.h"
#include "green.h"
#include "blue.h"
#include "food.h"



Simulation::Simulation(QQuickItem* parent)
    : container(parent),
	  board(parent->findChild<QQuickItem*>("board")),
      TICK_DURATION(50),
      TICKS_PER_STEP(1),
      ticksRemaining(TICKS_PER_STEP)
{
    Red::count = 0;
    Green::count = 0;
    Blue::count = 0;

    outputCounts();
	QQuickItem* foobar = board.view;
    QTimer* timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(run()));
    timer->start(TICK_DURATION);
}

Simulation::~Simulation() {}

void Simulation::run()
{
    for (auto item : board.view->childItems())
    {
        try
        {
            static_cast<Entity*>(item)->move(*this);
        }
        catch (const std::exception& e)
        {
            std::cout << "An exception was caught with message '" << e.what() << "'\n";
        }
    }

    if (ticksRemaining)
    {
        ticksRemaining--;
        return;
    }
	else
	{
		ticksRemaining = TICKS_PER_STEP;
	}

    if (QRandomGenerator::global()->bounded(100) < Red(board.view).getCreationChance())
    {
        Red* red = new Red(board.view);
    }
	if (QRandomGenerator::global()->bounded(100) < Food(board.view).getCreationChance())
	{
		Food* food = new Food(board.view);
	}

    for (auto item : board.view->childItems())
    {
        try
        {
            static_cast<Entity*>(item)->simulate(*this);
        }
        catch (const std::exception& e)
        {
            std::cout << "An exception was caught with message '" << e.what() << "'\n";
        }
    }
    outputCounts();
}

void Simulation::outputCounts()
{
    QQuickItem* parent = static_cast<QQuickItem*>(container->findChild<QObject*>("textRow"));
    QObject* redLabel = static_cast<QObject*>(parent->findChild<QObject*>("redCountText"));
    redLabel->setProperty("text", "Red: " + QString::number(Red::count));
    QObject* greenLabel = static_cast<QObject*>(parent->findChild<QObject*>("greenCountText"));
    greenLabel->setProperty("text", "Green: " + QString::number(Green::count));
    QObject* blueLabel = static_cast<QObject*>(parent->findChild<QObject*>("blueCountText"));
    blueLabel->setProperty("text", "Blue: " + QString::number(Blue::count));
}
