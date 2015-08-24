#include "MainMenuModel.h"

#include "MeshBuilder.h"
#include "LoadTGA.h"

void CMainMenuModel::Init()
{
	Model::Init();

	for (int count = 0; count < MainMenu::NUM_MENU; ++count)
	{
		meshList[count] = new Mesh("null");
		meshList[count]->textureID[0] = 0;
	}

	meshList[BACKGROUND] = MeshBuilder::GenerateQuad("background", Color());
	meshList[BACKGROUND]->textureID[0] = LoadTGA("Image\\MenuBG.tga");

	meshList[START_BUTTON] = MeshBuilder::GenerateQuad("Start", Color());
	meshList[START_BUTTON]->textureID[0] = LoadTGA("Image\\Startbtn.tga");

	meshList[LOAD_BUTTON] = MeshBuilder::GenerateQuad("LOAD_BUTTON", Color());
	meshList[LOAD_BUTTON]->textureID[0] = LoadTGA("Image\\Loadbtn.tga");

	meshList[EXIT_BUTTON] = MeshBuilder::GenerateQuad("EXIT_BUTTON", Color());
	meshList[EXIT_BUTTON]->textureID[0] = LoadTGA("Image\\Exitbtn.tga");

	meshList[START_BUTTON2] = MeshBuilder::GenerateQuad("Start", Color());
	meshList[START_BUTTON2]->textureID[0] = LoadTGA("Image\\Startbtn2.tga");

	meshList[LOAD_BUTTON2] = MeshBuilder::GenerateQuad("LOAD_BUTTON", Color());
	meshList[LOAD_BUTTON2]->textureID[0] = LoadTGA("Image\\Loadbtn2.tga");

	meshList[EXIT_BUTTON2] = MeshBuilder::GenerateQuad("EXIT_BUTTON", Color());
	meshList[EXIT_BUTTON2]->textureID[0] = LoadTGA("Image\\Exitbtn2.tga");


	commands = new bool[NUM_COMMANDS];

	counter = 0;
	countminus = false;
	countplus = false;

	for (int count = 0; count < NUM_COMMANDS; ++count)
	{
		commands[count] = false;
	}

}

Mesh* CMainMenuModel::getBackgroundMesh()
{
	return meshList[BACKGROUND];
}

Mesh* CMainMenuModel::getStartMesh()
{
	return meshList[START_BUTTON];
}
Mesh* CMainMenuModel::getLoadMesh()
{
	return meshList[LOAD_BUTTON];
}
Mesh* CMainMenuModel::getExitMesh()
{
	return meshList[EXIT_BUTTON];
}

Mesh* CMainMenuModel::getStartMesh2()
{
	return meshList[START_BUTTON2];
}
Mesh* CMainMenuModel::getLoadMesh2()
{
	return meshList[LOAD_BUTTON2];
}
Mesh* CMainMenuModel::getExitMesh2()
{
	return meshList[EXIT_BUTTON2];
}

void CMainMenuModel::Update(double dt)
{
	if (countminus == true)
	{
		counter -=1;
		countminus = false;
	}
	if (countplus == true)
	{
		counter +=1;
		countplus = false;
	}
	if (counter < 0)
	{
		counter = 2;
	}
	if (counter >2)
	{
		counter = 0;
	}

	if (commands[MOVE_UP])
	{
		countminus = true;
		commands[MOVE_UP] = false;
	}
	if (commands[MOVE_DOWN])
	{
		countplus = true;
		commands[MOVE_DOWN] = false;
	}

}

void CMainMenuModel::setCommands(int command)
{
	if (command >= 0 && command < NUM_COMMANDS)
		commands[command] = true;
}

int CMainMenuModel::getCount(void)
{
	return counter;
}