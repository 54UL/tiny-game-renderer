#include "Shader.h"
#include "FileIO.h"
#include <glew.h>
#include <gl\GL.h>
#include "gtc\type_ptr.hpp"
#include <iostream>



ShaderObject::ShaderObject(const char * FnVertex, const char * FnFragment)
{

}


ShaderObject::ShaderObject()
{

}

ShaderObject::ShaderObject(GLuint ProgramID)
{
	this->ShaderProgramID = ProgramID;
}

ShaderObject::~ShaderObject()
{

}

//Functions
bool ShaderObject::CreateShader(const char * FnVertex, const char * FnFragment)
{
	FileIO SourceHandlerV,SourceHandlerF;
	//Debug
	if (SourceHandlerV.ReadFile(FnVertex))
	{
		std::cout << "Error opening" << FnVertex << std::endl;
		return true;
	}
	else if (SourceHandlerF.ReadFile(FnFragment))
	{
		std::cout << "Error Opening" << FnFragment << std::endl;
		return true;
	}
	else
		std::cout << "Shaders loaded properly" << std::endl;
	//END DEBUG
	//Compile Vertex shader and handle errors messages
	VertexID = glCreateShader(GL_VERTEX_SHADER);
	const GLchar * srcvertex =(const GLchar*)SourceHandlerV.getFbuffer();
	GLint lenghtfv = SourceHandlerV.getFsize();
	glShaderSource(VertexID, 1,&srcvertex,&lenghtfv);
	glCompileShader(VertexID);
	//Error Handling
	GLint CompileStatus;
	glGetShaderiv(VertexID, GL_COMPILE_STATUS, &CompileStatus);
	if (CompileStatus)
		std::cout << "Vertex Shader "<<FnVertex<<" Compiled" << std::endl;
	else
	{
		GLint shadersourcelenght;
		glGetShaderiv(VertexID, GL_INFO_LOG_LENGTH, &shadersourcelenght);
		char * MessageLog = new char[shadersourcelenght];
		glGetShaderInfoLog(VertexID, shadersourcelenght, NULL, MessageLog);
		//DEBUG
		std::cout <<"VERTEX :"<<FnVertex<<" :"<< MessageLog << std::endl;
		delete MessageLog;
		return 1;
	}
	//fragment shader
	FragmentID = glCreateShader(GL_FRAGMENT_SHADER);
	const GLchar * Fshadersrc =(const GLchar *) SourceHandlerF.getFbuffer();
	GLint flenght = SourceHandlerF.getFsize();
	glShaderSource(FragmentID, 1, &Fshadersrc, &flenght);
	glCompileShader(FragmentID);

	//Error Handling for fragment
	glGetShaderiv(FragmentID, GL_COMPILE_STATUS, &CompileStatus);

	if (CompileStatus)
		std::cout << "Fragmet Shader "<<FnFragment << " Compiled" << std::endl;
	else
	{
		GLint shadersourcelenght;
		glGetShaderiv(VertexID, GL_INFO_LOG_LENGTH, &shadersourcelenght);
		char * MessageLogf = new char[shadersourcelenght];
		glGetShaderInfoLog(VertexID, shadersourcelenght, NULL, MessageLogf);
		//DEBUG
		std::cout <<"FRAGMENT: "<<FnFragment<<" :"<< MessageLogf << std::endl;
		delete MessageLogf;
		return 1;
	}

	//Shader program 
	ShaderProgramID = glCreateProgram();
	glAttachShader(ShaderProgramID, VertexID);
	glAttachShader(ShaderProgramID, FragmentID);
	glLinkProgram(ShaderProgramID);
	//shader program error handling;
	//Free resources
	glDeleteShader(VertexID);
	glDeleteShader(FragmentID);
	return false;
}

void ShaderObject::SetShader(GLuint ExistingProgram)
{
	this->ShaderProgramID = ExistingProgram;
}


GLuint ShaderObject::GetProgram()
{
	return this->ShaderProgramID;
}

//Uniforms

void ShaderObject::setUniform(const char * VarName, glm::mat4   * Matrix4X4)
{
	glUniformMatrix4fv(glGetUniformLocation(this->ShaderProgramID, VarName),
		1, GL_FALSE, glm::value_ptr(*Matrix4X4));
}

void ShaderObject::setUniform(const char * VarName, GLfloat  * floatValue)
{
	glUniform1fv(glGetUniformLocation(this->ShaderProgramID, VarName), 1, floatValue);
}

void ShaderObject::setUniform(const char * VarName, GLint intValue)
{
	glUniform1i(glGetUniformLocation(this->ShaderProgramID, VarName), intValue);
}

void ShaderObject::setUniform(const char * VarName, glm::vec3 Vector3)
{
	glUniform3fv(glGetUniformLocation(this->ShaderProgramID, VarName),
		1, glm::value_ptr(Vector3));
}

