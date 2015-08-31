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
	if ((IsKeyPressed(VK_DOWN) && down) || (IsKeyPressed('S') && down))
	{
		down = false;
		model->setCommands(CMainMenuModel::COMMANDS::MOVE_DOWN);
	}
	else if ((IsKeyPressed(VK_UP) && down) || (IsKeyPressed('W') && down))
	{
		down = false;
		model->setCommands(CMainMenuModel::COMMANDS::MOVE_UP);
	}
	else if (IsKeyPressed(VK_RETURN) && down)
	{
		down = false;
		model->setCommands(CMainMenuModel::COMMANDS::ENTER);
		
	}
	else if (!IsKeyPressed(VK_DOWN) && !down && !IsKeyPressed(VK_UP) && !IsKeyPressed(VK_RETURN) && !IsKeyPressed('S') && !IsKeyPressed('W'))
	{
		down = true;
	}
		
	Controller::Update();
}