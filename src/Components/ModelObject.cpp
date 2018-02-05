
#include <glew.h>
#include <gl\GL.h>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>


#include "Camera.h"
#include "ModelObject.h"
#include "Transform.h"
#include "gtc\type_ptr.hpp"

ModelObject::ModelObject()
{
	
}


ModelObject::~ModelObject()
{

}

//aqui encontre un tip de optimizacion, el sistema de renderizado es ambiguo tanto en shaders como en mallas, asi que hacer esto una factoria
void ModelObject::Show( Camera * CurrentCamera)
{

	m_Material.Use();
	glm::mat4 PMV =CurrentCamera->GetProyectionMatrix()* glm::inverse( CurrentCamera->GetTransformMatrix()) * this->GetTransformMatrix();
	m_Material.setUniform("PVM", &PMV);

	// to do hacer un or binario
	switch (m_Mesh.getActualMeshFormat())
	{
	case MESH_GL_FORMAT::OnlyVertexVec3:

		glBindVertexArray(m_Mesh.GetVAO());
		glDrawArrays(GL_POLYGON, 0, m_Mesh.getVertexCount());
		break;
	case MESH_GL_FORMAT::VertAndTc:
		glBindVertexArray(m_Mesh.GetVAO());
		glDrawArrays(GL_POLYGON, 0, m_Mesh.getVertexCount());
		glBindTexture(GL_TEXTURE_2D, 0);
		break;
	case MESH_GL_FORMAT::Vert_TexC_VertN: //Indexing rendering
		glBindVertexArray(m_Mesh.GetVAO());
		glDrawElements(GL_POLYGON, m_Mesh.getVertexCount(), GL_UNSIGNED_INT, 0);
		break;
	}
	glBindVertexArray(0);
	
}
