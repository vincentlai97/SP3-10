#pragma once
#include "Controller.h"
#include "MainMenuModel.h"
#include "MainMenuView.h"
class CMainMenuController :
	public Controller
{
private:
	void Update();
	bool down;
	int index;

public:

	CMainMenuController(Model* model, View* view);
	~CMainMenuController();



};

