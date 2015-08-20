#include "MainMenuController.h"


CMainMenuController::CMainMenuController(Model* model, View* view) : Controller(model, view)
, down(false)
, index(0)

{
}


CMainMenuController::~CMainMenuController()
{
}

void CMainMenuController::Update()
{
	if (IsKeyPressed(VK_DOWN) && down)
	{
		down = false;
		model->setCommands(CMainMenuModel::COMMANDS::MOVE_DOWN);
		index += 1;
	}
	else if (IsKeyPressed(VK_UP) && down)
	{
		down = false;
		model->setCommands(CMainMenuModel::COMMANDS::MOVE_UP);
		index -= 1;
	}
	else if (IsKeyPressed(VK_RETURN) && down)
	{
		model->setCommands(CMainMenuModel::COMMANDS::ENTER);
	}
	else if (!IsKeyPressed(VK_DOWN) && !down && !IsKeyPressed(VK_UP) && !IsKeyPressed(VK_RETURN))
	{
		down = true;
	}
	if (IsKeyPressed(VK_RETURN) && index == 2)
	{
		Controller::ExitKey = true;
	}
		
	Controller::Update();
}