#ifndef BUILDING_H_
#define BUILDING_H_

#include "Model.h"

#define CANTIDAD_TEXTURAS_EDIFICIOS 5

class Building : public Model
{
public:
	Building(int x, int y, int rotation, int alto);
	virtual ~Building();
	virtual void draw();
	virtual void init();
	
protected:
	
	virtual void doDraw();
	
	static bool loaded;
	static int ventanas[CANTIDAD_TEXTURAS_EDIFICIOS][3];
	static int puertas[CANTIDAD_TEXTURAS_EDIFICIOS][3];

	int x, y, rotation;
	int alto;
	
};

#endif /*BUILDING_H_*/
