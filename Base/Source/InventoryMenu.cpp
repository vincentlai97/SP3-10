#include "InventoryMenu.h"

InventoryMenu::InventoryMenu()
{
}

InventoryMenu::~InventoryMenu()
{
	delete Invent;
	delete border;
}

void InventoryMenu::Init()
{
	Invent = MeshBuilder::GenerateText("Invent",1,1);
	Invent->textureID[0] = LoadTGA("Image//Inventory2.tga");

	border = MeshBuilder::GenerateText("border",1,1);
	border->textureID[0] = LoadTGA("Image//Border.tga");

	InventPos[0] = Vector3(-6,3.3,0); 
	InventPos[1] = Vector3(-2.2,3.3,0);
	InventPos[2] = Vector3(1.6,3.3,0);
	InventPos[3] = Vector3(5.3,3.3,0); 
	InventPos[4] = Vector3(-6,0,0); 
	InventPos[5] = Vector3(-2.2,0,0);
	InventPos[6] = Vector3(1.6,0,0);
	InventPos[7] = Vector3(5.3,0,0); 
	InventPos[8] = Vector3(-6,-3,0); 
	InventPos[9] = Vector3(-2.2,-3,0);

	InvCount = 0 ;

	showInvent = false;

	inventory.Init();
}

void InventoryMenu::Update()
{
	if(!showInvent)
	{
		showInvent = true;
		InvCount = 0;
	}
	else
	{
		showInvent = false;
	}
}

void InventoryMenu::MoveUp()
{
	if (InvCount > 3) InvCount -= 4;
}

void InventoryMenu::MoveDown()
{
	if (InvCount < 6) InvCount += 4;
}

void InventoryMenu::MoveLeft()
{
	if (InvCount > 0) --InvCount;
}

void InventoryMenu::MoveRight()
{
	if (InvCount < 9) ++InvCount;
}

Mesh* InventoryMenu::getInventMesh()
{
	return Invent;
}

Mesh* InventoryMenu::getborderMesh()
{
	return border;
}

bool InventoryMenu::getInvent()
{
	return showInvent;
}