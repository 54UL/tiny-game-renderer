#pragma once
#include <stdlib.h>
#include <list>




class GameApplication
{
private:


public:
	explicit GameApplication ();

	~GameApplication();

	//System 

	
	void CreateWindow();
	void RemoveWindow();

	void InitALL();
	void InitRendering();
	void InitPhysics();
	void InitAudio();
	void InitBackgroundTasks();
	void InitGUI();
	void InitDebugAndLog();

	void AttachApplcation(const GameApplication & otherapp);
	void detachExecution();

	void AddBackgroundTask();
	void RemoveBackgroundTask();

	void runBgTask();
	void joinBgTask();

	//game 
	void pushGameLogic();//some callback function
	void removeGameLogic();

	void InitGameSystems();
	void ProcessGameSystems();
	void LoadScene();
	void RestartGame();
	void PauseGame();
	void SaveState();
	void LoadState();


	//void pushInputStack(void(*InputFunction)(InputManager & CurrentInput));

};

