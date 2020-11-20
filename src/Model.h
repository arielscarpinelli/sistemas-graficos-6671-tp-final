#ifndef MODEL_H_
#define MODEL_H_

#include  "GL/glut.h"

#include "Polygon.h"
#include "Culler.h"

class Model
{
public:
	Model();
	virtual void init();
	virtual void draw();
	virtual void draw2D();
	virtual void time(float ellapsedSecs);
	virtual ~Model();
	virtual void setCuller(Culler * culler);
	virtual bool hits(Model &against);
	Polygon2D& getBoundingBox() {return boundingBox;};
	
protected:
	virtual void doDraw() = 0;
	virtual void predraw();
	virtual void postdraw();
	virtual bool cull();
	GLuint dl_handle;
	Culler * culler;
	Polygon2D boundingBox;
	bool hitable;
	bool cullable;
};


// Esta mal tener esto aca
GLuint loadTexture( const char * filename);


#endif /*MODEL_H_*/
