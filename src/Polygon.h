#ifndef POLYGON_H_
#define POLYGON_H_


#include <vector>
#include <ostream>

class Point2D {
public:	
	Point2D(float x = .0, float y = .0) {setXY(x, y);}; 
	void setXY(float x, float y) {this->x = x; this->y = y;}
	float x;
	float y;

	bool operator==(const Point2D& _right) const
    {
        return x == _right.x && y == _right.y;
    };
	
	void operator +=(const Point2D& _right)
    {
        x+= _right.x;
        y+= _right.y;
    };

};

#define PI_BY_180 0.017453292519943295769236907684886

#ifndef __DBL_EPSILON__ 
	#define __DBL_EPSILON__ 2.2204460492503131e-16 
#endif

class Polygon2D
{
public:
	typedef std::vector<Point2D> VertexArray;
	
	Polygon2D();
	virtual ~Polygon2D();
	void addVertex(const Point2D& v);
	bool intersects(const Polygon2D &against) const;
	bool pointInsidePolygon(const Point2D &p) const;
	void rotate(float angle);
	void move(const Point2D& delta);
	void clear();
	VertexArray& getVertices() {return vertices;};
	
	friend std::ostream& operator<< (std::ostream& os, const Polygon2D& poly); 
	
private:
	VertexArray vertices;
};

std::ostream& operator<< (std::ostream& os, const Polygon2D& poly); 
std::ostream& operator<< (std::ostream& os, const Point2D& point); 

#endif /*POLYGON_H_*/
