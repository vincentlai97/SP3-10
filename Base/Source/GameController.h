#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "Controller.h"
#include "GameModel.h"
#include "GameView.h"

class GameController : public Controller
{
private:
	virtual void Update();

public:
	GameController(Model* model, View* view);
	~GameController();

	bool keypressed;
	bool modelkey;
	bool enterkey;
};

#endif