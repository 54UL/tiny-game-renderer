#pragma once
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>





class Transform
{
public:

	Transform();
	~Transform();

	//operaciones basicas con las transformaciones
	// transformaciones globales (no son afectadas por un padre)
	void setGlobalPosition(glm::vec3 position);
	void setGlobalRotation(glm::vec3 Axis, float Angle);
	//euler from euler angles
	void setGlobalRotation(glm::vec3 Euler);
	//directly form other quaternion
	void setGlobalRotation(glm::quat rotQuat);
	//Transformaciones locales afectadas por padres
	void  setLocalPosition(glm::vec3 position);
	void  setLocalRotation(glm::vec3 euler);
	void  setLocalRotation(glm::quat rotQuat);
	 void translate(glm::vec3 RelativeDirection);
	 //To implement
	 void setGlobalScale(glm::vec3 scaleFactor);
	 void setLocalScale(glm::vec3  scaleFactor);
	 //sets the father of the current transform
	 void setFather(Transform *& father);
	 //unsets the actually father of the current transform
	 void unsetFather();
	 //geters
	 //globals
	 glm::vec3 getGlobalPosition();
	 glm::vec3 getEulerGlobalRotaion();
	 glm::quat getGlobalRotation();
	//locals
	 glm::vec3 getLocalPosition();
	 glm::vec3 getEulerLocalRotation();
	 glm::quat getLocalRotation();
	//Utility Functions.
	glm::mat4 GetTransformMatrix();
	void lookAt(glm::vec3 Target);
	void lookAt(Transform Target);
protected:
	//miembros
	glm::mat4 TransformMatrix;  // m*r*s
	glm::mat4 ModelMatrix;  //Position
	glm::mat4 RotationMatrix; 
	glm::mat4 ScaleMatrix;
	//Meta values
	glm::vec3 LocalPosition;
	glm::vec3 Position;
	glm::vec3 EulerRotation;
};

