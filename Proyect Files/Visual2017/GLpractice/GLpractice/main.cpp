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

//Class
glm::vec3 vertices[] = {
	glm::vec3(-0.5f, -0.5f, 0.0f),
	glm::vec3(0.5f, -0.5f, 0.0f),
	glm::vec3(0.0f,  0.5f, 0.0f)
};


//NO TIENE INDICES ASI QUE NO FUNCA...(se genero en un .obj)
glm::vec3 GizmoVertices[]
{
	glm::vec3(-1.000000 ,-1.000000, 1.000000),
	glm::vec3(-1.000000, 1.000000, 1.000000),
	glm::vec3(-1.000000, -1.000000, -1.000000),
	glm::vec3(-1.000000, 1.000000, -1.000000),
	glm::vec3(1.000000, -1.000000, 1.000000),
	glm::vec3(1.000000, 1.000000, 1.000000),
	glm::vec3(1.000000, -1.000000, -1.000000),
	glm::vec3(1.000000, 1.000000, -1.000000),
	glm::vec3(-1.000000, -1.000000, -5.930170),
	glm::vec3(-1.000000, 1.000000, -5.930170),
	glm::vec3(1.000000, 1.000000, -5.930170),
	glm::vec3(1.000000, -1.000000, -5.930170),
	glm::vec3(5.930170, -1.000000 ,-1.000000),
	glm::vec3(5.930170, 1.000000, -1.000000),
	glm::vec3(5.930170, 1.000000, 1.000000),
	glm::vec3(5.930170, -1.000000, 1.000000),
	glm::vec3(1.000000, 5.930170, -1.000000),
	glm::vec3(-1.000000, 5.930170, -1.000000),
	glm::vec3(-1.000000 ,5.930170, 1.000000),
	glm::vec3(1.000000 ,5.930170, 1.000000)
};


inline void ProccesWindow()

{
	system("color 0a");
	//Mouse Things
	glm::vec2 MouseDelta;
	float lasty=0, lastx=0, Mousex=0, Mousey=0;
	float MouseMultplier = 0.004f;
	bool firstPass=true;


	bool LookCursor=true;
	float valueinput=0;
	float valueinput2 = 0;

	float valueinpu3 = 0;
	float valueinput4 = 0;

	// create the window
	sf::Window window(sf::VideoMode(800, 600), "Carenae framework(gl)", sf::Style::Default, sf::ContextSettings(8, 8, 4, 4, 6, 0, false));
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);


	// load resources, initialize the OpenGL states, ...
	GLenum err = glewInit();
	if (GLEW_OK != err)
		std::cout << "errorxd" << std::endl;
 
    
	std::cout << sizeof(Transform) << std::endl;

	//My objects
	Camera  Camara(window.getSize().x, window.getSize().y,60,0.1);
	
	ModelObject Sprite,Sprite2,modelTest;
	modelTest.setPosition(glm::vec3(0, 0, 0));
	
	modelTest.m_Mesh.CreateMeshFromObjModel("Models/test.obj");
	//modelTest.m_Material.LoadTexture("Textres/grid.png");

	//Sprites
	Sprite.setPosition(glm::vec3(0,0,-5));
	Sprite2.setPosition(glm::vec3(1, 0, 6));
	Sprite.m_Material.LoadTexture("Textures/grid.png");
	Sprite.m_Material.CreateShader("Shaders/MainVertex.vert", "Shaders/MainFragment.frag");
	
	Sprite.m_Mesh.MakeAsQuad(0, 0);

	//this just copy the actual shader to another mesh
	GLuint DEFAULT_SHADER_PROGRAM = Sprite.m_Material.GetProgram();
	Sprite2.m_Material.SetShader(DEFAULT_SHADER_PROGRAM);
	modelTest.m_Material.SetShader(DEFAULT_SHADER_PROGRAM);
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
					valueinput = 0.1f;

				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
					valueinput = -0.1f;
				
									



				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				{
					valueinput2 = 0.1;
					//	std::cout << "xd" << std::endl;

				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
					valueinput2 = -0.1f;
								
									


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

							
							//	Camara.translate(glm::vec3(valueinput2, 0, valueinput));		//Camara.translate(glm::vec3(valueinput4, 0, valueinpu3));

			}
			else if (event.type == sf::Event::EventType::KeyReleased)
			{
				valueinput = 0;
				valueinput2 = 0;
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
		

		//int centerx = (int)((float)window.getSize().x / 2);
		//int centery = (int)((float)window.getSize().y / 2);
		//sf::Mouse::setPosition(sf::Vector2i(centerx,centery));

	

		// clear the buffers
		//gl  states
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.3,0.6, 0.4, 0);

		//std::cout << "mouse delta x " << MouseDelta.x << " mouse delta y " << MouseDelta.y << std::endl;

		//std::cout << "mouse x " << Mousex << " mouse  y " << Mousey << std::endl;

		//Camara.setLocalRotation(glm::vec3(0, valueinput2, 0));
		if(!firstPass)
		{
			Mousey -= MouseDelta.y*MouseMultplier;
			Mousex -= MouseDelta.x*MouseMultplier;
		}
		
		Camara.setRotation(glm::vec3(Mousey, Mousex, 0));
		Camara.translate(glm::vec3(valueinput2, 0, -valueinput));



		modelTest.Show(&Camara);
		Sprite.Show(&Camara); 
		Sprite2.Show(&Camara);


		//Camara.setLocalRotation(glm::vec3(valueinput, valueinput2, 0));
		//std::cout << valueinput << "  " << valueinput2 << std::endl;
		
		// MeshDrawOverHere (MainCameraMatrix)s
		// end the current frame (internally swaps the front and back buffers)
		window.display();
		firstPass = false;
	}
	// release resources...
}





int main()
{
	modelFormat  DataHolder;
	modelParser::OpenModel("Models/test.obj", MODEL_FORMAT::OBJ,&DataHolder,0);
	
	std::system("pause");
	ProccesWindow();
	return 0;
}
