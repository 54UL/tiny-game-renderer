#pragma once
#include "material.h"
#include "..\Rendering\GLmesh.h"
#include "Transform.h"
#include "Camera.h"




class ModelObject: public Transform
{

public:


	//Posibles constructores


	//Construcores finales
	ModelObject();
	~ModelObject();

	//Members
	material  m_Material;//This should be a pointer or an array 
	GLmesh    m_Mesh;
	void Show(Camera * CurrentCamera);
	//Functions
private:

};

