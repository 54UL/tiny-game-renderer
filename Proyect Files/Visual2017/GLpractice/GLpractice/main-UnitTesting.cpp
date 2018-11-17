#include <SFML/Window.hpp>
#include <GL\glew.h>
#include <gl\GL.h>
#include <iostream>
#include <glm.hpp>

//My Includes
#include "System\FileIO.h"
#include "Rendering\GLmesh.h"
#include "Rendering\Shader.h"
#include "Components\Camera.h"
#include "Components\ModelObject.h"
#include "Components\Transform.h"
#include "System\ModelHandling\modelParser.h"



/*
por hacer:

	agregar sistema sencillo de entrada
	agregar sistema de ventanas
	sistema de logs y debugeado

	agregar sistema de tiempo 
	 agregar tiempo delta... importante!! xd
    implementar operadores sobrecargados y constructores requeridos(gltexture,glmesh,etc)

	checar el sistema de renderizado (centralizar)

	funcion de creear malla a partir de otra tambien con las demas primitivas de gl(texturas y shaders) = con operadores

	checar sistema de camara(no funciona ortografico)

	checar sistema de materiales(algo huele a pescado ahi )

	checar el parser y optimizarlo(no funciona bien con los vertex normals)

	verificar que no haya memory leaks

	implementar mas cosas del transform

	agregar funcion de compilar shaders en tiempo de ejecucion

	shaders: implementar sistema de luz sencillo


	to do especiales:

	implementar sistema de ventanas, niveles(scenes) y resources loaders
	multi threading

	implementar sistema de fisica
	implementar sistema de audio

*/


/*

inline void ProccesWindow()

{
	
	system("color 0a");
	//control things (ghost camera propierties)
	glm::vec2 MouseDelta;
	float lasty=0, lastx=0, Mousex=0, Mousey=0;
	float MouseMultplier = 0.4f;
	bool firstPass=true;
	bool LookCursor=true;
	float valueinput=0;
	float valueinput2 = 0;
	float valueinpu3 = 0;
	float valueinput4 = 0;
	
	float elevar = 0;
	float aceleracion = 1;

	float shiftspeed = 10;

	float	angulogiro = 0;

	// create the window
	sf::Window window(sf::VideoMode(800, 600), "opengl saulitos", sf::Style::Default, sf::ContextSettings(8, 8, 4, 4, 6, 0, false));
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(120);

	

	
	GLenum err = glewInit();
	if (GLEW_OK != err)
		std::cout << "errorxd" << std::endl;
 
    



	Camera  Camara(window.getSize().x, window.getSize().y,60,0.1); // don ta el zfar :v? 
	//Camera  Camara(window.getSize().x, window.getSize().y);
	ModelObject Sprite, Sprite2, modelTest;
	
	ModelObject  ModeloCLONADO[32];
	
	//3D MODEL TESTING FORM OBJ
	modelTest.setGlobalPosition(glm::vec3(6,7,8));
	
	modelTest.m_Mesh.CreateMeshFromObjModel("Models/dragonfinal.obj");

	modelTest.m_Material.CreateShader("Shaders/modelVertex.vert", "Shaders/modelFragment.frag");
	
	
	GLuint shaderdelmodeloxd = modelTest.m_Material.GetProgram();

	
	
	/*
	for (int i = 0; i<32; i++)
	{
		ModeloCLONADO[i].setGlobalPosition(glm::vec3(rand() % 100, rand() % 100, rand() % 100));
		ModeloCLONADO[i].setGlobalPosition(glm::vec3(rand() % 360, rand() % 360, rand() % 360 ));
		ModeloCLONADO[i].m_Mesh.CreateMeshFromExistingMesh(modelTest.m_Mesh);
		ModeloCLONADO[i].m_Material.SetShader(shaderdelmodeloxd);
	}
	


	//Sprites
	
	Sprite.setGlobalPosition(glm::vec3(0,0,3));
	Sprite2.setGlobalPosition(glm::vec3(0, 0, -5));

	Sprite.setGlobalRotation(glm::vec3(90, 90, 90));

	Sprite.m_Material.LoadTexture("Textures/soldado.jpg");
	Sprite2.m_Material.LoadTexture(Sprite.m_Material.returnTextureID());

	Sprite.m_Material.CreateShader("Shaders/MainVertex.vert", "Shaders/MainFragment.frag");
	Sprite.m_Mesh.MakeAsQuad(0, 0);

	Sprite2.m_Material.SetShader(Sprite.m_Material.GetProgram());
	Sprite2.m_Mesh.MakeAsQuad(0, 0);


	bool running = true;

	while (running)
	{
		// handle events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				// end the program
				running = false;
			}
			else if (event.type == sf::Event::EventType::KeyPressed)
			{

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				{
					valueinput = 0.1f*aceleracion;

				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
					valueinput = -0.1f*aceleracion;

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				{
					valueinput2 = 0.1*aceleracion;
					//	std::cout << "xd" << std::endl;

				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
					valueinput2 = -0.1f*aceleracion;

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					valueinpu3 += 0.1f;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
					valueinpu3 -= 0.1f;

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					valueinput4 += 0.1f;
					//std::cout << "xd" << std::endl;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
					valueinput4 -= 0.1f;

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
					LookCursor = true;
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
					LookCursor = false;

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
					elevar = 1 * aceleracion;
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
					elevar = -1 * aceleracion;

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
					aceleracion = shiftspeed;
			


			}
			else if (event.type == sf::Event::EventType::KeyReleased)
			{
				valueinput = 0;
				valueinput2 = 0;
				elevar = 0;
				aceleracion =1;
			}
			else if (event.type == sf::Event::Resized)
			{
				// adjust the viewport when the window is resized
				glViewport(0, 0, event.size.width, event.size.height);
			}
		}
		if (LookCursor)
		{
			lastx = sf::Mouse::getPosition(window).x;
			lasty = sf::Mouse::getPosition(window).y;
			int Centerx = window.getPosition().x + ((float)window.getSize().x / 2);
			int Centery = window.getPosition().y + ((float)window.getSize().y / 2);
			sf::Mouse::setPosition(sf::Vector2i(Centerx, Centery));

			MouseDelta.x = (lastx - sf::Mouse::getPosition(window).x);
			MouseDelta.y = (lasty - sf::Mouse::getPosition(window).y);
		}
	
		glEnable(GL_DEPTH_TEST);
		//glEnable(GL_CULL_FACE);
		//glCullFace(GL_BACK);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.3,0.6, 0.4, 1);
		//glClearColor(0,0,0,0);

		if(!firstPass)
		{
			Mousey -= MouseDelta.y*MouseMultplier;
			Mousex -= MouseDelta.x*MouseMultplier;
		}

		glm::vec3 Positionxd = glm::vec3(valueinput2, 0, -valueinput);
		Camara.setGlobalRotation(glm::vec3(Mousey, Mousex, 0));
		Camara.translate(Positionxd);



		//Camara.setLocalPosition(Positionxd);


		

		//Camara.setPosition(Positionxd);

			angulogiro += 0.3f;

		//modelTest.setGlobalRotation(glm::vec3(1, 1, 0),angulogiro);

		//renderizado...
		Sprite.Show(&Camara); 
		Sprite2.Show(&Camara);
        modelTest.Show(&Camara);
		glm::vec3 camarapos = Camara.getGlobalPosition();


		//	std::cout << camarapos.x << " " << camarapos.y << " " << camarapos.z << std::endl;


	    /*
		for(int i =0;i<32;i++)
		{
			ModeloCLONADO[i].Show(&Camara);
			ModeloCLONADO[i].setLocalRotation(glm::vec3(angulogiro, angulogiro, angulogiro));
		}
	

		//glm::vec3 camerarotation = Camara.getEulerGlobalRotaion();
		//std::cout << camerarotation.x << " " <<   camerarotation.y << " " << camerarotation.z << " " << std::endl;


	
		window.display();
		firstPass = false;
	}
	// release resources...
	
}
*/

int main()
{
	//occesWindow();
	return 0;
}
