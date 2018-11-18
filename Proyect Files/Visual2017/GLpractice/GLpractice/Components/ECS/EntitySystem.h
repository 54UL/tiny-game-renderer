#pragma once

//esta clase es la encargada de comunicar codigo externo hacia los componentes
//operaciones de valores asignacion de miembros, operaciones de lectura
//procesamiento asicronico, cada cluster de entidades tendra su hilo
//entity system, contiene la raiz de cualquier entidad, es decir
//tiene todas las entidades registradas, 
class EntitySystem
{
private:

	static unsigned int ID_Count;
	
public:
	EntitySystem();
	~EntitySystem();


	//Functions
//	bool pushLogicalFunction(std::function<void(const  EntitySystem * raw_scene)> function);

	
};

