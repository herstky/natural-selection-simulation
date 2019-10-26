#pragma once

#include "Model.h"

class Simulation;

class Entity : public Model
{
	friend class Simulation;

public:
	enum class Type { none, predator, prey };

	Entity();
	Entity(const QPointF& pPosition);
	
	virtual void simulate(Simulation& pSimulation);
	virtual void train(Simulation& pSimulation);
	virtual void move(const Simulation& pSimulation);
	virtual void detectCollisions(Simulation& pSimulation);
	virtual void collide(Simulation& pSimulation, Entity& pOther);
	virtual void emanateScent(Simulation& pSimulation);
	
	Type getType();
	qreal getEnergyContent();
	qreal getMass();
	qreal getDensity();
	qreal getAspectRatio();
	qreal getDepth();

protected:
	Type mType;
	qreal mEnergyContent; // [kJ/kg]
	qreal mMass; // [kg]
	qreal mDensity; // [kg/m^3]
	qreal mAspectRatio; // width/height
	qreal mDepth; // [m]
};

