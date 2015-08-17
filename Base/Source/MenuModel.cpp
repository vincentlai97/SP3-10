#include "MenuModel.h"

#include "MeshBuilder.h"
#include "LoadTGA.h"

MenuModel::MenuModel()
{
}

MenuModel::~MenuModel()
{
}

void MenuModel::Init()
{
	Model::Init();

	menuScreen = MeshBuilder::GenerateQuad("menu", Color());
	menuScreen->textureID[0] = LoadTGA("Image//menu.tga");
	arrow = MeshBuilder::GenerateQuad("arrow", Color());
	arrow->textureID[0] = LoadTGA("Image//arrow.tga");

	arrowPosition = 0;

	commands = new bool[NUM_COMMANDS];
	for (int count = 0; count < NUM_COMMANDS; ++count)
		commands[count] = false;
}

void MenuModel::Update(double dt)
{
	Model::Update(dt);

	if (commands[MOVE_UP]) arrowPosition = 0;
	else if (commands[MOVE_DOWN]) arrowPosition = 1;
	if (commands[ENTER]) throw arrowPosition;

	for (int count = 0; count < NUM_COMMANDS; ++count)
		commands[count] = false;
}

void MenuModel::setCommands(int command)
{
	if (command >= 0 && command < NUM_COMMANDS)
		commands[command] = true;
}

Mesh* MenuModel::getMenuMesh()
{
	return menuScreen;
}

Mesh* MenuModel::getArrowMesh()
{
	return arrow;
}

int MenuModel::getArrowPosition()
{
	return arrowPosition;
}