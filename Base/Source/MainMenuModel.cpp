#include "MainMenuModel.h"

#include "MeshBuilder.h"
#include "LoadTGA.h"

void CMainMenuModel::Init()
{
	Model::Init();

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

	Text = MeshBuilder::GenerateText("text", 16, 16);
	Text->textureID[0] = LoadTGA("Image//Font.tga");

	commands = new bool[NUM_COMMANDS];

	counter = 0;

	chooselvl = false;

	for (int count = 0; count < NUM_COMMANDS; ++count)
	{
		commands[count] = false;
	}

}

Mesh* CMainMenuModel::getBackgroundMesh()
{
	return meshList[BACKGROUND];
}

Mesh* CMainMenuModel::getMesh(int a)
{
	return meshList[a];
}

void CMainMenuModel::Update(double dt)
{
	if (!chooselvl)
	{
		if (counter < 0) counter = 2;
		if (counter > 2) counter = 0;

	}
	else
	{
		if (counter < 0) counter = 6;
		if (counter > 6) counter = 0;
	}

	if (commands[MOVE_UP]) counter -= 1;
	if (commands[MOVE_DOWN]) counter += 1;

	if (commands[ENTER])
	{
		if (!chooselvl)
		{
			if (counter == 2)
				throw - 2;
			if (counter == 0)
			{
				counter = 0;
				chooselvl = true;
			}
		}
		else
		{
			throw counter;
		}
	}

	for (int i = 0; i < NUM_COMMANDS; i++)
		commands[i] = false;

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


bool CMainMenuModel::getChoose()
{
	return chooselvl;
}

Mesh* CMainMenuModel::getTextMesh()
{
	return Text;
}
