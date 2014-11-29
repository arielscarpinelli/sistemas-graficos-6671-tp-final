#include "Culler.h"

Culler::Culler()
{
	// El frustum se deberia calcular desde la matrix de model view
}

Culler::~Culler()
{
}

void Culler::updateFrustum(const PointOfView& pov)
{
	frustum.clear();
	
	Point2D v(-20, -5);
	if(pov.upZ > 0)
	{
		frustum.addVertex(v);
		v.setXY(20, -5);
	
		frustum.addVertex(v);
		v.setXY(240, 350);
		
		frustum.addVertex(v);
		v.setXY(-240, 350);
		frustum.addVertex(v);
		
	} else {
		// Vista superior
		v.setXY(-75, -75);
		frustum.addVertex(v);
		v.setXY(75, -75);
	
		frustum.addVertex(v);
		v.setXY(75, 75);
		
		frustum.addVertex(v);
		v.setXY(-75, 75);
		frustum.addVertex(v);
		
		
	}
	v.setXY(pov.x, pov.y);
	frustum.rotate(pov.rotation);
	frustum.move(v);
	
}

bool Culler::polygonInside(const Polygon2D &p)
{
	return frustum.intersects(p);
}
