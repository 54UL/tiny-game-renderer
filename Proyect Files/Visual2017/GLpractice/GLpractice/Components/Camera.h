#pragma once
#include <glm.hpp>
#include "Transform.h"


class Camera :  public Transform 
{
public:
	
	Camera(int h,int w);
	Camera(int h, int w, float fov,float znear );

	Camera();
	~Camera();
	glm::mat4 GetProyectionMatrix();
    void SetOrtho(int ScreenXSz,int ScreenYSz);
    void SetPrespective(int ScreenXSz, int ScreenYSz, float FOV, float Znear);
	bool isSetPrespective();
private:
	bool ispresp;
	//miembros
	glm::mat4 ProjectionMatrix;
    //CameraValues
};

