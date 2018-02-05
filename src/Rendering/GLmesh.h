#pragma once

#include <glew.h>
#include <gl\GL.h>
#include <glm.hpp>
#include "Shader.h"
#include "Transform.h"
#include "modelFormat.h"

//This class only register the vertices in the respective buffers

typedef enum MESH_GL_FORMAT {empty,OnlyVertexVec2,OnlyVertexVec3,Vert_TexC_VertN,VertAndTc};

class GLmesh
{


public:
	GLmesh();
	~GLmesh();

	 //Creation and deletion
	 void CreateMesh(glm::vec3 * MeshData, unsigned int VertexCount);//Generic model creation
	 void CreateMesh(glm::vec3 * MeshData, glm::vec2 * TexCoords, unsigned int VertexCount,unsigned int TexCoordsCount);
	 //This functions are for 3D models ready with obj, triangulate models, vertex,normals,Tcoords
	 void CreateMesh(VertexSpec * VertexSpecArray, unsigned int  * Indices, unsigned int VertexCount, unsigned int IndicesCount);
	 void CreateMeshFromObjModel(const char *fname);
	
	 //Utility functions
	 void CleanUpMesh();
	 GLuint GetVAO();
	 GLuint getAuxVBO();

	 unsigned int getVertexCount();
	 void MakeAsQuad(float width, float height);
	 void MakeAsCircle(float radius);
	 MESH_GL_FORMAT getActualMeshFormat();
private:
	 MESH_GL_FORMAT  m_CurrentFormatBind;
	 unsigned int    m_VertexCount,m_VertexNormalCount,m_VertexTextureCoordCount;
	 GLuint		     m_VAO, m_VBO,m_VBO_AUX, m_EBO; //Vertexarray object { Vertex buffer object,Element buffer object, Vertex normal buffer object, and texcord}
};

