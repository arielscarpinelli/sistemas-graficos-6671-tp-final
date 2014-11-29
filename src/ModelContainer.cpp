#include "ModelContainer.h"

ModelContainer::ModelContainer()
{
}

void ModelContainer::createChildren()
{
	numChildren = 0;
	children = NULL;
}

void ModelContainer::init()
{
	Model::init();
	createChildren();
	for(int i = 0; i < numChildren; i++)
		children[i]->init();
}

void ModelContainer::draw()
{
	Model::draw();
	if(!cull())
	{
		for(int i = 0; i < numChildren; i++)
			children[i]->draw();
	}
}

void ModelContainer::setCuller(Culler * culler)
{
	Model::setCuller(culler);
	for(int i = 0; i < numChildren; i++)
		children[i]->setCuller(culler);
}

ModelContainer::~ModelContainer()
{
	if(children)
	{
		for(int i = 0; i < numChildren; i++)
			delete children[i];
		delete[] children;
	}
}
