#include "Camera.h"
#include <gtc\matrix_transform.hpp>
#include <glm.hpp>



Camera::Camera(int h, int w)
{
	this->SetOrtho(h, w);
}

Camera::Camera(int h, int w, float fov,float znear)
{
	this->SetPrespective(h, w, fov, znear);
	//TransformMatrix = glm::lookAt(glm::vec3(0,0,-5),glm::vec3(0,0,1),glm::vec3(0,1,0));
}

Camera::Camera()
{
}


Camera::~Camera()
{

}

glm::mat4 Camera::GetProyectionMatrix()
{
	return this->ProjectionMatrix;
}

void Camera::SetOrtho(int ScreenXSz, int ScreenYSz)
{
	this->ProjectionMatrix = glm::mat4(1.0f);
	//this->ProjectionMatrix = glm::ortho(1, 1, ScreenXSz, ScreenYSz);
    this->ProjectionMatrix = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);
}

void Camera::SetPrespective(int ScreenXSz, int ScreenYSz, float FOV, float Znear)
{
	//this->ProjectionMatrix = glm::infinitePerspective(glm::radians(FOV), (float)ScreenXSz / (float)ScreenYSz, Znear);
	// this->ProjectionMatrix = glm::mat4(1.0f);
	this->ProjectionMatrix = glm::perspective(glm::radians(FOV), (float)ScreenXSz / (float)ScreenYSz, Znear, 100.0F);
}

