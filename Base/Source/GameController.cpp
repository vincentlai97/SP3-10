#include "GameController.h"

GameController::GameController(Model* model, View* view) : Controller(model, view) , keypressed(false)
{
}

GameController::~GameController()
{
}

void GameController::Update()
{
	if (IsKeyPressed('W') && keypressed)
		{
			keypressed = false;
			model->setCommands(GameModel::COMMANDS::MOVE_UP);
		}
		if (IsKeyPressed('A')  && keypressed)
		{
			keypressed = false;
			model->setCommands(GameModel::COMMANDS::MOVE_LEFT);
		}
		if (IsKeyPressed('S') && keypressed)
		{
			keypressed = false;
			model->setCommands(GameModel::COMMANDS::MOVE_DOWN);
		}
		if (IsKeyPressed('D') && keypressed)
		{
			keypressed = false;
			model->setCommands(GameModel::COMMANDS::MOVE_RIGHT);
		}
		if (IsKeyPressed('I') && keypressed)
		{
			keypressed = false;
			model->setCommands(GameModel::COMMANDS::INVENT);
		}
		if (IsKeyPressed('E') && keypressed)
		{
			keypressed = false;
			model->setCommands(GameModel::COMMANDS::ACTION);
		}

	else if(!IsKeyPressed('W') && !IsKeyPressed('A') && !IsKeyPressed('S') && !IsKeyPressed('D') && !IsKeyPressed('I') && !IsKeyPressed('E') && !keypressed)
	{
		keypressed = true;
	}

	Controller::Update();
}