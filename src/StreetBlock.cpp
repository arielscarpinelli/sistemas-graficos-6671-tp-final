#include "StreetBlock.h"
#include <cstdlib>

int StreetBlock::vereda = 0;
float StreetBlock::ALTO_CORDON = 0.25;

StreetBlock::StreetBlock(int x, int y):x(x), y(y)
{
	if(!vereda)
	{
		vereda = loadTexture("tex/Paveblank_64.bmp");

	}
	
	Point2D v(x,y);	
	boundingBox.addVertex(v);
	
	v.setXY(x, y+100);
	boundingBox.addVertex(v);
	
	v.setXY(x+100, y+100);
	boundingBox.addVertex(v);

	v.setXY(x+100, y);
	boundingBox.addVertex(v);

	hitable = true;
	cullable = true;
}


StreetBlock::~StreetBlock()
{
}


void StreetBlock::createChildren()
{
	numChildren = CANTIDAD_EDIFICIOS_MANZANA;
	children = new Model*[numChildren];
	int j=0;
	for(int i = 0;i<8;i++)
	{
		children[j++] = new Building(x + 15 + i*10, y + 10       ,   0, rand() % 32 + 8);
		children[j++] = new Building(x + 10       , y + 15 + i*10, -90, rand() % 32 + 8);
		children[j++] = new Building(x + 15 + i*10,         y +90, 180, rand() % 32 + 8);
		children[j++] = new Building(x + 90       , y + 15 + i*10,  90, rand() % 32 + 8);
	}
}

void StreetBlock::drawVereda()
{
	float color[4] = {0.4f, 0.4f, 0.4f, 1.0f};
	float negro[4] = {0.0f, 0.0f, 0.0f, 0.0f};
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, color);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, negro);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0);
	glColor3f(0.7, 0.7, 0.7);

	glBindTexture( GL_TEXTURE_2D, vereda);
	
	glBegin(GL_QUAD_STRIP);
				
		glNormal3f(0, -1, 0);
		int paso = 1;
		int i;
		int j;
		
		for(i=0;i<=100;i+=paso)
		{
			glTexCoord2f(((float)i)/5,ALTO_CORDON / 5); glVertex3f(i, 0, ALTO_CORDON);
			glTexCoord2f(((float)i)/5,0); glVertex3f(i, 0, 0);
			
		}
	
	glEnd();

	glNormal3f(0, 0, 1);
	for(j=0;j<=10;j+=paso)
	{
		glBegin(GL_QUAD_STRIP);
			for(i=0;i<=100;i+=paso)
			{
				glTexCoord2f(((float)i)/5,((float)(j+paso))/5); glVertex3f(i, j+paso, ALTO_CORDON);
				glTexCoord2f(((float)i)/5,((float)j)/5); glVertex3f(i, j, ALTO_CORDON);
			}
		glEnd();
	}
	
	for(j=90;j<100;j+=paso)
	{
		glBegin(GL_QUAD_STRIP);
			for(i=0;i<=100;i+=paso)
			{
				glTexCoord2f(((float)i)/5,((float)(j+paso))/5); glVertex3f(i, j+paso, ALTO_CORDON);
				glTexCoord2f(((float)i)/5,((float)j)/5); glVertex3f(i, j, ALTO_CORDON);
			}
		glEnd();
	}

	for(j=10;j<=90;j+=paso)
	{
		glBegin(GL_QUAD_STRIP);
			for(i=0;i<=10;i+=paso)
			{
				glTexCoord2f(((float)i)/5,((float)(j+paso))/5); glVertex3f(i, j+paso, ALTO_CORDON);
				glTexCoord2f(((float)i)/5,((float)j)/5); glVertex3f(i, j, ALTO_CORDON);
			}
		glEnd();
		glBegin(GL_QUAD_STRIP);
			for(i=90;i<=100;i+=paso)
			{
				glTexCoord2f(((float)i)/5,((float)(j+paso))/5); glVertex3f(i, j+paso, ALTO_CORDON);
				glTexCoord2f(((float)i)/5,((float)j)/5); glVertex3f(i, j, ALTO_CORDON);
			}
		glEnd();
	}
	
	glNormal3f(0, 1, 0);
	glBegin(GL_QUAD_STRIP);
		for(i=0;i<=100;i+=paso)
		{
			glTexCoord2f(((float)i)/5,0); glVertex3f(i, 100, 0);
			glTexCoord2f(((float)i)/5,ALTO_CORDON/5); glVertex3f(i, 100, ALTO_CORDON);
			
		}
	glEnd();

	glNormal3f(-1, 0, 0);
	glBegin(GL_QUAD_STRIP);
		for(i=0;i<=100;i+=paso)
		{
			glTexCoord2f(((float)i)/5,0); glVertex3f(0, i, 0);
			glTexCoord2f(((float)i)/5,ALTO_CORDON/5); glVertex3f(0, i, ALTO_CORDON);
			
		}
	glEnd();

	glNormal3f(1, 0, 0);
	glBegin(GL_QUAD_STRIP);
		for(i=0;i<=100;i+=paso)
		{
			glTexCoord2f(((float)i)/5,ALTO_CORDON/5); glVertex3f(100, i, ALTO_CORDON);
			glTexCoord2f(((float)i)/5,0); glVertex3f(100, i, 0);
			
		}
	glEnd();
	
}


void StreetBlock::doDraw()
{
	
	
	glEnable(GL_TEXTURE_2D);
	
		
	glPushMatrix();
	
	glTranslatef(x, y, 0);

	drawVereda();
	
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);


}

void StreetBlock::draw2D()
{
	if(!cull())
		glColor3f(1, 1, 1);
	else
		glColor3f(0.8, 0.8, 0.8);
		
	glBegin(GL_POLYGON);

		glVertex2f(x, y);
		glVertex2f(x + 100,  y);
		glVertex2f(x + 100, y +100);
		glVertex2f(x, y + 100);

	glEnd();
	
}

