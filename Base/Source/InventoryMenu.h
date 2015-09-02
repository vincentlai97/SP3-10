#ifndef INVENTORYMENU_H
#define INVENTORYMENU_H

#include "Model.h"
#include "Inventory.h"

class InventoryMenu 
{
public:
	InventoryMenu();
	~InventoryMenu();

	Mesh *Invent;
	Mesh *border;

	bool showInvent;
	Vector3 InventPos[10];

	int InvCount;
	
	Inventory inventory;

	void Init();
	void Update();

	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();

	Mesh* getInventMesh();

	Mesh* getborderMesh();

	bool getInvent();

};

#endif