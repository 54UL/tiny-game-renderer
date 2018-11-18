#pragma once

#include "Component.h"
#include <iostream>
#include <limits>

//Wrapper para la clase de alocadores genericos, especializada en el almacenamiento
//de los componentes en memoria, gestionando bloqueos mutuos

enum class   MemoryAllocationType {STACK=1,HEAP=2,BOTH=3,NDF=4};
enum class   AllocatorType {LINEAR,POOL,ARENA,OWN,NDF};//own refers to i dont know what i did 



//cuidado, solo para propocitos de desarrollo se establecen estas constantes
const unsigned int  MAX_HEAP_SZ =   6000000; 
const unsigned int	MAX_STACK_SZ =	2000000; //2mb 

//For lineal allocation
	const unsigned int  HEADER_LENGTH = sizeof(std::size_t);

	//basic template metaprograming for the stack buffer
	template<MemoryAllocationType AllocT>                  //this should be ndf and heap 
	struct MemoryStorage{ unsigned char m_buffer[1] = 0; };

	template<>                  //this for only stack
	struct MemoryStorage<MemoryAllocationType::STACK> { unsigned char m_buffer[MAX_STACK_SZ]; };


	template<>                  //this is for both
	struct MemoryStorage<MemoryAllocationType::BOTH> { unsigned  char m_buffer[MAX_STACK_SZ]; };




	/*
	--esta clase gestiona la memoria de los componentes
	--memoria compartida, stack y heap, 
	--por cada componente, creear un alocador
	--condiciones de carrera se evitan 
	--lista de miembros:

	alloc<component type>(r);

    bool CreateComponent<component type>();
	bool reuseComponent<component type>(component& other); //copy assigment

	//bool rebindComponent<component ToRebind>();

	bool DestroyComponentByID(unsigned int ID);
	bool DestroyComponentByMemoryIndex<Component type>(unsigned int index);

	void DestroyAllComponents();


	*/


template<MemoryAllocationType MaT, AllocatorType AT>
class ComponentsMMU
{
private:
	
	static const MemoryStorage<MaT> m_Allocator_Buffer;
	
public:
	ComponentsMMU();
	~ComponentsMMU();
	
	

	//NEW and construction
   template<typename CT>
  static  CT const * AllocateMem(const CT& component);

   template<typename CT>
   static CT const * AllocateMem(CT&& component);

   //DELETE and destructor
   template<typename CT>
   static void DeAllocateMem(const CT& component);

   //clean up


   //getter
   template<typename CT>
   static CT const * getComponentInMemory(unsigned int id); //Look up for the header to check the id


};




