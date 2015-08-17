#include <stdio.h> //Include the standard C++ headers
#include <stdlib.h>

#include <GL/glew.h> //Include GLEW
#include <GLFW/glfw3.h> //Include GLFW

#include "Model.h"
#include "GameModel.h"
#include "GameModel2D.h"
#include "GameModelLevel1.h"
#include "GameModelLevel2.h"
#include "View.h"
#include "GameView.h"
#include "GameView2D.h"
#include "Controller.h"
#include "GameController2D.h"
#include "GameController.h"

void main( void )
{
	Model* model = new GameModel();
	View* view = new GameView(model);
	Controller* controller = new GameController(model, view);

	// Initialize GLFW
	if (!glfwInit()) exit(EXIT_FAILURE);
	controller->Init();
	glewExperimental = true; // Needed for core profile
	// Initialize GLEW
	if (glewInit() != GLEW_OK) exit(EXIT_FAILURE);
	view->Init();
	model->Init();

	controller->RunLoop();

	if (model != NULL) delete model;
	if (view != NULL) delete view;
	if (controller != NULL) delete controller;
}