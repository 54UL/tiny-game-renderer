
#include "ComponentBase.h"
#include "EntitySystem.h"
#include <string>

#pragma once

class EntityBase : public ComponentBase
{
public:
	
	EntityBase();
	~EntityBase();

	EntityBase( const EntityBase& lvalue); //Copy 
	EntityBase(EntityBase&& rvalue);       //move constructor


	unsigned int getEntityID();

	

private:

	//Miembros que conforman una entidad
	unsigned int m_EntityID;
	std::string  m_EntityName;
	

};

