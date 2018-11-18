#include "GLmesh.h"
#include <GL\glew.h>
#include <gl\GL.h>
#include "glm.hpp"
#include "..\System\ModelHandling\modelFormat.h"
#include "..\System\ModelHandling\modelParser.h"
#include <iostream>


//to do, checar referencias hacia adelante,lreferences y rreferences

GLmesh::GLmesh() 
{
	m_VertexCount = m_VertexNormalCount = m_VertexTextureCoordCount = 0;
	m_CurrentFormatBind = MESH_GL_FORMAT::empty;
	CreatedFromCopy = false;
}

GLmesh::~GLmesh()
{
	CleanUpMesh();
}


//use this if you dont care about indexing rendering 
void GLmesh::CreateMesh(glm::vec3 * MeshData, unsigned int VertexCount)
{
	
	if (m_CurrentFormatBind == empty)
	{
		m_CurrentFormatBind = MESH_GL_FORMAT::NonIndexedDrawing;
	}
	else
	{
		std::cout << "ERROR : vao  = " << m_VAO << " ; is currently created:" << std::endl;
		return;
	}
	    this->m_VertexCount = VertexCount;
		//Create the vao
		glGenVertexArrays(1, &m_VAO);
		//Setting up the data
		glBindVertexArray(m_VAO);
		glGenBuffers(1, &m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)* VertexCount, MeshData, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,sizeof(glm::vec3), (void*)0);
		//Unbind the content
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
}



//okey esto estara un poco sucio ya que usare dos vbos para subir los vertices y las cordenadas de textura(cambiar) todo por un solo buffer
void GLmesh::CreateMesh(glm::vec3 * MeshData, glm::vec2 *TexCoords, unsigned int VertexCount, unsigned int TexCoordsCount)
{
	if (m_CurrentFormatBind == empty)
	{
		m_CurrentFormatBind = MESH_GL_FORMAT::NonIndexedDrawing;
	}
	else
	{
		std::cout << "ERROR : vao  = " << m_VAO << " ; is currently created:" << std::endl;
		return;
	}
	this->m_VertexCount = VertexCount;
	this->m_VertexTextureCoordCount = TexCoordsCount;
	//Create the vao
	glGenVertexArrays(1, &m_VAO);
	//Setting up the data
	glBindVertexArray(m_VAO);
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_VBO_AUX);
	//primer vbo
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)* VertexCount, MeshData, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
	//Segundo vbo
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO_AUX);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2)* TexCoordsCount, TexCoords, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);
	//Unbind the content
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


//dual buffer for drawing with tex coords with indexing
void GLmesh::CreateMesh(glm::vec3 * MeshData, glm::vec2 * TexCoords,  unsigned int * Indices ,unsigned int VertexCount, unsigned int TexCoordsCount, unsigned int IndicesCount)
{
	if (m_CurrentFormatBind == empty)
	{
		m_CurrentFormatBind = MESH_GL_FORMAT::IndexedDrawing;
	}
	else
	{
		std::cout << "ERROR : vao  = " << m_VAO << " ; is currently created:" << std::endl;
		return;
	}
	this->m_VertexCount = VertexCount;
	this->m_VertexTextureCoordCount = TexCoordsCount;
	this->m_IndicesCount = IndicesCount;

	//Create the vao
	glGenVertexArrays(1, &m_VAO);
	//Setting up the data
	glBindVertexArray(m_VAO);
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_VBO_AUX);
	glGenBuffers(1, &this->m_EBO);
	
	//primer vbo
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)* VertexCount, MeshData, GL_STATIC_DRAW);
	//EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*IndicesCount, Indices, GL_STATIC_DRAW);
	//FIRST VBO ATTRIBS
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
	//Segundo vbo
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO_AUX);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2)* TexCoordsCount, TexCoords, GL_STATIC_DRAW);
	////SECOND VBO ATTRIBS
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);
	//Unbind the content
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void GLmesh::CreateMesh(glm::vec3 * MeshData, glm::vec3 * VertexNormals, unsigned int * Indices, unsigned int VertexCount, unsigned int VertexNormalCount, unsigned int IndicesCount)
{
	if (m_CurrentFormatBind == empty)
	{
		m_CurrentFormatBind = MESH_GL_FORMAT::IndexedDrawing;
	}
	else
	{
		std::cout << "ERROR : vao  = " << m_VAO << " ; is currently created:" << std::endl;
		return;
	}
	this->m_VertexCount = VertexCount;
	this->m_VertexNormalCount = VertexNormalCount;
	this->m_IndicesCount = IndicesCount;
	//Create the vao
	glGenVertexArrays(1, &m_VAO);
	//Setting up the data
	glBindVertexArray(m_VAO);
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_VBO_AUX);
	glGenBuffers(1, &this->m_EBO);
	//primer vbo
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)* VertexCount, MeshData, GL_STATIC_DRAW);
	//EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*IndicesCount, Indices, GL_STATIC_DRAW);
	//FIRST VBO ATTRIBS
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
	//Segundo vbo
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO_AUX);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)* VertexNormalCount, VertexNormals, GL_STATIC_DRAW);
	////SECOND VBO ATTRIBS
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
	//Unbind the content
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


//what this exactly does is a shortcout to have an mesh ready for drawing as sprite (vertices and texture coords);
void GLmesh::MakeAsQuad(float width, float height)
{
	//Quad Vertices and texture coords (without normals)
	 glm::vec3 v[] =
	{
		glm::vec3(1,-1, 0),
		glm::vec3(-1,-1, 0),
		glm::vec3(1, 1, 0),
		glm::vec3(-1, 1, 0),
	};
	 glm::vec2 Tc[]
	{
		glm::vec2(1,0),
		glm::vec2(0,0),
		glm::vec2(1,1),
		glm::vec2(0,1)
	};
	unsigned int IndicesQUAD[] = 
	{
	2,1,3,2,0,1
	};
	CreateMesh(v,Tc,IndicesQUAD,4,4,6);
}

void GLmesh::MakeAsCircle(float radius)
{
	std::cout << "not implemented : MakeAsCircle" << std::endl;
}

MESH_GL_FORMAT GLmesh::getActualMeshFormat()
{
	return m_CurrentFormatBind;
}


void GLmesh::CreateMesh(VertexSpec * VertexSpecArray,unsigned int  * Indices,unsigned int VertexCount,unsigned int IndicesCount)
{
	if (m_CurrentFormatBind == empty)
	{
		m_CurrentFormatBind = MESH_GL_FORMAT::IndexedDrawing;
    }
	else
	{
		std::cout << "ERROR : vao  = " << m_VAO << " ; is currently created:" << std::endl;
		return;
	}

	    m_IndicesCount = IndicesCount;

		//Creation of buffers and vao
		glGenVertexArrays(1, &this->m_VAO);
		glBindVertexArray(this->m_VAO);
		glGenBuffers(1, &this->m_VBO);
		glGenBuffers(1, &this->m_EBO);
		//Buffers data
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(VertexSpec)*VertexCount, VertexSpecArray, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*IndicesCount, Indices, GL_STATIC_DRAW);
		//GLSL layout
		glEnableVertexArrayAttrib(this->m_VAO, 0); //Vertex
		glVertexAttribPointer(0, 1, GL_FLOAT, false, sizeof(glm::vec3),(void *)0);
		glEnableVertexArrayAttrib(this->m_VAO, 1); //Tex Coords
		glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(glm::vec2), (void *)offsetof(VertexSpec, TextureCoord));
		glEnableVertexArrayAttrib(this->m_VAO, 2); //Vertex Normals
		glVertexAttribPointer(2, 3, GL_FLOAT, false, sizeof(glm::vec3), (void *)offsetof(VertexSpec, VertexNormal));
		//Unbind the content
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


//TO DO : Elaborar los arreglos aptos para el formato de gl y eliminarlos al no ser usados
void GLmesh::CreateMeshFromObjModel(const char * fname)
{
	modelFormat TMPmodelbuffer;
	modelParser ParserInstance;
	ParserInstance.OpenModel(fname, MODEL_FORMAT::OBJ, &TMPmodelbuffer);
	//una vez en memoria lo convertimos al formato de modelo en open gl... to do
//	glm::vec3 normaltest = glm::vec3(1, 1, 1);

	this->CreateMesh(TMPmodelbuffer.Vertex_c_array(),
		TMPmodelbuffer.VertexNormal_c_array(), TMPmodelbuffer.VertexIndices_c_array(),
		TMPmodelbuffer.Vertex.size(), TMPmodelbuffer.VertexNormal.size(),
		TMPmodelbuffer.FaceIndices.size());
}


void GLmesh::CreateMeshFromExistingMesh(GLmesh & existingMesh)
{
   // just copy all the parameters
	this->m_CurrentFormatBind = existingMesh.m_CurrentFormatBind;
	this->m_VAO = existingMesh.m_VAO;
	this->m_VBO_AUX = existingMesh.m_VBO_AUX;
	this->m_VBO = existingMesh.m_VBO;
	this->m_EBO = existingMesh.m_EBO;
	//tamaños
	this->m_VertexCount = existingMesh.m_VertexCount;
	this->m_IndicesCount = existingMesh.m_IndicesCount;
	this->m_VertexTextureCoordCount = existingMesh.m_VertexTextureCoordCount;
	this->m_VertexNormalCount = existingMesh.m_VertexNormalCount;
	CreatedFromCopy = true;
}

void GLmesh::CleanUpMesh()
{
	if(!CreatedFromCopy)
	{
		//agregar el
		glDeleteBuffers(1, &m_VBO);
		glDeleteBuffers(1, &m_VBO_AUX);
		glDeleteBuffers(1, &m_EBO);
		glDeleteVertexArrays(1, &m_VAO);
	}
}

GLuint GLmesh::GetVAO()
{
	return this->m_VAO;
}

GLuint GLmesh::getAuxVBO()
{
	return this->m_VBO_AUX;
}

GLuint GLmesh::getEBO()
{
	return m_EBO;
}

unsigned int GLmesh::getVertexCount()
{
	return this->m_VertexCount;
}

unsigned int GLmesh::getIndicesCount()
{
	return m_IndicesCount;
}





