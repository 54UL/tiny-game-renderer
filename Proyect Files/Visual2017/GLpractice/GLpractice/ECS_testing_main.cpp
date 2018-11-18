


#include <iostream>

#include "Components\ECS\EntityBase.h"
#include "Components\ECS\ComponentBase.h"
#include <typeinfo>
#include <limits>


class prueba :public Component<prueba>
{
public:
	explicit prueba() { };
	~prueba() {};

	//float getPi() { return 3.141516f; };
	//int m_test;
//	float xd;
	float ss;
private:

};


class ObjetoScene : public EntityBase
{


public:

private:

};

int main(int argc, char* argv[]) 
{
	prueba componente1;

  

	std::cout << "tamaño de prueba "<< typeid(Component<prueba>::componentType::current_ct).name() << std::endl;

	std::cout << std::numeric_limits<std::size_t>::max() << std::endl;


	std::cin.get();


	return 0;
}