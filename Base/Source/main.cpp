#include <stdio.h> //Include the standard C++ headers
#include <stdlib.h>

#include <GL/glew.h> //Include GLEW
#include <GLFW/glfw3.h> //Include GLFW
#include "Model.h"
#include "MainMenuModel.h"
#include "GameModel.h"
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

void main(void)
{

	Model* model = new CMainMenuModel();
	View* view = new CMainMenuView(model);
	Controller* controller = new CMainMenuController(model, view);

	// Initialize GLFW
	if (!glfwInit()) exit(EXIT_FAILURE);
	controller->Init();
	glewExperimental = true; // Needed for core profile
	// Initialize GLEW
	if (glewInit() != GLEW_OK) exit(EXIT_FAILURE);
	view->Init();
	model->Init();
	try{
		controller->RunLoop();
	}
	catch (int state)
	{
		glfwDestroyWindow(view->getWindow());
		switch (state)
		{
		case 0:
			model = new GameModel();
			view = new GameView(model);
			controller = new GameController(model, view);
			controller->Init();
			view->Init();
			model->Init();

			controller->RunLoop();
			break;
		case 1:
			model = new GameModel();
			break;
		case 2:
			controller->ExitKey = true;
			break;
		}
	}

	if (model != NULL) delete model;
	if (view != NULL) delete view;
	if (controller != NULL) delete controller;

}