#include "Sun.h"

float light_position[4] = {-.3, 1, 2, 0};

Sun::Sun()
{

	setDay();
    glEnable(GL_LIGHT0);
}

Sun::~Sun()
{
}

void Sun::doDraw()
{
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
		
}

void Sun::setDay()
{
	float light_color[4] = {1.0f, 1.0f, 1.0f, 1.0f};
	float light_ambient[4] = {0.4f, 0.4f, 0.4f, 1.0f};

	glLightfv(GL_LIGHT0, GL_SPECULAR, light_color);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	
}

void Sun::setNight()
{
	float light_color[4] = {0.3f, 0.3f, 0.3f, 1.0f};
	float light_ambient[4] = {0.1f, 0.0f, 0.2f, 1.0f};

	glLightfv(GL_LIGHT0, GL_SPECULAR, light_color);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	
}
