#pragma once

#include "Component.h"
#include <iostream>

enum class   MemoryAllocationType {STACK=1,HEAP=2,BOTH=3,NDF=4};
enum class   AllocatorType {LINEAR,POOL,NDF};



//cuidado, solo para propocitos de desarrollo se establecen estas constantes
const unsigned int  MAX_HEAP_SZ =  2000000; 
const unsigned int	MAX_STACK_SZ = 1000000; //2mb 

//For lineal allocation
	const unsigned int  HEADER_LENGTH = sizeof(std::size_t);

	//basic template metaprograming for the stack buffer
	template<MemoryAllocationType AllocT>                  //this should be ndf and heap 
	struct MemoryStorage{ unsigned char m_buffer[1] = 0; };

	template<>                  //this for only stack
	struct MemoryStorage<MemoryAllocationType::STACK> { unsigned char m_buffer[MAX_STACK_SZ]; };


	template<>                  //this is for both
	struct MemoryStorage<MemoryAllocationType::BOTH> { unsigned  char m_buffer[MAX_STACK_SZ]; };




template<MemoryAllocationType MaT, AllocatorType AT>
class ComponentsMMU
{
private:
	
	static const MemoryStorage<MaT> m_Allocator_Buffer;
	
public:
	ComponentsMMU();
	~ComponentsMMU();
	
	//Funciones de alocamie

	//NEW
   template<typename CT>
    CT const * AllocateMem(const CT& component);

   template<typename CT>
    CT const * AllocateMem(CT&& component);

   //DELETE
   template<typename CT>
   void DeAllocateMem(const CT& component);

   //clean up


   //getter
   template<typename CT>
   CT const * getComponentInMemory(unsigned int id); //Look up for the header to check the id


  

};




