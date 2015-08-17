#ifndef GAMECONTROLLER2D_H
#define GAMECONTROLLER2D_H

#include "Controller.h"
#include "GameView2D.h"
#include "GameModel2D.h"

class GameController2D : public Controller
{
private:
	void Update();

public:
	GameController2D(Model* model, View* view);
	~GameController2D();

};

#endif