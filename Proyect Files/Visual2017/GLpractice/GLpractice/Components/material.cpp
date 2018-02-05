#include "material.h"

#include <SFML\Graphics.hpp>
#include <GL\glew.h>
#include <gl\GL.h>


material::material()
{
	
}


material::~material()
{

}


void material::SetActive(bool a)
{
	m_is_Active = a;
}

void material::Use()
{
	if (m_is_Active)
	{
		this->UseTexture();
		glUseProgram(this->ShaderProgramID);
	}
}
