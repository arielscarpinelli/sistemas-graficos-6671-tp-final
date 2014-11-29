#ifndef WALL_H_
#define WALL_H_

#include "Model.h"

class Wall : public Model
{
public:
	Wall(int x, int y, int rotation);
	
	virtual ~Wall();
	
protected:
	virtual void doDraw();
	
	static GLuint textura;
	
	int x;
	int y;
	int rotation;
};

#endif /*WALL_H_*/
