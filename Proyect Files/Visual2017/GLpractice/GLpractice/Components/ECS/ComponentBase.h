#pragma once



#include "Component.h"
#include "ComponentsMMU.h"


//esta clase agrupa todos los componentes, es una interfaz
class ComponentBase
{
private:
	
public:
	ComponentBase();
	~ComponentBase();


	//Funciones para el componente
	
	//get
	template<typename T>
	Component<T> & getComponent(unsigned int id);
	//set
	//remove
	//add
	//contains


};

