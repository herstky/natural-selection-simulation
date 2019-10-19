#pragma once

#include <QtGlobal>
#include <QColor>
#include <QRectF>

#include <memory>
#include <utility>

class Simulation;
class View;

class Model : public std::enable_shared_from_this<Model>
{
	friend class Simulation;

public:
	enum class Status { alive, dead };
	enum class Shape { ellipse, rectangle, roundedRectangle };

	Model();
	Model(const Simulation& pSimulation);
	Model(const Simulation& pSimulation, const QPointF& pPosition);

	Status mStatus;
	QColor mColor;
	Shape mShape;
	std::shared_ptr<View> mView;

	virtual const qreal height() const;
	virtual const qreal heightP() const;
	virtual const qreal width() const;
	virtual const qreal widthP() const;
	virtual const QPointF center() const;
	virtual const QPointF centerP() const;
	virtual void setHeight(const qreal pHeight);
	virtual void setWidth(const qreal pWidth);
	virtual const qreal x() const;
	virtual const qreal xP() const;
	virtual const qreal y() const;
	virtual const qreal yP() const;
	virtual void setX(const qreal pX);
	virtual void setY(const qreal pY);
	const std::pair<int, int> coords(Simulation& pSimulation) const;
	virtual QRectF hitbox();
	virtual void die(const Simulation& pSimulation);

	void initView(const Simulation& pSimulation);

protected:
	qreal mX;
	qreal mY;

	virtual void init();

private:
	qreal mHeight;
	qreal mWidth;
};

