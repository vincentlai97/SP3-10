#include "InventoryMenu.h"

void InventoryMenu::Init()
{
	Invent = MeshBuilder::GenerateText("Invent",1,1);
	Invent->textureID[0] = LoadTGA("Image//Inventory2.tga");

	border = MeshBuilder::GenerateText("border",1,1);
	border->textureID[0] = LoadTGA("Image//Border.tga");

	InventPos[0] = Vector3(-6,3,0); 
	InventPos[1] = Vector3(-2,3,0);
	InventPos[2] = Vector3(2,3,0);
	InventPos[3] = Vector3(6,3,0); 
	InventPos[4] = Vector3(-6,0,0); 
	InventPos[5] = Vector3(-2,0,0);
	InventPos[6] = Vector3(2,0,0);
	InventPos[7] = Vector3(6,0,0); 
	InventPos[8] = Vector3(-6,-3,0); 
	InventPos[9] = Vector3(-2,-3,0);

	InvCount = 0 ;

	showInvent = false;

	inventory.Init();

	Item wow("Amazing",inventory.TRAP,10,false);
	Item wow2("WUUUR",inventory.MIRROR,15,false);
	Item wow4("AMRIW",inventory.THROWABLE,5,false);
	inventory.AddToInvent(wow);
	inventory.AddToInvent(wow2);
	inventory.AddToInvent(wow4);
	inventory.AddToInvent(2);
	inventory.AddToInvent(2);
	inventory.AddToInvent(2);
	inventory.AddToInvent(2);
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

void InventoryMenu::MoveLeft()
{
	InvCount--;
}

void InventoryMenu::MoveRight()
{
	InvCount++;
}

void InventoryMenu::MoveUp()
{
	InvCount -= 4;
}

void InventoryMenu::MoveDown()
{
	InvCount += 4;
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