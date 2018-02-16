#pragma once

#include <GL\glew.h>
#include <gl\GL.h>
#include "glm.hpp"


//utilities

const int MAX_ENGINE_TEXTURES_PER_MATERIAL = 4;
typedef enum {RGB8,RGBA8,RGB32,RGBA32}TEXTURE_FORMAT;
typedef enum {TILING_REPEAT,TILING_CLAMP,FILTER_NEAREST,FILTER_LINEAR}TEXTURE_CONFIG;

//Class
class GLtexture
{
public:
	GLtexture(GLuint CreatedTexturetoAssing);
	GLtexture();
	~GLtexture();
	void LoadTexture(const char * fname);
	void LoadTexture(GLuint CreatedTexturetoAssing);
	void UseTexture();
	void CleanUp();//Erase ALL
	void Clean(GLuint TextureToDelete);
	bool isEmpty() { return m_empty; };

	GLuint returnTextureID() { return m_TextureID[0]; }
	
	GLuint returnTextureID(unsigned short Index) {
		return Index < 4 ? m_TextureID[Index] : -1;
	};

	//To implement
private:
	GLuint  m_TextureID[MAX_ENGINE_TEXTURES_PER_MATERIAL];//fixed size 
	GLuint  m_CurrentTexIndex;
	bool    m_empty;
};

