#pragma once

#include "modelFormat.h"
#include <glm.hpp>
#include <vector>



	//HACER UN TEMPLTE CON EL MODEL FORMAT
	typedef  enum { OBJ, MAX3DS, FBX }MODEL_FORMAT;
	//Model contents
	typedef enum MODEL_FEATURES { none, vertex, vertexNormal, textureCoord };//This could apply to any 3d model

class modelParser 
{
public:
	modelParser();
	~modelParser();

	 void
     OpenModel
	 (const char  * fname,  MODEL_FORMAT FORMAT,class  modelFormat * container);

private:

	// OBJ
	//especificamente para el obj loader, deberia ser modular para asi tener un sistema de importadores e exportadores
	  int findSpace(std::string * str, unsigned int pos, bool FindFirstorLast);
	  
	  glm::ivec3 getParsedFaceIndex(std::string & vertIndexstr);
	  glm::vec3  getParsedVector3(std::string & IslandStr);
	  glm::vec2  getParsedVector2(std::string & IslandStr);
	// END OBJ


};

