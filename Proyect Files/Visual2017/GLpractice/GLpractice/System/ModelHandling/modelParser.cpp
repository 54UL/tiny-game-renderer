#include "modelParser.h"


//STD INCLUDES
#include <fstream> // from da hell std
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


modelParser::modelParser()
{

}


modelParser::~modelParser()
{

}

void
modelParser::OpenModel(const char  * fname,  MODEL_FORMAT FORMAT, modelFormat * container)
{
	//variables
	char  buffer[64];
	std::string lineHeader;
	unsigned int m_CurrentContentFeatures=0;

	std::ifstream DOC(fname, std::fstream::binary);

	if (!DOC.is_open())
	{
		std::cout << "Error opening the 3d .obj model file : " << fname << std::endl;
		return;
	}


	// una vez abierto el archivo lo procesamos segun su formato
	switch (FORMAT)
	{

	
    //OBJ PARSER
	case MODEL_FORMAT::OBJ:

		//HACER MODULAR ESTE PEDO PARA NO TENER MUCHO CODIGO EN EL SWITCH

		//aqui se debera de hacer un primer pass para verificar con que datos va a trabajar el parser
		
		while (1)
		{
			DOC.getline(buffer, 64);

			if (DOC.eof())
			{
				break;
			}
				
			std::string headerL (buffer);

			if (headerL.compare(0, 2, "v ") == 0)
			{
				m_CurrentContentFeatures = m_CurrentContentFeatures | MODEL_FEATURES::vertex;
				continue;
			}
			else if (headerL.compare(0, 2, "vt") == 0)
			{
				m_CurrentContentFeatures = m_CurrentContentFeatures | MODEL_FEATURES::textureCoord;
				continue;
			}
			else if (headerL.compare(0, 2, "vn") == 0)
			{
				m_CurrentContentFeatures = m_CurrentContentFeatures | MODEL_FEATURES::vertexNormal;
			}
		    //exponer todos los errores en busca de errores en el formato
		}


		if (m_CurrentContentFeatures & MODEL_FEATURES::vertex != MODEL_FEATURES::vertex)
		{			
			std::cout << "Invalid OBJ format" << std::endl;
			return;
		}
		
		
		//Procesamos los respectivos datos...
		DOC.clear();
	  	DOC.seekg(0,DOC.beg);

		while (1)
		{
			DOC.getline(buffer, 64);

			if (DOC.eof())
				break;

			std::string Line(buffer);

			if (Line.compare(0, 2, "v ") == 0)
				container->Vertex.push_back(this->getParsedVector3(Line));
			else if (Line.compare(0, 2, "vt") == 0)
				container->TextureCoords.push_back(this->getParsedVector2(Line));
			else if (Line.compare(0, 2, "vn") == 0)
				container->VertexNormal.push_back(this->getParsedVector3(Line));
			else if (Line.compare(0, 2, "f ") == 0) 
			{
				//las caras deben de ser triangulares
				// container->FaceIndices =
				int vertice1a = findSpace(&Line, 1,false);
				int vertice1b = Line.find(" ", vertice1a+1);
				std::string isla1 = Line.substr(vertice1a, vertice1b - vertice1a);
				container->FaceIndices.push_back(getParsedFaceIndex(isla1));
				int vertice2a = findSpace(&Line, vertice1b,false);
				int vertice2b = Line.find(" ", vertice2a+1);
				std::string isla2 = Line.substr(vertice2a, vertice2b - vertice2a);
				container->FaceIndices.push_back(getParsedFaceIndex(isla2));
				int vertice3a = findSpace(&Line, vertice2b, false);
				int vertice3b = Line.find("\r", vertice3a+1);
				std::string isla3 = Line.substr(vertice3a, vertice3b - vertice3a);
				container->FaceIndices.push_back(getParsedFaceIndex(isla3));
			}
			else
			{
			//	std::cout << "Not defined by the parser" << std::endl;
			}
		}
	break;

	//3DS PARSER
	case MODEL_FORMAT::MAX3DS:
	break;

	//FBX PARSER
	case MODEL_FORMAT::FBX:
	break;

	}
	DOC.close();
}

//si es verdadero retorna encuanto encuentre un espacio, si no se supone que hay un espacio actual y encuanto encuentre otra cosa que no sea espacio
int modelParser::findSpace(std::string * str, unsigned int pos, bool FindFirstorLast)
{
	std::string::iterator strIterator = str->begin();
	strIterator += pos;
	unsigned int count = 0 + pos;
	while (strIterator != str->end())
	{
		if (FindFirstorLast ? *strIterator == ' ' : *std::next(strIterator) != ' ')
			return count;
		count++;
		strIterator++;
	}
	return -1;
}

glm::ivec3 modelParser::getParsedFaceIndex(std::string & vertIndexstr)
{
	glm::vec3 tmpvec3;
	unsigned int pos1 = vertIndexstr.find("/", 0);
	std::string xd1 = vertIndexstr.substr(0, pos1).c_str();
	tmpvec3.x = atoi(xd1.c_str());

	if (vertIndexstr.compare(pos1, 2, "//") == 0)
	{
		tmpvec3.y = 0;
		std::string xd = vertIndexstr.substr(pos1 + 2).c_str();
		tmpvec3.z = atoi(xd.c_str());
	}
	else
	{
		std::cout << "texture coords indexing not implemented" << std::endl;
	}

	return tmpvec3;
}

glm::vec3 modelParser::getParsedVector3(std::string & IslandStr)
{
	int vx1 = findSpace(&IslandStr, 1, false);
	int vx2 = IslandStr.find(' ', vx1 + 1);
	std::string vx = IslandStr.substr(vx1 + 1, (vx2 - vx1));
	int vy2 = findSpace(&IslandStr, vx2, true);
	std::string vy = IslandStr.substr(vx2 + 1, vy2 - vx1);
	int vz1 = findSpace(&IslandStr, vy2 + 1, true);
	std::string vz = IslandStr.substr(vz1 + 1);
	return glm::vec3(atof(vx.c_str()), atof(vy.c_str()), atof(vz.c_str()));
}

glm::vec2 modelParser::getParsedVector2(std::string & IslandStr)
{
	int vx1 = findSpace(&IslandStr, 1, false);
	int vx2 = IslandStr.find(' ', vx1 + 1);
	std::string vx = IslandStr.substr(vx1 + 1, (vx2 - vx1));
	int vy2 = findSpace(&IslandStr, vx2, true);
	std::string vy = IslandStr.substr(vx2 + 1);
	return glm::vec2(atof(vx.c_str()), atof(vy.c_str()));
}
