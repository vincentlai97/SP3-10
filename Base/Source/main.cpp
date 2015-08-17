#include <stdio.h> //Include the standard C++ headers
#include <stdlib.h>

#include <GL/glew.h> //Include GLEW
#include <GLFW/glfw3.h> //Include GLFW

#include "Model.h"
#include "MenuModel.h"
#include "GameModel2D.h"
#include "GameModelLevel1.h"
#include "GameModelLevel2.h"
#include "View.h"
#include "MenuView.h"
#include "GameView2D.h"
#include "Controller.h"
#include "MenuController.h"
#include "GameController2D.h"

void main( void )
{
	Model* model = new MenuModel();
	View* view = new MenuView(model);
	Controller* controller = new MenuController(model, view);

	// Initialize GLFW
	if (!glfwInit()) exit(EXIT_FAILURE);
	controller->Init();
	glewExperimental = true; // Needed for core profile
	// Initialize GLEW
	if (glewInit() != GLEW_OK) exit(EXIT_FAILURE);
	view->Init();
	model->Init();

	try {
		controller->RunLoop();
	}
	catch (int state)
	{
		glfwDestroyWindow(view->getWindow());
		switch (state)
		{
		case 0:
			model = new GameModelLevel1();
			break;
		case 1:
			model = new GameModelLevel2();
			break;
		}
		view = new GameView2D(model);
		controller = new GameController2D(model, view);

		// Initialize GLFW
		if (!glfwInit()) exit(EXIT_FAILURE);
		controller->Init();
		glewExperimental = true; // Needed for core profile
		// Initialize GLEW
		if (glewInit() != GLEW_OK) exit(EXIT_FAILURE);
		view->Init();
		model->Init();

		controller->RunLoop();
	}

	if (model != NULL) delete model;
	if (view != NULL) delete view;
	if (controller != NULL) delete controller;
}