#include "GLtexture.h"

#include <GL\glew.h>
#include <GL\gl.h>
#include <SFML\Graphics.hpp>
#include <iostream>
//#include <SFML\Graphics\Image.hpp>
GLtexture::GLtexture()
{
	m_CurrentTexIndex = 0;
	m_empty = true;
}


GLtexture::~GLtexture()
{

}

void GLtexture::LoadTexture(const char * fname)
{
	sf::Image m_PixelsSFimg;
    //	m_PixelsSFimg.create(256, 256, sf::Color::Blue);

	if (!m_PixelsSFimg.loadFromFile(fname))
	{
		std::cout << "error opening the texture : " << fname << std::endl;
		return;
	}
	else
		std::cout <<"the texture "<<fname << std::endl;
	m_empty = false;
	//Creating and setting up the texture
	glGenTextures(1, &m_TextureID[m_CurrentTexIndex]);
	glActiveTexture(GL_TEXTURE0 + m_CurrentTexIndex);
	glBindTexture(GL_TEXTURE_2D, m_TextureID[m_CurrentTexIndex]);
      //Parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//texture loading with the correspond format, default rgba
	glTexImage2D(GL_TEXTURE_2D,0, GL_RGBA, m_PixelsSFimg.getSize().x, m_PixelsSFimg.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_PixelsSFimg.getPixelsPtr());
	
}

void GLtexture::UseTexture()
{
	//quitar esta verga o cambiarla
	if (!m_empty)
	{

		for (int i = 0; i <= m_CurrentTexIndex; i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, m_TextureID[i]);
		}

	}
	
}

void GLtexture::CleanUp()
{
	glDeleteTextures(m_CurrentTexIndex, m_TextureID);
}

void GLtexture::Clean(GLuint TextureToDelete)
{
	glDeleteTextures(1, &m_TextureID[TextureToDelete]);
}

