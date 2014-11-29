
#include <vector>
#include <GL/glut.h>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include "Model.h"
#include "Car.h"
#include "Street.h"
#include "StreetBlock.h"
#include "Skybox.h"
#include "PointOfView.h"
#include "Sun.h"
#include "Wall.h"
#include "Park.h"

#ifndef GL_BGR_EXT
#define GL_BGR_EXT 0x80E0
#endif


using namespace std;

typedef vector< Model* > Models;
Models models;

// Tamaño de la ventana
GLfloat width;
GLfloat height;


// El objeto principal
Car* car;

// La camara actual
PointOfView pov;

Culler culler;

clock_t lastTime;
float fps;

// Para compensar el movimiento el pasaje del tiempo se promedia
#define TIME_LENGTH 10
double promediated[TIME_LENGTH];
int cursor = TIME_LENGTH - 1;

void OnIdle (void)
{
	clock_t newTime = clock();

	cursor = (cursor + 1) % TIME_LENGTH;
	
	double deltaSecs = ((double)(newTime - lastTime)) / CLOCKS_PER_SEC;
	promediated[cursor] = deltaSecs;
    
	double prom = 0;
	for(int i=0;i<TIME_LENGTH;i++)
    	prom += promediated[i];
	
	prom /= TIME_LENGTH;
	
	fps = 1 / prom;
	
	Model* hiter = NULL;
	for(Models::iterator it = models.begin(); it != models.end(); it++)
    {
    	(*it)->time(prom);
    	if(!hiter)
    	{
    		if((*it)->hits(*car))
    			hiter = *it;
    	}
    }
	if(hiter)
		car->hited(hiter);
	
    lastTime = newTime;
}

void Set3DEnv()
{
	glViewport (0, 0, (GLsizei) width, (GLsizei) height); 
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(60.0, (GLfloat) width/(GLfloat) height, 1, 380.0);
    glEnable(GL_LIGHTING);
}

void SetPanel2DEnv()
{
	glViewport (0, 0, (GLsizei) (width/5), (GLsizei) (height/5)); 
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
	gluOrtho2D(0, 380, 380, 0);
    glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
}

void init(void) 
{
	
	srand ( time(NULL) );
	
    glShadeModel (GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE ) ;
    glEnable(GL_COLOR_MATERIAL);
    

    models.push_back(new Skybox(&pov));


    car = new Car();
    models.push_back(car);
    models.push_back(new Sun());
    
 
    models.push_back(new Street());
 
   
    for (int i = 0; i < 3; i++)
    {
    	for (int j = 0; j < 3; j++)
    	{
    	    if(((i ==1) && (j==1)) || ((i == 2) && (j == 1)))
    	    	models.push_back(new Park(20 + i*120, 20 + j*120));
    	    else
    	    	models.push_back(new StreetBlock(20 + i*120, 20 + j*120));
    	}
    }

    models.push_back(new Wall(190,0,0));
    models.push_back(new Wall(0, 190, -90));
    models.push_back(new Wall(380,190,90));
    models.push_back(new Wall(190,380,180));

    for(Models::iterator it = models.begin(); it != models.end(); it++)
    {
    	(*it)->init();
    	(*it)->setCuller(&culler);
    }

    lastTime = clock();
    
}

void close ()
{
    for(Models::iterator it = models.begin(); it != models.end(); it++)
    {
    	delete (*it);
    }
}


void display(void)
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_CULL_FACE);


	Models::iterator it;
	
	///////////////////////////////////////////////////
	// Escena 3D
	Set3DEnv();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	pov.set(car->getX(), car->getY(), car->getRotation());
	
	culler.updateFrustum(pov);
	
    for(it = models.begin(); it != models.end(); it++)
    {
    	(*it)->draw();
    }
	//
	///////////////////////////////////////////////////


    glDisable(GL_CULL_FACE);
	///////////////////////////////////////////////////
	// Panel 2D
	SetPanel2DEnv();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
 
	
	for(it = models.begin(); it != models.end(); it++)
    {
		(*it)->draw2D();
    }
	
	glColor3f(1, 0, 0);
	glRasterPos3f(0, 0, 0.0);
 	char str[30]; 
 	char *ch; 
	sprintf(str, "FPS: %2.0f - Speed : %.f kph", fps, car->getSpeed() * 3.6);

	for(ch= str; *ch; ch++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, (int)*ch);
	}
	
	glutSwapBuffers();
}

void onResize (int w, int h)
{
   	width = w;
   	height = h;
}

void onKeyboard (unsigned char key, int x, int y)
{
	Models::iterator it;
	switch (key) {
      case 0x1b:

         exit (0);
         break;
      
      case 'n': // Modo noche
    	    for(it = models.begin(); it != models.end(); it++)
    	    {
	    		DayChangeable* day = dynamic_cast<DayChangeable*> (*it);
	    		if(day) 
	    		{
	    			day->setNight();
	    		}
    	    }
    	  break;
    	  
      case 'd': // Modo dia
    	    for(it = models.begin(); it != models.end(); it++)
    	    {
	    		DayChangeable* day = dynamic_cast<DayChangeable*> (*it);
	    		if(day) day->setDay();
    	    }
    	    break;

      case 'z':
    	  pov.rotate(-1);
    	  break;
    	  
      case 'x':
    	  pov.rotate(1);
    	  break;
      case '1': // Persecusion
    	  pov.setBack();
    	  break;
      
      case '2': // Adentro
    	  pov.setInside();
    	  break;
      
      case '3': // Arriba
    	  pov.setUp();
    	  break;
   }
}

void onKeyboardUp (unsigned char key, int x, int y)
{
   switch (key) {
	   case 'z':
	   case 'x':
	 	  pov.rotate(0);
	 	  break;
   }
}
void onSpecialKeyboardUp(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_LEFT:
		case GLUT_KEY_RIGHT:    	  
    	  car->wheel(0);
    	  break;
    	  
		case GLUT_KEY_UP:    	  
		case GLUT_KEY_DOWN:    	  
    	  car->accelerate(0);
    	  break;
         
   }
}

void onSpecialKeyboard(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_LEFT:
    	  car->wheel(-1);
    	  break;
    	  
		case GLUT_KEY_RIGHT:    	  
    	  car->wheel(1);
    	  break;
    	  
		case GLUT_KEY_UP:    	  
    	  car->accelerate(1);
    	  break;

		case GLUT_KEY_DOWN:    	  
    	  car->accelerate(-1);
    	  break;
         
   }
}
int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

   glutGameModeString( "800x600:32@60" );
   glutEnterGameMode();

/*   glutInitWindowSize (800, 600); 
   glutInitWindowPosition (0, 0);
	 
   glutCreateWindow (argv[0]);
*/   
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(onResize);
   glutKeyboardFunc(onKeyboard);
   glutKeyboardUpFunc(onKeyboardUp);
   glutSpecialFunc(onSpecialKeyboard);
   glutSpecialUpFunc(onSpecialKeyboardUp);
   glutIgnoreKeyRepeat(1);
   glutIdleFunc(OnIdle);
   glutMainLoop();
   close ();
   return 0;
}

GLuint loadTexture( const char * filename)
{
    GLuint texture;
    int width, height, size;
    char * data;
    FILE * img;

    // Levanta un BMP
	
	printf("Cargando textura: %s\n", filename);
    img = fopen( filename, "rb" );
    if ( img == NULL ) return 0;

	fseek(img,18,SEEK_SET);
	fread(&width,4,1,img);
	fread(&height,4,1,img);
	fseek(img,0,SEEK_END);
	size = ftell(img) - 54;

	data = (char*)malloc(size);

	fseek(img,54,SEEK_SET);
	fread(data,size,1,img);

	fclose(img);

	glGenTextures( 1, &texture );

	glBindTexture(GL_TEXTURE_2D, texture);

    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                     GL_LINEAR_MIPMAP_LINEAR );

    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                     GL_REPEAT);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
                     GL_REPEAT);

   
	gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height,
                       GL_BGR_EXT, GL_UNSIGNED_BYTE, data );

    free( data );

    return texture;
}
