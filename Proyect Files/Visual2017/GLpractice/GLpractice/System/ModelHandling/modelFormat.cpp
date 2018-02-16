#include "modelFormat.h"
#include <iostream>


modelFormat::modelFormat()
{

}


modelFormat::~modelFormat()
{
	this->CleanUp();
}

VertexSpec * modelFormat::convertToVertexSpecArray()
{
	return nullptr;
}


//indexed vertices
glm::vec3 * modelFormat::Vertex_c_array()
{
	if (m_vertex == NULL)
	{
		//Creeamos el buffer
		m_vertex = new glm::vec3[Vertex.size()];
		//Asiganamos los valores
		for (int i = 0; i < Vertex.size(); i++)
		{
			m_vertex[i] = Vertex[i];
		}
		return m_vertex;
	}
	else
		return nullptr;

}


//los normales se necesitan hacer en un arreglo plano
glm::vec3 * modelFormat::VertexNormal_c_array()
{
	if (m_vertexNormals == NULL && !VertexNormal.empty())
	{
		m_vertexNormals = new glm::vec3[FaceIndices.size()];
		
		for (int i = 0; i < FaceIndices.size(); i++)
		{
			m_vertexNormals[i] = VertexNormal[ FaceIndices[i].z-1 ];
		}
		return m_vertexNormals;
	}
	else
		return nullptr;
}


//las tex coords se necesitan hacer en un arreglo plano
glm::vec3 * modelFormat::TextureCoords_c_array()
{
	return nullptr;
}

//indices unicamente de los vertices(los demas indices no son necesarios)
unsigned int * modelFormat::VertexIndices_c_array()
{
	if (m_VERTEX_INDICES == NULL)
	{
		//Creeamos el buffer
		m_VERTEX_INDICES = new unsigned int[FaceIndices.size()];
		//Asiganamos los valores
		for (int i = 0; i < FaceIndices.size(); i++)
		{
			m_VERTEX_INDICES[i] = FaceIndices[i].x-1;
		}
		return m_VERTEX_INDICES;
	}
	else
		return nullptr;
}

void modelFormat::CleanUp()
{
	if (m_vertex != NULL)
		delete m_vertex;

	if (m_texCoords != NULL)
		delete m_texCoords;

	if (m_vertexNormals != NULL)
		delete m_vertexNormals;

	if (m_VERTEX_INDICES != NULL)
		delete m_VERTEX_INDICES;

	if (m_RAW_MESH != NULL)
		delete m_RAW_MESH;
}

