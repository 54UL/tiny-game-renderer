#pragma once


//Abstraccion de las ventanas utilizando sfml, (to do, implementar las propias, para posix, windows y qt)
//una ventana representa el viewport donde se renderizara cualquier cosa del backend

//Las ventanas comunican sus eventos mediante una interfaz generica de eventos

//la ejecucion se da mediante la task asignada, aqui solo se concentra la implementacion de una ventana

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <glm.hpp>
//#include <Windows.h>
#include <vector>
#include <string>
#include <functional>
#include <atomic>

enum class WindowSystem { SFML,SDL,GLFW,NATIVE_POSIX,NATIVE_WINDOWS,NOT_DEFINED};
enum class WindowEventType {MOUSE,KEYBOARD,WINDOW_STATE,NOT_DEFINED};


//data types specializations

template<WindowSystem Wt>
struct WindowDef
{
};


template<>
struct WindowDef<WindowSystem::SFML>
{
	unsigned int    parentID;
	unsigned int    windowID;
	std::string		WindowName;
	sf::Window		Window;
};




struct WindowEventInterface 
{
	WindowEventType Type;
	unsigned int  ResponseCount;
	unsigned int const * Responses;
};



template<WindowSystem Wsys>
class Game_Window 
{

public:
	Game_Window();
	~Game_Window();

	//Funciones relacionadas

	bool createWindow();
	void StartFrame();
	void EndFrame();
	const WindowEventInterface& ProcessEvents();

	void  hideWindow(std::string& windowName);
	void  hideWindow(unsigned int& windowID);

	void  showWindow(std::string& windowName);
	void  showWindow(unsigned int& windowID);

	void destroyWindow();
	void destroyChilds();
	void destroyAll();

	

	inline glm::vec2 & getMetrics();
	inline glm::vec2 & getMousePos();
	inline float getDeltaTime();
	



	

	WindowDef<Wsys> getWindow();
	WindowDef<Wsys> getWindow(unsigned int ID);
	WindowDef<Wsys> getWindow(std::string& name);
	//Utilidades
	unsigned int getChildCount();
	std::string  getWindowName(unsigned int ID);
private:
	std::atomic<unsigned int> thread_id; // the thread that owns this window/windows

	std::vector<WindowDef<Wsys>> m_windows;
};

