#include "Model.h"

Model::Model()
{
	dl_handle = 0;
	hitable = false;
	cullable = false;
}

Model::~Model()
{
}

void Model::init()
{
	dl_handle = glGenLists(1);
	glNewList(dl_handle, GL_COMPILE);
		doDraw();
	glEndList();
}

void Model::time(float ellapsedSecs)
{
	
}

bool Model::hits(Model &against)
{
	if(hitable)
	{
		return against.boundingBox.intersects(boundingBox);
	}
	return false;
}

bool Model::cull()
{
	if(cullable)
	{
		return(!culler->polygonInside(boundingBox));
	}
	return false;
}

void Model::predraw()
{
	
}

void Model::postdraw()
{
	
}

void Model::setCuller(Culler* culler)
{
	this->culler = culler;
}

void Model::draw()
{
	if(cull())
		return;
	predraw(); 
	if (this->dl_handle) {
		glCallList(this->dl_handle);
	}
	postdraw();
};

void Model::draw2D()
{
};
