#include "GameController.h"

GameController::GameController(Model* model, View* view) : Controller(model, view), keypressed(false), enterkey(false) //,modelkey(true)
{
}

GameController::~GameController()
{
}

float buttonBuffer;

void GameController::Update()
{

	if (IsKeyPressed(VK_SHIFT))
	{
		keypressed = false;
		model->setCommands(GameModel::COMMANDS::SHIFT);
	}

	if (IsKeyPressed('W') && buttonBuffer < 0.f)
	{
		keypressed = false;
		buttonBuffer = 0.2f;
		model->setCommands(GameModel::COMMANDS::MOVE_UP);
	}
	if (IsKeyPressed('A') && buttonBuffer < 0.f)
	{
		keypressed = false;
		buttonBuffer = 0.2f;
		model->setCommands(GameModel::COMMANDS::MOVE_LEFT);
	}
	if (IsKeyPressed('S') && buttonBuffer < 0.f)
	{
		keypressed = false;
		buttonBuffer = 0.2f;
		model->setCommands(GameModel::COMMANDS::MOVE_DOWN);
	}
	if (IsKeyPressed('D') && buttonBuffer < 0.f)
	{
		keypressed = false;
		buttonBuffer = 0.2f;
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

	if (IsKeyPressed(VK_UP))
		model->setCommands(GameModel::COMMANDS::IDLE_UP);
	if (IsKeyPressed(VK_DOWN))
		model->setCommands(GameModel::COMMANDS::IDLE_DOWN);
	if (IsKeyPressed(VK_LEFT))
		model->setCommands(GameModel::COMMANDS::IDLE_LEFT);
	if (IsKeyPressed(VK_RIGHT))
		model->setCommands(GameModel::COMMANDS::IDLE_RIGHT);

	if (IsKeyPressed(VK_RETURN) && !enterkey)
	{
		enterkey = true;
		model->setCommands(GameModel::COMMANDS::SPEECH_NEXTLINE);
	}
	if (!IsKeyPressed(VK_RETURN) && enterkey)
	{
		enterkey = false;
	}

	buttonBuffer -= m_dElapsedTime;

	Controller::Update();
}