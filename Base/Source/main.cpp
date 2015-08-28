#include <stdio.h> //Include the standard C++ headers
#include <stdlib.h>

#include <GL/glew.h> //Include GLEW
#include <GLFW/glfw3.h> //Include GLFW
#include "Model.h"
#include "MainMenuModel.h"
#include "GameModel.h"
#include "StoryModel1.h"
#include "GameModel2D.h"
#include "GameModelLevel1.h"
#include "GameModelLevel2.h"
#include "View.h"
#include "MainMenuView.h"
#include "GameView.h"
#include "GameView2D.h"
#include "Controller.h"
#include "MainMenuController.h"
#include "GameController2D.h"
#include "GameController.h"
#include "JSLvl.h"
#include "NDLvl.h"
#include "TutLvl2.h"
#include "TutLvl3.h"
#include "jslvl2.h"

void main(void)
{

	Model* model = new CMainMenuModel();
	View* view = new CMainMenuView(model);  // view is the only one not changing 
	Controller* controller = new CMainMenuController(model, view);

	// Initialize GLFW
	if (!glfwInit()) exit(EXIT_FAILURE);
	controller->Init();
	glewExperimental = true; // Needed for core profile
	// Initialize GLEW
	if (glewInit() != GLEW_OK) exit(EXIT_FAILURE);
	view->Init();
	model->Init();

	View* view2 = new CMainMenuView(model); // this is the view that changes
	int n = true;
	while(n)
	{
		try{
			controller->RunLoop();
		}
		catch (int state)
		{
			switch (state)
			{
			case -2:
				controller->ExitKey = true;
				n = false;
				break;
			case -1:
				model = new CMainMenuModel();
				view2 = new CMainMenuView(model);
				controller = new CMainMenuController(model, view2);
				break;
			case 0:
				model = new NDlvl();
				break;
			case 1:
				model = new TutLvl2();
				break;
			case 2:
				model = new TutLvl3();
				break;
			case 3:
				model = new JSlvl();
				break;
			case 4:
				model = new jslvl2();
				break;

			}

			if(state > -1)
			{
				view2 = new GameView(model);
				controller = new GameController(model, view2);
			}

			// Initialize GLFW
			if (!glfwInit()) exit(EXIT_FAILURE);
			controller->Init(view->getWindow());
			glewExperimental = true; // Needed for core profile
			// Initialize GLEW
			if (glewInit() != GLEW_OK) exit(EXIT_FAILURE);
			view2->Init();
			model->Init();

		}
	}

	if (model != NULL) delete model;
	if (view != NULL) {delete view; delete view2;}
	if (controller != NULL) delete controller;

}