#pragma once
#include <iostream>

//base clase for traits of components

/*
class componente : public component<componente> 
{
   

	void draw()
	float getOperation();

};

*/

template<typename tipo> struct componentType { tipo * component_ptr; };


template<typename ComponentType>
class Component
{
private:
	unsigned int m_Entity_OwnerShip;// id to an entity
protected:
   // void pushComponentTask();
//	void removeComponentTask()
   // void runComponentsTasks();

public:
	Component();   //llamamos al constructor del componente derivado
	~Component();
	

	
	//Tamaño
	static const componentType<ComponentType> m_instance;

	unsigned int getComponentTypeID();
	std::size_t  getComponentSize();
	void         setEntity(unsigned int E_ID);

};

