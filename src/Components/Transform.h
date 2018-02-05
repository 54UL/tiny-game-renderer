#pragma once
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>

class Transform
{
public:

	Transform();
	~Transform();

	//transform propierties


	 //transformaciones no arbitrarias
	 void setPosition(glm::vec3 position);
	 void setRotation(glm::vec3 Axis, float Angle);


	 //Transformaciones arbitrarias(guardan el estado anterior)
	 void setRotation(glm::vec3 Euler);
	 void setRotation(glm::quat rotQuat);
	
	 

	 //To implement
	 void translate(glm::vec3 RelativeDirection);
	 void lookAt(glm::vec3 Target);
	 void lookAt(Transform Target);


	 glm::vec3 getGlobalPosition();
	 glm::vec3 getGlobalRotation();

	 glm::vec3 getLocalPosition();
	 glm::vec3 getLocalRotation();
	

	//Utility Functions.
	glm::mat4 GetTransformMatrix();


protected:
	//miembros

	
	glm::mat4 TransformMatrix;  // m*r*s

	glm::mat4 ModelMatrix;  //Position
	glm::mat4 RotationMatrix; 
	glm::mat4 ScaleMatrix;

	//Meta values
	glm::vec3 Position;
	glm::vec3 EulerRotation;

};

