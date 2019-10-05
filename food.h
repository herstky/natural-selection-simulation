#pragma once

#include "entity.h"

class Simulation;

class Food : public Entity
{
	friend class Simulation;
public:
	Food(const Simulation& simulation);
	Food(const Simulation& simulation, const QPointF& position);
	~Food();

	qreal height() override;
	qreal width() override;
	qreal volume();

protected:
	QColor color;
	qreal energyContent;
	qreal mass;
	qreal density;
	qreal aspectRatio;
	qreal depth;

private:
	static unsigned int count;
	static qreal creationChance;
};

