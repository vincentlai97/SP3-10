#include "MenuController.h"

MenuController::MenuController(Model* model, View* view) : Controller(model, view)
{
}

MenuController::~MenuController()
{
}

void MenuController::Update()
{
	if (IsKeyPressed(VK_UP)) model->setCommands(MenuModel::COMMANDS::MOVE_UP);
	if (IsKeyPressed(VK_DOWN)) model->setCommands(MenuModel::COMMANDS::MOVE_DOWN);
	if (IsKeyPressed(VK_RETURN)) model->setCommands(MenuModel::COMMANDS::ENTER);

	Controller::Update();
}