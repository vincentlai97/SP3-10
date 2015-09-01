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
#include "RyLevel.h"
#include <irrKlang.h>

#pragma comment(lib, "irrKlang.lib")
using namespace irrklang;

ISoundEngine* MenuBGM1 = createIrrKlangDevice(ESOD_AUTO_DETECT, ESEO_MULTI_THREADED | ESEO_LOAD_PLUGINS | ESEO_USE_3D_BUFFERS);


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
	MenuBGM1->play2D("../irrKlang/media/Menu.mp3", true);
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
				MenuBGM1->stopAllSounds();
				model = new CMainMenuModel();
				view2 = new CMainMenuView(model);
				controller = new CMainMenuController(model, view2);
				MenuBGM1->play2D("../irrKlang/media/Menu.mp3", true);
				break;
			case 0:
				MenuBGM1->stopAllSounds();
				model = new NDlvl();
				MenuBGM1->play2D("../irrKlang/media/Drums.mp3", true);
				break;
			case 1:
				MenuBGM1->stopAllSounds();
				model = new TutLvl2();
				MenuBGM1->play2D("../irrKlang/media/Drums.mp3", true);
				break;
			case 2:
				MenuBGM1->stopAllSounds();
				model = new TutLvl3();
				MenuBGM1->play2D("../irrKlang/media/Drums.mp3", true);
				break;
			case 3:
				MenuBGM1->stopAllSounds();
				model = new StoryModel1();
				MenuBGM1->play2D("../irrKlang/media/Drums.mp3", true);
				break;
			case 4:
				MenuBGM1->stopAllSounds();
				model = new JSlvl();
				MenuBGM1->play2D("../irrKlang/media/level5.mp3", true);
				break;
			case 5:
				MenuBGM1->stopAllSounds();
				model = new jslvl2();
				MenuBGM1->play2D("../irrKlang/media/level5.mp3", true);
				break;
			case 6:
				MenuBGM1->stopAllSounds();
				model = new RyLevel();
				MenuBGM1->play2D("../irrKlang/media/level5.mp3", true);
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