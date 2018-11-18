#pragma once



#include "Component.h"
#include "ComponentsMMU.h"
#include <iostream>
#include <functional>
#include <string>
const std::size_t MaxComponentsPerEntity = 256;


//estaa clase es la que contiene todos los componentes de una entidad
//la entidad agrega los componentes que quiera heredandola

//COMPONENT QUERYS RETURN DEFS
enum class  queryType {MESSAGE,UNARY,BOTH,NONE};

template <queryType QT>
struct ComponentQuery
{
	std::string Message;
	std::string * NextMessage =__nullptr;
};


template <>
struct ComponentQuery<queryType::UNARY>
{
	unsigned int Result;
};

template <>
struct ComponentQuery<queryType::BOTH>
{
	unsigned int Result;
	std::string Message;
	std::string * NextMessage = __nullptr;
};
//END OF META STRUCTS AND OTHER CRAZY SHIT(put this in another place pls)

//esta clase agrupa todos los componentes, es una interfaz
class ComponentBase
{
private:


	
public:
	ComponentBase();
	~ComponentBase();



	//queries and predicates
	template<typename T>
	bool contains();


	template<typename T>
	const ComponentQuery<queryType::MESSAGE>&  queryComponentNameById(unsigned int id);

	template<typename T>
	const ComponentQuery<queryType::UNARY>&  queryIdByComponent();
    
	//template<typename T,...args>
	///bool  removeIf(const Component<T>::componentType& component, std::function<bool<>> pfn);


	// logic functions


	//add component
	template<typename T>
	bool addComponent();

    //
	//get
	template<typename T>
	Component<T> & getComponent(unsigned int id);




	

};

