#ifndef MENUVIEW_H
#define MENUVIEW_H

#include "View.h"
#include "MenuModel.h"

class MenuView : public View
{
private:

public:
	MenuView(Model* model = NULL);
	~MenuView();

	void Render();
	void RenderMenu();

};

#endif