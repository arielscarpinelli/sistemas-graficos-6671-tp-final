#ifndef POINTOFVIEW_H_
#define POINTOFVIEW_H_

#include <GL/glut.h>

class PointOfView
{
public:
	PointOfView();
	virtual ~PointOfView();
	virtual void set(float x, float y, float rotation);
	void setUp();
	void setBack();
	void setInside();
	void rotate(float delta);
	
	float camX;
	float camY;
	float camZ;

	float centerX;
	float centerY;
	float centerZ;
	
	float upY;
	float upZ;
	
	float x;
	float y;
	float rotation;
	float camRotationSpeed;
	float camRotation;
};

#endif /*POINTOFVIEW_H_*/
