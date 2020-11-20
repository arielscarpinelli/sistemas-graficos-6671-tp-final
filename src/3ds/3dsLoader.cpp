/************************************************************
*	APRON TUTORIAL PRESENTED BY MORROWLAND					*
*************************************************************
*	Author					: Ronny Andr� Reierstad			*
*	Web Page				: www.morrowland.com			*
*	E-Mail					: apron@morrowland.com			*
************************************************************/

#include "3dsLoader.h"



/////////////////////////////////////////////////////////////////////////////////////////////////
//										 INIT 3DS
/////////////////////////////////////////////////////////////////////////////////////////////////
bool C3dsLoader::Init_3ds(char* path, char* filename)
{
	if(!mLoad3ds.Import3DS(&m3DModel, filename)) {
		printf("failed to load 3ds model %s\n", filename);
		return false;
	}
	
	for(int i = 0; i < m3DModel.numOfMaterials; i++)				
	{
		if(strlen(m3DModel.pMaterials[i].strFile) > 0)				
		{
			if(!Texture_3ds(TextureArray3ds, path, m3DModel.pMaterials[i].strFile, i)) {
				return false;
			}
		}
		
		m3DModel.pMaterials[i].texureId = i;	
	}
	return true;
}


/////////////////////////////////////////////////////////////////////////////////////////////////
//										RENDER 3DS
/////////////////////////////////////////////////////////////////////////////////////////////////
void C3dsLoader::Render_3ds()
{
	
	for(int i = 0; i < m3DModel.numOfObjects; i++)
	{
		
		if(m3DModel.pObject.size() <= 0) break;						
		
		t3DObject *pObject = &m3DModel.pObject[i];					
		
		if(pObject->bHasTexture)									
		{									
			glEnable(GL_TEXTURE_2D);								
			
			glColor3ub(255, 255, 255);								
			
			glBindTexture(GL_TEXTURE_2D, TextureArray3ds[pObject->materialID]); 
		} 
		else 
		{
			glDisable(GL_TEXTURE_2D);								
			
			glColor3ub(255, 255, 255);								
		}
		
		glBegin(GL_TRIANGLES);										
		
		for(int j = 0; j < pObject->numOfFaces; j++)
		{
			
			for(int whichVertex = 0; whichVertex < 3; whichVertex++)
			{
				int index = pObject->pFaces[j].vertIndex[whichVertex];
				
				glNormal3f(pObject->pNormals[ index ].x, pObject->pNormals[ index ].y, pObject->pNormals[ index ].z);
				
				if(pObject->bHasTexture) {
					
					if(pObject->pTexVerts) {
						glTexCoord2f(pObject->pTexVerts[ index ].x, pObject->pTexVerts[ index ].y);
					}
				} else {
					
					if(m3DModel.pMaterials.size() < pObject->materialID) 
					{
						BYTE *pColor = m3DModel.pMaterials[pObject->materialID].color;
						
						glColor3ub(pColor[0], pColor[1], pColor[2]);
					}
				}
				glVertex3f(pObject->pVerts[ index ].x, pObject->pVerts[ index ].y, pObject->pVerts[ index ].z);
			}
		}
		
		glEnd();
	}
	
}


/////////////////////////////////////////////////////////////////////////////////////////////////
//										TEXTURE 3DS			jpeg or bmp
/////////////////////////////////////////////////////////////////////////////////////////////////
#include "../Model.h"
bool C3dsLoader::Texture_3ds(UINT textureArray[], LPSTR strPath, LPSTR strFileName, int ID)
{
	char path[255];
	strcpy(path, strPath);
	strcat(path, strFileName);
	char * ext = strstr(path, ".") + 1;
	strcpy(ext, "bmp");
	textureArray[ID] = loadTexture(path);
	return textureArray[ID];
}


/////////////////////////////////////////////////////////////////////////////////////////////////
//										UNLOAD 3DS
/////////////////////////////////////////////////////////////////////////////////////////////////
void C3dsLoader::Unload_3ds()
{
	for(int i = 0; i < m3DModel.numOfObjects; i++)	
	{
		delete [] m3DModel.pObject[i].pFaces;
		delete [] m3DModel.pObject[i].pNormals;
		delete [] m3DModel.pObject[i].pVerts;
		delete [] m3DModel.pObject[i].pTexVerts;
	}
}












