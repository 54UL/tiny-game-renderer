#pragma once
#include <glm.hpp>
#include <vector>

#include "modelParser.h"


//Esta clase abstrae el concepto de modelo en archivo, ya que pueden ser modelos 3d de los siguientes formatos: .obj, .3ds,.fbx etc



typedef struct
{
	glm::vec3 Vertex;
	glm::vec2 TextureCoord;
	glm::vec3 VertexNormal;
	
}VertexSpec;                    //vertex layaout  in gl memory



//Raw Model definition, this is not yet ready to be rendererd

typedef class modelFormat 
{
public:
	modelFormat();
	~modelFormat();

	//RAW DATA

	std::vector<glm::vec3> Vertex;
	std::vector<glm::vec3> VertexNormal;
	std::vector<glm::vec2> TextureCoords;
	// x = vertex indice, y = texture corrd indice, z= vertex normal indice
	std::vector<glm::ivec3> FaceIndices; 

	//Functions
	VertexSpec * convertToVertexSpecArray(); // Just convert this data to the standard structure for gl
	glm::vec3  * Vertex_c_array();
	glm::vec3  * VertexNormal_c_array();
	glm::vec3  * TextureCoords_c_array();

private:
	//RAW POINTERS TO SAVE THIS SHIT IN A BINARY OR DO WHATEVER YOU WANT
	VertexSpec     *m_RAW_MESH;
	unsigned int   *m_VERTEX_INDICES;
	glm::vec3      *m_vertex;
	glm::vec2      *m_texCoords;
	glm::vec3      *m_vertexNormals;
	glm::ivec3     *m_FaceIndices;
};

