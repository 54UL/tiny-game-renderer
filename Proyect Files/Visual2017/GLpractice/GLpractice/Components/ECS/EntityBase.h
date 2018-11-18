
#include "ComponentBase.h"
#include "EntitySystem.h"
#include <string>
#include <functional>
#pragma once

//esta es la clase donde se trataran los diversos componentes

//entity base, -> clase que tiene n componentes sirviendo para ella


class EntityBase : public ComponentBase
{
public:
	
	EntityBase();
	~EntityBase();

	EntityBase( const EntityBase& lvalue); //Copy 
	EntityBase(EntityBase&& rvalue);       //move constructor


	unsigned int getEntityID();
	constexpr void setName(std::string& nname);
	

private:

	//Miembros que conforman una entidad
	unsigned int m_EntityID;
	std::string  m_EntityName;
	

};

