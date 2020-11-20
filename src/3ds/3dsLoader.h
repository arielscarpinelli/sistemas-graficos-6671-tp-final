
#ifndef _3DSLOADER_H
#define _3DSLOADER_H

#include "Main.h"
#include "3ds.h"


//////////////////////////////////////
//The 3dsLoader Class
//////////////////////////////////////
class C3dsLoader
{
	public:
		CLoad3DS mLoad3ds;						
		UINT TextureArray3ds[MAXTEXTURE];	
		t3DModel m3DModel;	

		bool Init_3ds(char* path, char* filename);
		void Render_3ds();
		bool Texture_3ds(UINT textureArray[], LPSTR path, LPSTR strFileName, int ID);
		void Unload_3ds();
};


#endif

//Ronny Andr� Reierstad
//www.morrowland.com
//apron@morrowland.com
