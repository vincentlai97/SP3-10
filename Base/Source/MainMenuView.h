#pragma once
#include "View.h"
#include "MainMenuModel.h"

class CMainMenuView : public View
{
private:

public:

	CMainMenuView(Model* model = NULL);
	~CMainMenuView();

	void Render();
	void RenderBackground();
	void RenderButton();
	void RenderLevel();

};

