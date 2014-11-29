#ifndef STREET_H_
#define STREET_H_

#include "Model.h"

class Street : public Model
{
public:
	Street();
	virtual ~Street();
protected:
	virtual void doDraw();
	int textura;
};

#endif /*STREET_H_*/
