#pragma once
#include "material.h"
#include "..\Rendering\GLmesh.h"
#include "Transform.h"
#include "Camera.h"


//Esto se le podria considerar gameobjetct? 


class ModelObject: public Transform
{

public:


	//Posibles constructores


	//Construcores finales
	ModelObject();
	~ModelObject();

	//las mallas y materiales son conjunto asi que...
	material  m_Material;//This should be a pointer or an array 
	GLmesh    m_Mesh;


	void Show(Camera * CurrentCamera);


	//Functions
private:

};

