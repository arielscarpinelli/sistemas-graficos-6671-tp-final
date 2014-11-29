#include "Polygon.h"
#include <cmath>

Polygon2D::Polygon2D()
{
}

Polygon2D::~Polygon2D()
{
}

void Polygon2D::addVertex(const Point2D &v)
{
	vertices.push_back(v);
}

void Polygon2D::clear()
{
	vertices.clear();
}

void Polygon2D::rotate(float angle)
{
	float radians = angle * PI_BY_180;
	
	float cosA = cos(radians);
	float sinA = sin(radians);
	
	VertexArray::iterator it = vertices.begin();
	
	for(;(it != vertices.end()); it++)
	{
		Point2D &p = (*it);
		p.setXY(p.x * cosA + p.y * sinA, p.y * cosA - p.x * sinA);
	}
	
}

void Polygon2D::move(const Point2D &delta)
{
	VertexArray::iterator it = vertices.begin();
	
	for(;(it != vertices.end()); it++)
	{
		(*it) += delta;
	}
	
}


bool Polygon2D::intersects(const Polygon2D &against) const
{
	bool intersected = false;

	if((vertices.size() == 0) || (against.vertices.size() == 0))
		return false;
	
	VertexArray::const_iterator it = vertices.begin();
	
	for(;(it != vertices.end()) && (!intersected); it++)
	{
		intersected = against.pointInsidePolygon(*it);
	}
	if(!intersected)
	{
		for(it = against.vertices.begin(); (it != against.vertices.end()) && (!intersected); it++)
		{
			intersected = pointInsidePolygon(*it);
		}
	}
	return intersected;	
};

#define MIN(x,y) (x < y ? x : y)
#define MAX(x,y) (x > y ? x : y)

//horizintal left cross over direction algorithm
//-----------------------------------------------
//  bound   |   value that will be returned only if (p) lies on the bound or vertex
bool Polygon2D::pointInsidePolygon(const Point2D &p) const
{
    //cross Vertexs count of x
    int __count = 0;
    
    int N = vertices.size();
    
    //neighbour bound vertices
    Point2D p1 = vertices[0];
    
    //check all rays
    for(int i = 1; i <= N; ++i)
    {
        //Vertex is an vertex
        if(p == p1) return true;

        //right vertex
        const Point2D p2 = vertices[i % N];

        //ray is outside of our interests
        if(p.y < MIN(p1.y, p2.y) || p.y > MAX(p1.y, p2.y))
        {
            //next ray left Vertex
            p1 = p2; continue;
        }

        //ray is crossing over by the algorithm (common part of)
        if(p.y > MIN(p1.y, p2.y) && p.y < MAX(p1.y, p2.y))
        {
            //x is before of ray
            if(p.x <= MAX(p1.x, p2.x))
            {
                //overlies on a horizontal ray
                if(p1.y == p2.y && p.x >= MIN(p1.x, p2.x)) return true;

                //ray is vertical
                if(p1.x == p2.x)
                {
                    //overlies on a ray
                    if(p1.x == p.x) return true;
                    //before ray
                    else ++__count;
                }

                //cross Vertex on the left side
                else
                {
                    //cross Vertex of x
                    double xinters = (p.y - p1.y) * (p2.x - p1.x) / (p2.y - p1.y) + p1.x;

                    //overlies on a ray
                    if(fabs(p.x - xinters) < __DBL_EPSILON__) return true;

                    //before ray
                    if(p.x < xinters) ++__count;
                }
            }
        }
        //special case when ray is crossing through the vertex
        else
        {
            //p crossing over p2
            if(p.y == p2.y && p.x <= p2.x)
            {
                //next vertex
                const Point2D& p3 = vertices[(i+1) % N];

                //p.y lies between p1.y & p3.y
                if(p.y >= MIN(p1.y, p3.y) && p.y <= MAX(p1.y, p3.y))
                {
                    ++__count;
                }
                else
                {
                    __count += 2;
                }
            }
        }

        //next ray left Vertex
        p1 = p2;
    }

    return (__count % 2 != 0); // Return true if odd
}

std::ostream& operator<< (std::ostream& os, const Polygon2D& poly)
{
	os << "Polygon: ";
	Polygon2D::VertexArray::const_iterator it = poly.vertices.begin();
	
	for(;(it != poly.vertices.end()); it++)
	{
		os << (*it) << "; ";
	}
		
	return os;
}

std::ostream& operator<< (std::ostream& os, const Point2D& point)
{
	os << "x=" << point.x << " y= " << point.y;
	return os;
}
