#pragma once
#include "Item.h"
#include "Mesh.h"
#include "MeshBuilder.h"
#include "LoadTGA.h"

class Inventory
{
public:

	enum ITEM_TYPE
	{
		MIRROR,
		TRAP,
		HOLOGRAM,
		THROWABLE,
		PLAYERB_BOX,
		PLAYERG_BOX,
		BUTLER_BOX,
		CAT_BOX,
		CHARO_BOX,
		CLOWN_BOX,
		DARK_BOX,
		EYES_BOX,
		GLOW_BOX,
		HORN_BOX,
		MASK_BOX,
		NOEYES_BOX,
		SKELETON_BOX,
		TURBAN_BOX,
		WITCH_BOX,
		KEY,
		TOTAL_ITEM,
	};

	Inventory(void);
	~Inventory(void);

	void Init();

	bool AddToInvent(Item a);
	bool AddToInvent(int ID);

	void MeshBox();

	bool UseItem(int num);

	Item* getItem(int num);

	Item DefaultItem[TOTAL_ITEM];

	Mesh* meshlist[TOTAL_ITEM];

private:
	Item * PlayerInventory[10];
};

