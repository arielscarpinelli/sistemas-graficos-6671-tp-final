#ifndef _MAIN_H
#define _MAIN_H


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef __APPLE__
	#include <GL/gl.h>
	#include <GL/glu.h>
#else
	#define GL_SILENCE_DEPRECATION
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#endif	

#include <fstream>
#include <vector>									
using namespace std;


#define MAXTEXTURE 100

typedef unsigned char BYTE;
typedef unsigned int UINT;
typedef char CHAR;
typedef CHAR *LPSTR;

//////////////////////////////////////
//The tVector3 Struct
//////////////////////////////////////
typedef struct tVector3					// expanded 3D vector struct
{			
	tVector3() {}	// constructor
	tVector3 (float new_x, float new_y, float new_z) // initialize constructor	 
	{x = new_x; y = new_y; z = new_z;}
	// overload + operator so that we easier can add vectors
	tVector3 operator+(tVector3 vVector) {return tVector3(vVector.x+x, vVector.y+y, vVector.z+z);}
	// overload - operator that we easier can subtract vectors
	tVector3 operator-(tVector3 vVector) {return tVector3(x-vVector.x, y-vVector.y, z-vVector.z);}
	// overload * operator that we easier can multiply by scalars
	tVector3 operator*(float number)	 {return tVector3(x*number, y*number, z*number);}
	// overload / operator that we easier can divide by a scalar
	tVector3 operator/(float number)	 {return tVector3(x/number, y/number, z/number);}
	
	float x, y, z;						// 3D vector coordinates
}tVector3;

//////////////////////////////////////
//The tVector2 Struct
//////////////////////////////////////											
struct tVector2 
{
	float x, y;							// 2D vector coordinates
};


#endif

//Ronny Andr� Reierstad
//www.morrowland.com
//apron@morrowland.com
