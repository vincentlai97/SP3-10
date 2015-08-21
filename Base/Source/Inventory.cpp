#include "Inventory.h"


Inventory::Inventory(void)
{
}


Inventory::~Inventory(void)
{
}

void Inventory::Init()
{
	for(int i = 0 ; i < 10; i++)
	{
		PlayerInventory[i] = new Item();
	}

	for(int i = 0 ; i < 4 ; i++)
	{
		meshlist[i] = new Mesh("null");
	}

	meshlist[MIRROR] = MeshBuilder::GenerateText("border",1,1);
	meshlist[MIRROR]->textureID[0] = LoadTGA("Image//Mirror.tga");

	meshlist[TRAP] = MeshBuilder::GenerateText("border",1,1);
	meshlist[TRAP]->textureID[0] = LoadTGA("Image//Trap.tga");

	meshlist[HOLOGRAM] = MeshBuilder::GenerateText("border",1,1);
	meshlist[HOLOGRAM]->textureID[0] = LoadTGA("Image//Holo.tga");

	meshlist[THROWABLE] = MeshBuilder::GenerateText("border",1,1);
	meshlist[THROWABLE]->textureID[0] = LoadTGA("Image//Random.tga");

	DefaultItem[MIRROR].Set("Mirror",MIRROR,1,false);
	DefaultItem[TRAP].Set("Trap",TRAP,1,false);
	DefaultItem[HOLOGRAM].Set("Hologram",HOLOGRAM,1,false);
	DefaultItem[THROWABLE].Set("Throwable",THROWABLE,1,false);

}

bool Inventory::AddToInvent(Item a)
{
	for(int i = 0 ; i < sizeof(PlayerInventory)/4 ; i++)
	{
		if(PlayerInventory[i]->getID() == a.getID() || PlayerInventory[i]->getID() == -1)
		{
			a.SetOnground(false);
			PlayerInventory[i]->Loot(a);
			PlayerInventory[i]->setMesh(meshlist[PlayerInventory[i]->getID()]);
			return true;
		}
	}

	return false;
}

bool Inventory::AddToInvent(int ID)
{
	for(int i = 0 ; i < sizeof(PlayerInventory)/4 ; i++)
	{
		if(PlayerInventory[i]->getID() == ID || PlayerInventory[i]->getID() == -1)
		{
			PlayerInventory[i]->Loot(DefaultItem[ID]);
			PlayerInventory[i]->setMesh(meshlist[PlayerInventory[i]->getID()]);
			return true;
		}
	}

	return false;
}

bool Inventory::UseItem(int num)
{
	if(PlayerInventory[num]->getCount() > 0 )
	{
		PlayerInventory[num]->SetCount(PlayerInventory[num]->getCount() - 1);


		if(PlayerInventory[num]->getCount() == 0)
		{
			for(int i = 0 ; PlayerInventory[num+i]->getID() != -1 ; i++)
			{
				PlayerInventory[num+i] = PlayerInventory[num+i+1];

				if(PlayerInventory[num+i+1]->getID() == -1)
				{
					PlayerInventory[num+i] = new Item();
				}
			}
		}

		return true;
	}

	return false;
}

Item* Inventory::getItem(int num)
{
	return PlayerInventory[num];
}