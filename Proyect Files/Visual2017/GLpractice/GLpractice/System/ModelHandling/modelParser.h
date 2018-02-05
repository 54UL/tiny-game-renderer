#pragma once

#include "modelFormat.h"

#include <glm.hpp>
#include <vector>

	//HACER UN TEMPLTE CON EL MODEL FORMAT
	typedef  enum { OBJ, MAX3DS, FBX }MODEL_FORMAT;
	//OBJ  format
	typedef enum MODEL_FEATURES { none, vertex, vertexNormal, textureCoord };//This could apply to any 3d model



class modelParser 
{
public:
	modelParser();
	~modelParser();

	static void
     OpenModel
	 (const char  * fname,  MODEL_FORMAT FORMAT,class  modelFormat * container,bool DEBUG_INFO);
};

