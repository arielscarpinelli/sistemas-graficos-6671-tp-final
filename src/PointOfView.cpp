#include "PointOfView.h"
#include <math.h>

PointOfView::PointOfView()
{
	setBack();
}

PointOfView::~PointOfView()
{
}

void PointOfView::setBack()
{
	camX = 0;
	camY = -8;
	camZ = 3;
	centerX = 0;
	centerY = 0;
	centerZ = 1;
	upZ = 1;
	upY = 0;
	camRotation = 0;
}

void PointOfView::setUp()
{
	camX = 0;
	camY = -15;
	camZ = 80;
	centerX = 0;
	centerY = 0;
	centerZ = 0;
	upZ = 0;
	upY = 1;
	camRotation = 0;
}

void PointOfView::setInside()
{
	camX = -0.3;
	camY = -0.5;
	camZ = 2.5;
	centerX = -0.1;
	centerY = 5;
	centerZ = 2;
	upY = 0;
	upZ = 1;
	camRotation = 0;
}

void PointOfView::rotate(float delta)
{
	this->camRotationSpeed = delta;
}

void PointOfView::set(float x, float y, float rotation)
{
	//float rotation = c->getRotation() * 6.28 / 360;
	//gluLookAt (c->getX()  - 5.0f * sin(rotation), c->getY() - 5.0f * cos(rotation) , 2.5, c->getX(), c->getY(), 1, 0, 0, 1);
	camRotation += camRotationSpeed;
	gluLookAt(camX, camY, camZ, centerX,centerY, centerZ, 0, upY, upZ);
	glRotatef(camRotation, 0, 0, 1);
	this->x = x;
	this->y = y;
	this->rotation = rotation + camRotation;
}
