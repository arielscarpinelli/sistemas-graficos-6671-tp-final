#ifndef STREETBLOCK_H_
#define STREETBLOCK_H_

#include "ModelContainer.h"
#include "Building.h"

#define CANTIDAD_EDIFICIOS_MANZANA 32

class StreetBlock : public ModelContainer
{
public:
	StreetBlock(int x, int y);
	virtual ~StreetBlock();
	virtual void draw2D();	
	
protected:
	
	virtual void createChildren();
	
	virtual void doDraw();
	
	void drawVereda();
	
	int x, y;
	
	static int vereda;
	
	static float ALTO_CORDON;
};

#endif /*STREETBLOCK_H_*/
