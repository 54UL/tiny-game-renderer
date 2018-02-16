#pragma once

#include <GL\glew.h>
#include <gl\GL.h>
#include <glm.hpp>


#include "Shader.h"
#include "..\Components\Transform.h"
#include "..\System\ModelHandling\modelFormat.h"

//This class only register the vertices in the respective buffers

typedef enum MESH_GL_FORMAT {empty,IndexedDrawing,NonIndexedDrawing};



//TO DO PAR ESTA CLASE:
//no es necesario que las funciones sean miembros, convertir en una factoria? 
//esta clase esta destinada a cambiar en otros proyectos

class GLmesh
{

public:
	GLmesh();
	~GLmesh();

	 //Creation and deletion
	 //simple mono buffer direct for drawing without indexing
	  void CreateMesh(glm::vec3 * MeshData, unsigned int VertexCount);//Generic model creation
	 //dual buffer direct for drawing with tex coords without indexing
	  void CreateMesh(glm::vec3 * MeshData, glm::vec2 * TexCoords, unsigned int VertexCount,unsigned int TexCoordsCount);
	 //dual buffer for drawing with tex coords with indexing
	 void CreateMesh(glm::vec3 * MeshData, glm::vec2 * TexCoords,unsigned int * Indices , unsigned int VertexCount, unsigned int TexCoordsCount, unsigned int IndicesCount);
	 //dual buffer for drawing vertex and vertex normal, doesn't include vt, uses vertices,vertices normals and indices :  indexing rendering
	 void CreateMesh(glm::vec3 * MeshData, glm::vec3 * VertexNormals, unsigned int * Indices, unsigned int VertexCount, unsigned int VertexNormalCount, unsigned int IndicesCount);
	 //This functions are for 3D models ready with obj, triangulate models, vertex,normals,Tcoords
	 void CreateMesh(VertexSpec * VertexSpecArray, unsigned int  * Indices, unsigned int VertexCount, unsigned int IndicesCount);


	 modelFormat  GetModelData();

	 //Utility functions
	 void CleanUpMesh();
	 GLuint GetVAO();
	 GLuint getAuxVBO();
	 GLuint getEBO();
	 unsigned int getVertexCount();
	 unsigned int getIndicesCount();
	 void MakeAsQuad(float width, float height);
	 void MakeAsCircle(float radius);
	 void CreateMeshFromObjModel(const char *fname);
	 void CreateMeshFromExistingMesh(GLmesh & existingMesh);
	 MESH_GL_FORMAT getActualMeshFormat();

private:
	 bool CreatedFromCopy;
	 MESH_GL_FORMAT  m_CurrentFormatBind;
	 unsigned int    m_VertexCount,m_VertexNormalCount,m_VertexTextureCoordCount,m_IndicesCount;
	 GLuint		     m_VAO, m_VBO,m_VBO_AUX, m_EBO; //Vertexarray object { Vertex buffer object,Element buffer object, Vertex normal buffer object, and texcord}
};

