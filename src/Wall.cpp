#include "Wall.h"
#include <cmath>

GLuint Wall::textura = 0;

Wall::Wall(int x, int y, int rotation): x(x), y(y), rotation(rotation)
{
	if(!textura)
		textura = loadTexture("tex/BLOCK.bmp");
	
	Point2D v(-190, -2);
	boundingBox.addVertex(v);
	
	v.setXY(-190, 0);
	boundingBox.addVertex(v);
	
	v.setXY(190, 0);
	boundingBox.addVertex(v);
	
	v.setXY(190, -2);
	boundingBox.addVertex(v);

	boundingBox.rotate(-rotation);
	
	v.setXY(x, y);
	boundingBox.move(v);

	
	hitable = true;
	cullable = false;
}


Wall::~Wall()
{
}

void Wall::doDraw()
{
	float street_negro[4] = {0.0f, 0.0f, 0.0f, 0.0f};
	glBindTexture( GL_TEXTURE_2D, textura );
	
	glColor3f(0.7, 0.7, 0.7);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, street_negro);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, street_negro);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 64);
	
	glEnable(GL_TEXTURE_2D);
	
	glNormal3f(0, 1, 0);
	glPushMatrix();
	glTranslatef(x, y, 0);
	glRotatef(rotation, 0, 0, 1);
	int paso = 1;
	int j, i;

	for(j=0;j<5;j+=paso)
	{
		glBegin(GL_QUAD_STRIP);
			for(i=-190;i<=190;i+=paso)
			{
				glTexCoord2f(((float)i)/5,((float)j)/2.5); glVertex3f(i, 0, j);
				glTexCoord2f(((float)i)/5,((float)(j+paso))/2.5); glVertex3f(i, 0, j+paso);
			}
		glEnd();
	}
	
	glPopMatrix();
	
	glDisable(GL_TEXTURE_2D);

}
