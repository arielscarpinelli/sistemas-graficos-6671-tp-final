#include "Street.h"

/**
 * Contiene las calles del escenario
 */
Street::Street()
{
	textura = loadTexture("tex/Road_1line256.bmp");
}

Street::~Street()
{
}

void drawStreet()
{
	glNormal3f(0, 0, 1);
	int paso = 1;
	int j, i;
	for(j=0;j<380;j+=paso)
	{
		glBegin(GL_QUAD_STRIP);
			for(i=0;i<=20;i+=paso)
			{
				glTexCoord2f(((float)i)/5,((float)(j+paso))/5); glVertex3f(i, j+paso, 0);
				glTexCoord2f(((float)i)/5,((float)j)/5); glVertex3f(i, j, 0);
			}
		glEnd();
	}

}


void Street::doDraw()
{
	glColor3f(0.4, 0.4, 0.4);
	float street_negro[4] = {0.0f, 0.0f, 0.0f, 0.0f};
	float color[4] = {0.4f, 0.4f, 0.4f, 0.0f};
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, color);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, street_negro);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0);
	
	glBindTexture( GL_TEXTURE_2D, textura );
	
	glEnable(GL_TEXTURE_2D);

	int i;
	
	glPushMatrix();
		for(i=0;i<4;i++)
		{
			drawStreet();
			glTranslated(120, 0, 0);
		}
	glPopMatrix();
	
	glPushMatrix();
		glTranslated(380, 0, 0.001);		
		glRotated(90, 0, 0, 1);
		for(i=0;i<4;i++)
		{
			drawStreet();
			glTranslated(120, 0, 0);
		}
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

