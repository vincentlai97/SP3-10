#pragma once
#include "View.h"
#include "MainMenuModel.h"
class CMainMenuView : public View
{
private:
	bool b_MenuBGM;
public:

	CMainMenuView(Model* model = NULL);
	~CMainMenuView();

	void Render();
	void RenderBackground();
	void RenderButton();
	void RenderLevel();


};

