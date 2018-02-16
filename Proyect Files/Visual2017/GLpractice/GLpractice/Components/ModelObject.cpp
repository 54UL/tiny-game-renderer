
#include <GL\glew.h>
#include <gl\GL.h>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>



#include "..\Rendering\GLmesh.h"
#include "Camera.h"
#include "ModelObject.h"
#include "Transform.h"

ModelObject::ModelObject()
{
	
}


ModelObject::~ModelObject()
{

}

//el numero de drawcalls sera variante e ineficiente cambiar esto por una clase rendererEngine
//aqui encontre un tip de optimizacion, el sistema de renderizado es ambiguo tanto en shaders como en mallas, asi que hacer esto una clase centralizada
void ModelObject::Show( Camera * CurrentCamera)
{
	m_Material.Use();
	//repara el problema de la camara ortografica
	glm::mat4 PMV =  CurrentCamera->GetProyectionMatrix() * glm::inverse( CurrentCamera->GetTransformMatrix()) * this->GetTransformMatrix();

	m_Material.setUniform("PVM", &PMV);
	switch (m_Mesh.getActualMeshFormat())
	{
	case MESH_GL_FORMAT::NonIndexedDrawing:
		glBindVertexArray(m_Mesh.GetVAO());
		glDrawArrays(GL_POLYGON, 0, m_Mesh.getVertexCount());
		break;
	case MESH_GL_FORMAT::IndexedDrawing: //Indexing rendering
		glBindVertexArray(m_Mesh.GetVAO());
		glDrawElements(GL_POLYGON,m_Mesh.getIndicesCount(), GL_UNSIGNED_INT,0);
		break;
	}
	//Un bind all the things can interoperate with other objects
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
