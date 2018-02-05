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
	//esta clave sera para evitar ambiguedad en ejecucion ya que puede que un material sea identico a otro
	unsigned int MATERIAL_KEY;

	bool m_is_Active;

};

