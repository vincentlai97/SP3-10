#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Model.h"
#include "View.h"

#include <windows.h>

class Controller 
{
protected:
	Model* model;
	View* view;

	double m_dElapsedTime; // delta time
	double m_dAccumulatedTime_ThreadOne;
	double m_dAccumulatedTime_ThreadTwo;

	virtual void Update();

	bool IsKeyPressed(unsigned short key) { return ((GetAsyncKeyState(key) & 0x8001) != 0); }

public:
	Controller(Model* model, View* view) : model(model), view(view) {}

	virtual void Init(GLFWwindow* a = NULL);
	virtual void RunLoop();
	static bool ExitKey;
};

#endif