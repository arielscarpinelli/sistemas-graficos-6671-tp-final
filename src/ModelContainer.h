#ifndef MODELCONTAINER_H_
#define MODELCONTAINER_H_

#include "Model.h"

class ModelContainer : public Model
{
public:
	ModelContainer();
	virtual ~ModelContainer();
	virtual void init();
	virtual void draw();
	virtual void setCuller(Culler * culler);

protected:
	
	virtual void createChildren();
	Model** children;
	int numChildren;
};

#endif /*MODELCONTAINER_H_*/
