#ifndef SKYBOX_H_
#define SKYBOX_H_

#include "Model.h"
#include "PointOfView.h"
#include "DayChangeable.h"

class Skybox : public Model, public DayChangeable
{
public:
	Skybox(PointOfView* pov);
	virtual ~Skybox();
	virtual void setDay();
	virtual void setNight();

protected:
	
	virtual void predraw();
	virtual void doDraw();
	virtual void postdraw();
	
	unsigned int* _skybox;
	unsigned int _daybox[6];
	unsigned int _nightbox[6];
	
	PointOfView* pov;
};

#endif /*SKYBOX_H_*/
