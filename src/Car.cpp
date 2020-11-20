#include "Car.h"
#include <math.h>
#include "stdio.h"

#define ROZAMIENTO 			5
#define ACELERACION 		50
#define FRENO 				20
#define MAXIMA_VELOCIDAD 	72 
#define MAXIMA_REVERSA 		10

#define ABS(x) ((x < 0 ? -x : x))
#define SGN(x) ((x < 0 ? -1 : 1))

#include "3ds/3dsLoader.h"

C3dsLoader loader;

//#include "dff/dff.h"
//LoadDFF dffLoader;

Car::Car()
{
	directionAngle = 0;
	speed = 0;
	directionX = 0;
	directionY = 1;
	deltaX = 0;
	deltaY = 0;
	rotation = 0;
	x = 130;
	y = 160;
	
	// Cargar el modelo
	if(!loader.Init_3ds("jeep/", "jeep/jeep1.3ds")) {
		printf("no puedo cargar jeep\n");
	}
//	dffLoader.ImportDFF(new TextureLoader(), "car/car.dff");

	float light_color[4] = {1.0f, 1.0f, 0.0f, 1.0f};
	float light_ambient[4] = {0, 0, 0, 1.0f};

    glLightfv(GL_LIGHT1, GL_SPECULAR, light_color);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_color);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45.0f);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.07f);
    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0);
    

    glLightfv(GL_LIGHT2, GL_SPECULAR, light_color);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, light_color);
    glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient);
    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 45.0f);
    glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.07f);
    glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 0);
        
}

Car::~Car()
{
}

void Car::accelerate(int deltaY)
{
	this->deltaY = deltaY;
}

void Car::wheel(int deltaX)
{
	this->deltaX = deltaX;
}

float Car::accelerateAndWheel(float t)
{
	float acceleration = 0;
	
	if(deltaY > 0)
	{
		if(speed < MAXIMA_VELOCIDAD)
			acceleration = deltaY * ACELERACION;
	} else if(deltaY < 0) {
		if(speed > -MAXIMA_REVERSA)
			acceleration = deltaY * FRENO;
	} else {
	
		// Aplico el rozamiento
		if(speed > 0)
			acceleration = -ROZAMIENTO;
		else if(speed < 0)
			acceleration = ROZAMIENTO;
	}
	float accByt = acceleration * t;
	
	float delta = (speed +  0.5 * accByt) * t;
	
	speed += accByt;
	if(deltaY == 0)
	{
		if(ABS(accByt) > ABS(speed))
			speed = 0;
	}
	
	if((deltaX != 0) && (speed != 0))
	{
		directionAngle += deltaX * SGN(speed) * (1.5 - (ABS(speed) / (MAXIMA_VELOCIDAD)));
		calculateDirection();
	}
	
	return delta;
}

void Car::calculateDirection()
{
	float radians = directionAngle * PI_BY_180;
	directionX = sin(radians);
	directionY = cos(radians);
	
}

void Car::predraw()
{
}

void Car::doDraw()
{


	float light_position[4] = {-0.6, 3.1f, 1.5f, 1.0f};
    glLightfv(GL_LIGHT1, GL_POSITION, light_position);
    light_position[0] = 0.6;
    glLightfv(GL_LIGHT2, GL_POSITION, light_position);

    float light_direction[3] = {0.0f, 1.0f, -0.7f};
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light_direction);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, light_direction);

	glColor3f(1,1,1);
		
	glPushMatrix();
		
		glTranslatef(0, -1.4, 0);
		glScalef(0.4, 0.4, 0.4);

		loader.Render_3ds();
		
	glPopMatrix();
}

void Car::postdraw()
{
			glRotatef(rotation, 0,0, 1);
			glTranslatef(-x, -y, 0);
}

void Car::draw2D()
{
	glColor3f(1, 0,0);
	glPushMatrix();
		glTranslatef(x, y, 0);
		glRotatef(-rotation, 0,0, 1);
		glRectf(-2.2, -2.75, 2.2, 2.75);
	glPopMatrix();
}

void Car::time(float seconds)
{

	float delta = accelerateAndWheel(seconds);
	
	
	rotation = directionAngle;
	
	
	y+= delta * directionY;
	x+= delta * directionX;

	
	boundingBox.clear();
	
	Point2D v(-2.2, -2.75);
	boundingBox.addVertex(v);
	
	v.setXY(-2.2, 2.75);
	boundingBox.addVertex(v);
	
	v.setXY(2.2, 2.75);
	boundingBox.addVertex(v);
	
	v.setXY(2.2, -2.75);
	boundingBox.addVertex(v);
	
	boundingBox.rotate(-rotation);
	
	v.setXY(x, y);
	boundingBox.move(v);
	glutPostRedisplay();	
}

#include "Wall.h"

void Car::hited(Model* against)
{
	Polygon2D::VertexArray &vertices = against->getBoundingBox().getVertices();
	Polygon2D::VertexArray &car_vertices = boundingBox.getVertices();
		
	if(speed > 0)
	{
		if(!testHitedSide(vertices,  car_vertices[1],  car_vertices[0]))
			testHitedSide(vertices,  car_vertices[2],  car_vertices[3]);
	} else {
		if(!testHitedSide(vertices,  car_vertices[0],  car_vertices[1]))
			testHitedSide(vertices,  car_vertices[3],  car_vertices[2]);
	}
}

bool Car::testHitedSide(Polygon2D::VertexArray &vertices, Point2D& car_begin_, Point2D& car_end_)	
{
	Polygon2D::VertexArray::iterator it = vertices.begin();
	Polygon2D::VertexArray::iterator next = it+1;
	
	// Voy a determinar contra que lado de la manzana se choco
	
	bool found = false;
	for(;(it != vertices.end()); it++, next++)
	{
	    
		if(next == vertices.end())
	    	next = vertices.begin();
	    
	    Point2D& begin_  = *it;
	    Point2D& end_  = *next;
	    	    
    	float denom = ((car_end_.y - car_begin_.y)*(end_.x - begin_.x)) -
                      ((car_end_.x - car_begin_.x)*(end_.y - begin_.y));

        float nume_a = ((car_end_.x - car_begin_.x)*(begin_.y - car_begin_.y)) -
                       ((car_end_.y - car_begin_.y)*(begin_.x - car_begin_.x));

        float nume_b = ((end_.x - begin_.x)*(begin_.y - car_begin_.y)) -
                       ((end_.y - begin_.y)*(begin_.x - car_begin_.x));


    	if(denom != 0.0f)
        {
	        float ua = nume_a / denom;
	        float ub = nume_b / denom;

	        if(ua >= 0.0f && ua <= 1.0f && ub >= 0.0f && ub <= 1.0f)
	        {
	            // Hay interseccion, calculo el angulo de incidencia con el producto escalar.
	        	
	        	float sideX = (end_.x - begin_.x);
	        	float sideY = (end_.y - begin_.y);
	        	float modulo = sqrt(sideX*sideX + sideY * sideY);
	        	
	        	
	        	float angle = (sideX * directionX
	        				+ sideY * directionY) / modulo ;
	        	if(fabs(angle) > 0.35 )
	        	{
		        	angle = acosf(angle);
		        	
		        	// Coeficiente de elasticidad 0.01
		        	angle = atan(tan(angle) * 100);
		        	
		        	angle = (angle - atan2(sideY , sideX )) / PI_BY_180;
	        	} else { // perpendiculares
	        		angle = directionAngle;
	        		speed = -speed;
	        		x -=directionX;
	        		y -=directionY;
	        	}
	        	directionAngle = angle;
	        	calculateDirection();
	        	speed *= 0.5;
	        	found = true;
	        	break;
	        }
        }


	}
	return found;
}

void Car::setDay()
{
    glDisable(GL_LIGHT1);
    glDisable(GL_LIGHT2);
	
}

void Car::setNight()
{
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
	
}
