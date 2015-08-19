#pragma once
#include "Item.h"
#include "Mesh.h"
#include "MeshBuilder.h"
#include "LoadTGA.h"

class Inventory
{
private:
	Item * PlayerInventory[10];

	Item DefaultItem[4];

	Mesh* meshlist[4];

public:

	enum ITEM
	{
		MIRROR,
		TRAP,
		HOLOGRAM,
		THROWABLE,
		TOTAL_ITEM,
	};

	Inventory(void);
	~Inventory(void);

	void Init();

	bool AddToInvent(Item a);
	bool AddToInvent(int ID);

	bool UseItem(int num);

	Item* getItem(int num);
};

