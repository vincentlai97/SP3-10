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

	virtual void Update();

	bool IsKeyPressed(unsigned short key) { return ((GetAsyncKeyState(key) & 0x8001) != 0); }

public:
	Controller(Model* model, View* view) : model(model), view(view) {}

	virtual void Init();
	virtual void RunLoop();
};

#endif