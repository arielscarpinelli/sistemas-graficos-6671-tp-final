#include "Building.h"

int Building::ventanas[CANTIDAD_TEXTURAS_EDIFICIOS][3];
int Building::puertas[CANTIDAD_TEXTURAS_EDIFICIOS][3];
bool Building::loaded = false;

#define ALTO_CORDON 0.25

Building::Building(int x, int y, int rotation, int alto): x(x), y(y), rotation(rotation), alto(alto)
{
	if(!loaded)
	{
		ventanas[0][0] = loadTexture("tex/Build18win.bmp");
		ventanas[0][1] = 1; // Repeticiones en ancho
		ventanas[0][2] = 5; // Alto en metros
		
		puertas[0][0] = loadTexture("tex/combdoor1_128.bmp");
		puertas[0][1] = 3; // Ancho en metros
		puertas[0][2] = 3; // Alto en metros
	
		ventanas[1][0] = loadTexture("tex/combeige128.bmp");
		ventanas[1][1] = 1; // Repeticiones en ancho
		ventanas[1][2] = 5; // Alto en metros
		
		puertas[1][0] = loadTexture("tex/bellisimo256128.bmp");
		puertas[1][1] = 7; // Ancho en metros
		puertas[1][2] = 3; // Alto en metros
				
		ventanas[2][0] = loadTexture("tex/Build4win1.bmp");
		ventanas[2][1] = 3; // Repeticiones en ancho
		ventanas[2][2] = 2; // Alto en metros
	
		puertas[2][0] = loadTexture("tex/iltaywppd256128.bmp");
		puertas[2][1] = 10; // Ancho en metros
		puertas[2][2] = 3; // Alto en metros
	
		ventanas[3][0] = loadTexture("tex/off9_128.bmp");
		ventanas[3][1] = 1; // Repeticiones en ancho
		ventanas[3][2] = 5; // Alto en metros
	
		puertas[3][0] = loadTexture("tex/ind_italdeli128.bmp");
		puertas[3][1] = 7; // Ancho en metros
		puertas[3][2] = 3; // Alto en metros
		
		ventanas[4][0] = loadTexture("tex/Storeroom3.bmp");
		ventanas[4][1] = 2; // Repeticiones en ancho
		ventanas[4][2] = 2; // Alto en metros
	
		puertas[4][0] = loadTexture("tex/shopdoor2_64.bmp");
		puertas[4][1] = 3; // Ancho en metros
		puertas[4][2] = 3; // Alto en metros
		
		loaded = true;
	}
	
	Point2D v(x-5,y-5);	
	boundingBox.addVertex(v);
	
	v.setXY(x-5, y+5);
	boundingBox.addVertex(v);
	
	v.setXY(x+5, y-5);
	boundingBox.addVertex(v);

	v.setXY(x+5, y+5);
	boundingBox.addVertex(v);
	
	cullable = true;
}

Building::~Building()
{
}

void Building::draw()
{
	if(!cull())
		doDraw();
}

void Building::init()
{
	
}

void Building::doDraw()
{
	int *puerta = puertas[alto % CANTIDAD_TEXTURAS_EDIFICIOS];
	int *textura = ventanas[alto % CANTIDAD_TEXTURAS_EDIFICIOS];
	int baseVentana;
	float altoTex;
	
	float i;
	int paso = 1;

	glEnable(GL_TEXTURE_2D);
			
	glPushMatrix();
	
	glTranslatef(x, y, 0);
	glRotatef(rotation, 0,0, 1);

	if(puerta[0] != 0) // Si tiene puerta
	{
		glBindTexture( GL_TEXTURE_2D, textura[0]);

		baseVentana = puerta[2];
		altoTex = puerta[2];
		float anchoPuerta = ((float)puerta[1]) / 2;
				
		glBegin(GL_QUAD_STRIP);

				// Normal para la izq.
				glNormal3f(-1, 0, 0);
				for(i=5; i>=-5; i-=paso)
				{
					glTexCoord2f(0, 1); glVertex3f(-5, i, altoTex);
					glTexCoord2f(0, 0); glVertex3f(-5, i, ALTO_CORDON);
				}	
				
				// Normal para adelante (abajo)
				glNormal3f(0, -1, 0);
				for(i=-5; i<=-anchoPuerta; i+=paso)
				{
					glTexCoord2f(0, 1); glVertex3f(i,  -5, altoTex);
					glTexCoord2f(0, 0); glVertex3f(i, -5, ALTO_CORDON);
				}
				glTexCoord2f(0, 1); glVertex3f(-anchoPuerta,  -5, altoTex);
				glTexCoord2f(0, 0); glVertex3f(-anchoPuerta, -5, ALTO_CORDON);


		glEnd();	
		
		glBegin(GL_QUAD_STRIP);
				for(i=anchoPuerta; i<=5; i+=paso)
				{
					glTexCoord2f(0, 1); glVertex3f(i,  -5, altoTex);
					glTexCoord2f(0, 0); glVertex3f(i, -5, ALTO_CORDON);
				}
				glTexCoord2f(0, 1); glVertex3f(5,  -5, altoTex);
				glTexCoord2f(0, 0); glVertex3f(5, -5, ALTO_CORDON);
				
				// Normal a la derecha
				glNormal3f(1, 0, 0);
				for(i=-5; i<=5; i+=paso)
				{
					glTexCoord2f(0, 1); glVertex3f(5, i, altoTex);
					glTexCoord2f(0, 0); glVertex3f(5, i, ALTO_CORDON);
				}	

		glEnd();	

		glBegin(GL_QUAD_STRIP);

				// Normal para atras
				glNormal3f(0, 1, 0);
				for(i=-5; i<=5; i+=paso)
				{
					glTexCoord2f(0, 0); glVertex3f(i, 5, ALTO_CORDON);
					glTexCoord2f(0, 1); glVertex3f(i,  5, altoTex);
				}
				glTexCoord2f(0, 0); glVertex3f(5, 5, ALTO_CORDON);
				glTexCoord2f(0, 1); glVertex3f(5,  5, altoTex);
						
		glEnd();	

		glBindTexture( GL_TEXTURE_2D, puerta[0]);

		glBegin(GL_QUAD_STRIP);
		
				glNormal3f(0, -1, 0);
				glTexCoord2f(0, 1); glVertex3f(-anchoPuerta,  -5, altoTex);
				glTexCoord2f(0, 0); glVertex3f(-anchoPuerta, -5, ALTO_CORDON);

				glTexCoord2f(1, 1); glVertex3f(anchoPuerta, -5, altoTex);
				glTexCoord2f(1, 0); glVertex3f(anchoPuerta, -5, ALTO_CORDON);
		glEnd();	
		
		
	} else
		baseVentana = (int)ALTO_CORDON;
	
	glBindTexture( GL_TEXTURE_2D, textura[0]);

	altoTex = ((float)(alto - baseVentana)) / textura[2];
	
	glBegin(GL_QUAD_STRIP);

			// Normal para la izq.
			glNormal3f(-1, 0, 0);
			for(i=5; i>=-5; i-=paso)
			{
				glTexCoord2f(0, altoTex); glVertex3f(-5, i, alto);
				glTexCoord2f(0, 0); glVertex3f(-5, i, baseVentana);
			}	
			
			// Normal para adelante (abajo)
			glNormal3f(0, -1, 0);
			for(i=-5; i<=5; i+=paso)
			{
				glTexCoord2f((float)textura[1] * ((float)(i + 5))* 0.1, altoTex); glVertex3f(i,  -5, alto);
				glTexCoord2f((float)textura[1] * ((float)(i + 5)) * 0.1, 0); glVertex3f(i, -5, baseVentana);
			}

			// Normal a la derecha
			glNormal3f(1, 0, 0);
			for(i=-5; i<=5; i+=paso)
			{
				glTexCoord2f(textura[1], altoTex); glVertex3f(5, i, alto);
				glTexCoord2f(textura[1], 0); glVertex3f(5, i, baseVentana);
			}	
			
			// Normal para atras (arriba)
			glNormal3f(0, 1, 0);
			for(i=-5; i<=5; i+=paso)
			{
				glTexCoord2f((float)textura[1] * ((float)(i + 5))* 0.1, altoTex); glVertex3f(i,  5, alto);
				glTexCoord2f((float)textura[1] * ((float)(i + 5)) * 0.1, 0); glVertex3f(i, 5, baseVentana);
			}

	glEnd();	

	// La tapa
	
	glBegin(GL_QUADS);
		
		glNormal3f(0, 0, 1);
		glVertex3f(-5, 5, alto);
		glVertex3f(-5, -5, alto);
		glVertex3f(5, -5, alto);
		glVertex3f(5, 5, alto);

	glEnd();

	glPopMatrix();
}

