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
	


	 //component type info
	 struct componentType { typedef  ComponentType  current_ct; };



	constexpr unsigned int getComponentTypeID();
	constexpr std::size_t  getComponentSize();
	constexpr void         setEntity(unsigned int E_ID);

};

template<typename ComponentType>
inline Component<ComponentType>::Component()
{

}

template<typename ComponentType>
inline Component<ComponentType>::~Component()
{
}
