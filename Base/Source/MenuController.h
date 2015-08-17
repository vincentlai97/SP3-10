#ifndef MENUCONTROLLER_H
#define MENUCONTROLLER_H

#include "Controller.h"
#include "MenuView.h"
#include "MenuModel.h"

class MenuController : public Controller
{
private:
	void Update();

public:
	MenuController(Model* model, View* view);
	~MenuController();

};

#endif