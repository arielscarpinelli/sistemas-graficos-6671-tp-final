#ifndef SUN_H_
#define SUN_H_

#include "Model.h"

#include "DayChangeable.h"

class Sun : public Model, public DayChangeable
{
public:
	Sun();
	virtual ~Sun();
	virtual void doDraw();
	virtual void setDay();
	virtual void setNight();
};

#endif /*SUN_H_*/
