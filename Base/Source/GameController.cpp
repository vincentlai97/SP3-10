#include "GameController.h"

GameController::GameController(Model* model, View* view) : Controller(model, view)
{
}

GameController::~GameController()
{
}

void GameController::Update()
{
	if (IsKeyPressed('W'))
		model->setCommands(GameModel::COMMANDS::MOVE_UP);
	if (IsKeyPressed('A'))
		model->setCommands(GameModel::COMMANDS::MOVE_LEFT);
	if (IsKeyPressed('S'))
		model->setCommands(GameModel::COMMANDS::MOVE_DOWN);
	if (IsKeyPressed('D'))
		model->setCommands(GameModel::COMMANDS::MOVE_RIGHT);

	Controller::Update();
}