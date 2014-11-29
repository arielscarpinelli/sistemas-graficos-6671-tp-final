#include "Park.h"

GLuint Park::pasto = 0;

Park::Park(int x, int y): StreetBlock(x,y)
{
	if(!pasto)
	{
		pasto = loadTexture("tex/Grass_128HV.bmp");
	}
}

void Park::doDraw()
{

	glEnable(GL_TEXTURE_2D);
		
	glPushMatrix();
	
		
		glTranslatef(x, y, 0);
		
		drawVereda();

		glBindTexture( GL_TEXTURE_2D, pasto);
		
		float color[4] = {0.0f, 0.4f, 0.0f, 1.0f};
		float negro[4] = {0.0f, 0.0f, 0.0f, 0.0f};
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, color);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, negro);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0);
		glColor3fv(color);

		glNormal3f(0, 0, 1);
		int paso = 1;
		for(int j=10;j<90;j+=paso)
		{
			glBegin(GL_QUAD_STRIP);
				for(int i=10;i<=90;i+=paso)
				{
					glTexCoord2f(((float)i)/5,((float)(j+paso))/5); glVertex3f(i, j+paso, ALTO_CORDON );
					glTexCoord2f(((float)i)/5,((float)j)/5); glVertex3f(i, j, ALTO_CORDON );
				}
			glEnd();
		}
		
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);


}


Park::~Park()
{
}

void Park::createChildren()
{
	numChildren = 0;
	children = NULL;
}

