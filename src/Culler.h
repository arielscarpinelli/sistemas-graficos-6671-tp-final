#ifndef CULLER_H_
#define CULLER_H_

#include "Polygon.h"
#include "PointOfView.h"

class Culler
{
public:
	Culler();
	virtual ~Culler();
	void updateFrustum(const PointOfView& pov);
	bool polygonInside(const Polygon2D &p);

protected:
	Polygon2D frustum;
};

#endif /*CULLER_H_*/
