#include "material.h"

#include <SFML\Graphics.hpp>
#include <GL\glew.h>
#include <gl\GL.h>


material::material()
{
	m_is_Active = true;
}


material::~material()
{

}


void material::SetActive(bool a)
{
	m_is_Active = a;
}

//esta madre esta mal diseñada :v 
void material::Use()
{
	if (m_is_Active)
	{
		if(!this->isEmpty())
		this->UseTexture();

		glUseProgram(this->ShaderProgramID);
	}
}
