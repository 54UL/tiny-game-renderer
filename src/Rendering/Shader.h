#pragma once 
#include <glm.hpp>
#include <glew.h>
#include <gl\GL.h>
#include "FileIO.h"

class ShaderObject
{
public:
	//Constructors
	ShaderObject(const char * FnVertex, const char * FnFragment);
	ShaderObject();
	ShaderObject(GLuint ProgramID);
	~ShaderObject();

	//specific functions
	//void CompileShader();
	//Functions (this is for constructor and for individual objects)
	bool CreateShader(const char * FnVertex, const char * FnFragment);
	//Getters and setters also uniforms setters and getters
	//Uniform Setters
	 	
	    //Matrix 
	    void setUniform(const char * VarName, glm::mat4 * Matrix4X4);//Sets a 4x4 matrix
		void setUniform(const char * VarName, glm::mat3 Matrix3x3);

		//Samplers
		
		//Simple Numeric
		void setUniform(const char * VarName, GLfloat * floatValue);
	//	void setUniform(const char * VarName, GLdouble doubleValue);
		void setUniform(const char * VarName, GLint    intValue);
		//Vectors overloads
		void setUniform(const char * VarName, glm::vec2 Vector2);
		void setUniform(const char * VarName, glm::vec3 Vector3);
		void setUniform(const char * VarName, glm::vec4 Vector4);
        //Utility functions

		void SetShader(GLuint ExistingProgram);

		GLuint GetProgram();
protected:
	GLuint VertexID, FragmentID, ShaderProgramID;

};

