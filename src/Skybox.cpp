#include "Skybox.h"
#include "GL/glut.h"

/// Tendria que incluir glext.h pero en vc 6.0 no esta!!!
#define GL_CLAMP_TO_EDGE 0x812F


Skybox::Skybox(PointOfView * pov)
{
	
	_daybox[0] = loadTexture("dia/skyrender0001.bmp");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	_daybox[1] = loadTexture("dia/skyrender0002.bmp");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	_daybox[2] = loadTexture("dia/skyrender0003.bmp");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	_daybox[3] = loadTexture("dia/skyrender0004.bmp");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	_daybox[4] = loadTexture("dia/skyrender0005.bmp");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	_daybox[5] = loadTexture("tex/tierra.bmp");

	_nightbox[0] = loadTexture("noche/skyrender0001.bmp");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	_nightbox[1] = loadTexture("noche/skyrender0002.bmp");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	_nightbox[2] = loadTexture("noche/skyrender0003.bmp");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	_nightbox[3] = loadTexture("noche/skyrender0004.bmp");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	_nightbox[4] = loadTexture("noche/skyrender0005.bmp");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	_nightbox[5] = _daybox[5];
	
	_skybox = _daybox;
	this->pov = pov;
}

Skybox::~Skybox()
{
}

void Skybox::predraw()
{
    glPushMatrix();

    // Reset and transform the matrix.
        glLoadIdentity();
        
        if(pov->upZ > 0)
        {
	        gluLookAt(
	            0,0.3,0,
	            0,0,0,
	            0,0,1);
	        glRotatef(pov->rotation, 0, 0, 1);
        } else {
	        gluLookAt(
	            0,0,0.3,
	            0,0,0,
	            0,1,0);
	        glRotatef(pov->rotation, 0, 0, 1);
        }
        glScalef(2,2,2);
        glTranslatef(0,0,0.2);
}

void Skybox::postdraw()
{
	glPopMatrix();
}


void Skybox::doDraw()
{
	
	// Store the current matrix

	    // Enable/Disable features
	    glPushAttrib(GL_ENABLE_BIT);
	    glDisable(GL_DEPTH_TEST);
	    glDisable(GL_LIGHTING);
	    glDisable(GL_BLEND);
	    glEnable(GL_TEXTURE_2D);
	    glDisable(GL_CULL_FACE);

	    // Just in case we set all vertices to white.
	    glColor4f(1,1,1,1);

		float r = 1.0f; // If you have border issues change this to 1.005f

		
			// I
			glBindTexture(GL_TEXTURE_2D,_skybox[3]);
	    	glBegin(GL_QUAD_STRIP);	
	    		glTexCoord2f(0, 1); glVertex3f(-r ,r,r);
	    		glTexCoord2f(0,  0); glVertex3f(-r,r,-r);
	    		glTexCoord2f(1,  1); glVertex3f(-r,-r,r); 
	    		glTexCoord2f(1, 0); glVertex3f(-r ,-r,-r);
	    	glEnd();

	    	// Adelante
			glBindTexture(GL_TEXTURE_2D,_skybox[4]);
	    	glBegin(GL_QUAD_STRIP);	
	    		glTexCoord2f(0, 1); glVertex3f(-r ,-r,r);
	    		glTexCoord2f(0,  0); glVertex3f(-r,-r,-r);
	    		glTexCoord2f(1,  1); glVertex3f( r,-r,r); 
	    		glTexCoord2f(1, 0); glVertex3f( r ,-r,-r);
	    	glEnd();
	    	
	    	//Derecha
			glBindTexture(GL_TEXTURE_2D,_skybox[0]);
	    	glBegin(GL_QUAD_STRIP);	
	    		glTexCoord2f(0, 1); glVertex3f(r ,-r,r);
	    		glTexCoord2f(0,  0); glVertex3f(r,-r,-r);
	    		glTexCoord2f(1,  1); glVertex3f(r,r,r); 
	    		glTexCoord2f(1, 0); glVertex3f(r ,r,-r);
	    	glEnd();
	    	
	    	// Atras
			glBindTexture(GL_TEXTURE_2D,_skybox[1]);
	    	glBegin(GL_QUAD_STRIP);	
	    		glTexCoord2f(1, 1); glVertex3f(-r ,r,r);
	    		glTexCoord2f(1,  0); glVertex3f(-r,r,-r);
	    		glTexCoord2f(0,  1); glVertex3f( r,r,r); 
	    		glTexCoord2f(0, 0); glVertex3f( r ,r,-r);
	    	glEnd();
	     	     
	    	// Piso
			glBindTexture(GL_TEXTURE_2D,_skybox[5]);
	    	glBegin(GL_QUAD_STRIP);	
	    		glTexCoord2f(20, 20); glVertex3f(-r ,r,-r);
	    		glTexCoord2f(20,  0); glVertex3f(-r,-r,-r);
	    		glTexCoord2f(0,  20); glVertex3f( r,r,-r); 
	    		glTexCoord2f(0, 0); glVertex3f( r ,-r,-r);
	    	glEnd();
	    
	    	// Restore enable bits and matrix
	    glPopAttrib();
}

void Skybox::setDay()
{
	_skybox = _daybox;
	glNewList(dl_handle, GL_COMPILE);
		doDraw();
	glEndList();
}

void Skybox::setNight()
{
	_skybox = _nightbox;
	glNewList(dl_handle, GL_COMPILE);
		doDraw();
	glEndList();	
}

