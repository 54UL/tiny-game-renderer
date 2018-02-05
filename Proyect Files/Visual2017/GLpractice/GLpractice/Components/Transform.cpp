#include "Transform.h"
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\quaternion.hpp>

//to do implement apply transform ...(private)

Transform::Transform()
{
	this->TransformMatrix = glm::mat4(1.0f);
	this->ModelMatrix = glm::mat4(1.0f);
	this->RotationMatrix = glm::mat4(1.0);
}


Transform::~Transform()
{
}

void Transform::setPosition(glm::vec3 position)
{
	this->ModelMatrix = glm::translate(this->ModelMatrix, position);
	this->TransformMatrix = ModelMatrix * RotationMatrix;
}

void Transform::setRotation(glm::vec3 Euler)
{
	RotationMatrix = glm::mat4_cast(glm::quat(Euler));
	TransformMatrix = ModelMatrix *RotationMatrix;
}

void Transform::setRotation(glm::quat rotQuat)
{
	RotationMatrix = glm::mat4_cast(rotQuat);
}



void Transform::translate(glm::vec3 RelativeDirection)
{
	glm::quat tmpRot(RotationMatrix);
    ModelMatrix = glm::translate(this->ModelMatrix, tmpRot*RelativeDirection);
	TransformMatrix = ModelMatrix * RotationMatrix;
}

glm::mat4 Transform::GetTransformMatrix()
{
	return this->TransformMatrix;
}

