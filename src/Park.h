#ifndef PARK_H_
#define PARK_H_

#include "StreetBlock.h"

class Park : public StreetBlock
{
public:
	Park(int x, int y);
	virtual ~Park();

protected:
	virtual void doDraw();
	virtual void createChildren();
	
	static GLuint pasto;
};

#endif /*PARK_H_*/
