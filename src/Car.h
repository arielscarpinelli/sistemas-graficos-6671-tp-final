#ifndef CAR_H_
#define CAR_H_

#include "Model.h"

#include "DayChangeable.h"

class Car : public Model, public DayChangeable
{
public:
	Car();
	virtual ~Car();
	void accelerate(int deltaY);
	void wheel(int deltaX);
	inline float getX() {return x;};
	inline float getY() {return y;};
	inline float getRotation() {return rotation;};
	inline float getSpeed() {return speed;};
	virtual void draw2D();
	virtual void time(float ellapsedSeconds);
	virtual void setDay();
	virtual void setNight();
	virtual void hited(Model* against);
	
protected:
	virtual void predraw();
	virtual void postdraw();
	virtual void doDraw();
	void calculateDirection();
	bool testHitedSide(Polygon2D::VertexArray &vertices, Point2D& car_begin_, Point2D& car_end_);
	
	float accelerateAndWheel(float segundos);
	
	int deltaX;
	int deltaY;
	
	float rotation; // grados
	float speed; // mts / seg
	float directionX;
	float directionY;
	float directionAngle;
	float x, y;
};

#endif /*CAR_H_*/
