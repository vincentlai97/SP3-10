#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "Controller.h"

class GameController : public Controller
{
private:

public:
	GameController(Model* model, View* view);
	~GameController();

	virtual void Update();

};

#endif