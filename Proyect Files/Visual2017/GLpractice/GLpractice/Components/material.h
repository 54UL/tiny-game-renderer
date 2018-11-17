#pragma once


#include <SFML\Graphics.hpp>
#include <GL\glew.h>
#include <gl\GL.h>


#include "..\Rendering\GLtexture.h"
#include "..\Rendering\Shader.h"

//implementar pila de uniforms
class material : public ShaderObject , public GLtexture
{
public:

	
	material();
	~material();

	//Funciones

	void SetActive(bool a);
	void Use();
private:

	bool m_is_Active;

};

