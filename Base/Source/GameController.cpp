#include "GameController.h"

GameController::GameController(Model* model, View* view) : Controller(model, view), keypressed(false), modelkey(true)
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
	if (IsKeyPressed('A') && keypressed)
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

	if (!IsKeyPressed('W') && !IsKeyPressed('A') && !IsKeyPressed('S') && !IsKeyPressed('D') && !IsKeyPressed('I') && !IsKeyPressed('E') && !keypressed)
	{
		keypressed = true;
	}

	if (IsKeyPressed('1') && modelkey)
	{
		modelkey = false;
		model->setCommands(GameModel::COMMANDS::MODEL_UP);
	}
	else if (IsKeyPressed('2') && modelkey)
	{
		modelkey = false;
		model->setCommands(GameModel::COMMANDS::MODEL_DOWN);
	}

	if (!IsKeyPressed('1') && !IsKeyPressed('2') && !modelkey)
		modelkey = true;

	Controller::Update();
}