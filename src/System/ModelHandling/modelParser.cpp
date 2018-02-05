#include "modelParser.h"

//NOTA: ESTE CODIGO ESTA SUPER MAL ELABORADO Y SE PUEDE NOTAR EL HARDCODING QUE SE HIZO, TO DO... : codigo repetido hacerlo
//funciones, y hacer generica la funcion de "find space"


//STD INCLUDES
#include <fstream> // from da hell std
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "ArrayList.h"



#define toDigit(c) (c-'0')



//pos means the character where is going to start the search
static int findSpace(std::string * str, unsigned int pos, bool FindFirstorLast)
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


static glm::ivec3 getParsedFaceIndex(std::string & vertIndexstr)
{
	
	glm::ivec3 tmpvec = glm::ivec3();

	short int pos = vertIndexstr.find("/", 0);
	std::string VertexIndex = vertIndexstr.substr(0, pos);
	tmpvec.x = atoi(VertexIndex.c_str());
	
	short int pos2 = vertIndexstr.find("/", pos + 1);
	std::string TextureCoordIndex = vertIndexstr.substr(pos + 1, pos2 - pos);
	tmpvec.y = atoi(TextureCoordIndex.c_str());
    
	std::string VertexNormalIndex = vertIndexstr.substr(pos2+1);
	tmpvec.z = atoi(VertexNormalIndex.c_str());

	return tmpvec;

}

modelParser::modelParser()
{

}


modelParser::~modelParser()
{

}

void
modelParser::OpenModel(const char  * fname,  MODEL_FORMAT FORMAT, modelFormat * container, bool DEBUG_INFO)
{
	//variables
	char  buffer[64];
	std::string lineHeader;
	unsigned int m_CurrentContentFeatures=0;

	std::ifstream DOC(fname, std::fstream::binary);

	if (!DOC.is_open())
	{
		std::cout << "Error opening the 3d model file : " << fname << std::endl;
		return;
	}


	// una vez abierto el archivo lo procesamos segun su formato
	switch (FORMAT)
	{

	
    //OBJ PARSER
	case MODEL_FORMAT::OBJ:

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
			}
			else if (headerL.compare(0, 2, "vt") == 0)
			{
				m_CurrentContentFeatures = m_CurrentContentFeatures | MODEL_FEATURES::textureCoord;
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

			if (Line.compare(0, 2, "v ") == 0 )
			{
				
				int vx1 = findSpace(&Line, 1, false);
				int vx2 = Line.find(' ', vx1 + 1);
				std::string vx = Line.substr(vx1 + 1, (vx2 - vx1));
				int vy2 = findSpace(&Line, vx2, true);
				std::string vy = Line.substr(vx2 + 1, vy2 - vx1);
				int vz1 = findSpace(&Line, vy2 + 1, true);
				std::string vz = Line.substr(vz1 + 1);

				container->Vertex.push_back(glm::vec3(atof(vx.c_str()), atof(vy.c_str()), atof(vz.c_str())));
			//	std::cout << "Vertex : " << atof(vx.c_str()) << " " << atof(vy.c_str()) << " " << atof(vz.c_str()) << std::endl;
			}
			else if (Line.compare(0, 2, "vt") == 0)
			{
				int vx1 = findSpace(&Line, 1, false);
				int vx2 = Line.find(' ', vx1 + 1);
				std::string vx = Line.substr(vx1 + 1, (vx2 - vx1));
				int vy2 = findSpace(&Line, vx2, true);
				std::string vy = Line.substr(vx2 + 1);
				container->TextureCoords.push_back(glm::vec2(atof(vx.c_str()), atof(vy.c_str()) ));

				//std::cout << "Tex Coord : " << atof(vx.c_str()) << " " << atof(vy.c_str()) << std::endl;
			}
			else if (Line.compare(0, 2, "vn") == 0)
			{
				int vx1 = findSpace(&Line, 1, false);
				int vx2 = Line.find(' ', vx1 + 1);
				std::string vx = Line.substr(vx1 + 1, (vx2 - vx1));
				int vy2 = findSpace(&Line, vx2, true);
				std::string vy = Line.substr(vx2 + 1, vy2 - vx1);
				int vz1 = findSpace(&Line, vy2 + 1, true);
				std::string vz = Line.substr(vz1 + 1);
				container->VertexNormal.push_back(glm::vec3(atof(vx.c_str()), atof(vy.c_str()), atof(vz.c_str())));
				//std::cout << "Vertex Normal : " << atof(vx.c_str()) << " " << atof(vy.c_str()) << " " << atof(vz.c_str()) << std::endl;
			}
			else if (Line.compare(0, 2, "f ") == 0) // LECTURA DE CARAS, ESTA PARTE ES LA COMPLICADA HIJOSU CHINGADA MADRE
			{
				//ESTE ES EL CASO EN DODE LA CARA ESTA COMPUESTA POR INDICE DE VERTICE/TEXTURA/NORMAL(esta madre va explotar si no se tiene el formato adecuado)
				if (m_CurrentContentFeatures == MODEL_FEATURES::textureCoord | MODEL_FEATURES::vertexNormal)
				{
					//buscamos las islas de informacion 
					int vx1 = findSpace(&Line, 1, false);
					int vx2 = Line.find(' ', vx1 + 1);
					std::string vx = Line.substr(vx1 + 1, (vx2 - vx1) - 1);
					int vy2 = findSpace(&Line, vx2, true);
					std::string vy = Line.substr(vx2 + 1, (vy2 - vx1) - 1);
					int vz1 = findSpace(&Line, vy2 + 1, true);
					int vz2 = Line.find(' ', vz1 + 1);
					std::string vz = Line.substr(vz1 + 1, (vz2 - vz1) - 1);
					std::string vw = Line.substr(vz2 + 1);
					//Separamos los respectivos indices
					//Analisis del formato de cadena x/x/x
					glm::ivec3 Vertexx = getParsedFaceIndex(vx);
					glm::ivec3 Vertexy = getParsedFaceIndex(vy);
					glm::ivec3 Vertexz = getParsedFaceIndex(vz);
					glm::ivec3 Vertexw = getParsedFaceIndex(vw);
					container->FaceIndices.push_back(Vertexx);
					container->FaceIndices.push_back(Vertexy);
					container->FaceIndices.push_back(Vertexz);
					container->FaceIndices.push_back(Vertexw);
					//	std::cout << Vertexx.x << "/" << Vertexx.y << "/" << Vertexx.z << " "
					//		<< Vertexy.x << "/" << Vertexy.y << "/" << Vertexy.z << " "
					//		<< Vertexz.x << "/" << Vertexz.y << "/" << Vertexz.z << " "
					//		<< Vertexw.x << "/" << Vertexw.y << "/" << Vertexw.z << std::endl;

				}
				else  if (m_CurrentContentFeatures == MODEL_FEATURES::textureCoord)
				{
					std::cout << "no implementado" << std::endl;
				}
				else if (m_CurrentContentFeatures == MODEL_FEATURES::vertexNormal)
				{
					std::cout << "no implementado"<<std::endl;
				}
				else
					std::cout << "no implementado" << std::endl;

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
