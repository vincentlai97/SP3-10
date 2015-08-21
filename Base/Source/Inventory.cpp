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

	MeshBox();

	DefaultItem[MIRROR].Set("Mirror",MIRROR,1,false);
	DefaultItem[TRAP].Set("Trap",TRAP,1,false);
	DefaultItem[HOLOGRAM].Set("Hologram",HOLOGRAM,1,false);
	DefaultItem[THROWABLE].Set("Throwable",THROWABLE,1,false);

	DefaultItem[PLAYERB_BOX].Set("MainBoy", PLAYERB_BOX, 1, false);
	DefaultItem[PLAYERG_BOX].Set("MainGirl", PLAYERG_BOX, 1, false);
	DefaultItem[BUTLER_BOX].Set("Butler", BUTLER_BOX, 1, false);
	DefaultItem[CAT_BOX].Set("Cat", CAT_BOX, 1, false);
	DefaultItem[CHARO_BOX].Set("Charo", CHARO_BOX, 1, false);
	DefaultItem[CLOWN_BOX].Set("Clown", CLOWN_BOX, 1, false);
	DefaultItem[DARK_BOX].Set("Dark", DARK_BOX, 1, false);
	DefaultItem[EYES_BOX].Set("Eyes", EYES_BOX, 1, false);
	DefaultItem[GLOW_BOX].Set("Glow", GLOW_BOX, 1, false);
	DefaultItem[HORN_BOX].Set("Horn", HORN_BOX, 1, false);
	DefaultItem[MASK_BOX].Set("Mask", MASK_BOX, 1, false);
	DefaultItem[NOEYES_BOX].Set("NoEyes", NOEYES_BOX, 1, false);
	DefaultItem[SKELETON_BOX].Set("Skeleton", SKELETON_BOX, 1, false);
	DefaultItem[TURBAN_BOX].Set("Turban", TURBAN_BOX, 1, false);
	DefaultItem[WITCH_BOX].Set("Witch", WITCH_BOX, 1, false);
}

void Inventory::MeshBox()
{
	meshlist[PLAYERB_BOX] = MeshBuilder::GenerateText("MainBoyBox", 1, 1);
	meshlist[PLAYERB_BOX]->textureID[0] = LoadTGA("Image//Sprite//Box//MainBox.tga");

	meshlist[PLAYERG_BOX] = MeshBuilder::GenerateText("MainGirlBox", 1, 1);
	meshlist[PLAYERG_BOX]->textureID[0] = LoadTGA("Image//Sprite//Box//MainGBox.tga");

	meshlist[BUTLER_BOX] = MeshBuilder::GenerateText("MainBoyBox", 1, 1);
	meshlist[BUTLER_BOX]->textureID[0] = LoadTGA("Image//Sprite//Box//ButlerBox.tga");

	meshlist[CAT_BOX] = MeshBuilder::GenerateText("MainBoyBox", 1, 1);
	meshlist[CAT_BOX]->textureID[0] = LoadTGA("Image//Sprite//Box//CatBox.tga");

	meshlist[CHARO_BOX] = MeshBuilder::GenerateText("MainBoyBox", 1, 1);
	meshlist[CHARO_BOX]->textureID[0] = LoadTGA("Image//Sprite//Box//CharoBox.tga");

	meshlist[CLOWN_BOX] = MeshBuilder::GenerateText("MainBoyBox", 1, 1);
	meshlist[CLOWN_BOX]->textureID[0] = LoadTGA("Image//Sprite//Box//ClownBox.tga");

	meshlist[DARK_BOX] = MeshBuilder::GenerateText("MainBoyBox", 1, 1);
	meshlist[DARK_BOX]->textureID[0] = LoadTGA("Image//Sprite//Box//DarkBox.tga");

	meshlist[EYES_BOX] = MeshBuilder::GenerateText("MainBoyBox", 1, 1);
	meshlist[EYES_BOX]->textureID[0] = LoadTGA("Image//Sprite//Box//EyesBox.tga");

	meshlist[GLOW_BOX] = MeshBuilder::GenerateText("MainBoyBox", 1, 1);
	meshlist[GLOW_BOX]->textureID[0] = LoadTGA("Image//Sprite//Box//GlowBox.tga");

	meshlist[HORN_BOX] = MeshBuilder::GenerateText("MainBoyBox", 1, 1);
	meshlist[HORN_BOX]->textureID[0] = LoadTGA("Image//Sprite//Box//HornBox.tga");

	meshlist[MASK_BOX] = MeshBuilder::GenerateText("MainBoyBox", 1, 1);
	meshlist[MASK_BOX]->textureID[0] = LoadTGA("Image//Sprite//Box//MaskBox.tga");

	meshlist[NOEYES_BOX] = MeshBuilder::GenerateText("MainBoyBox", 1, 1);
	meshlist[NOEYES_BOX]->textureID[0] = LoadTGA("Image//Sprite//Box//NoEyesBox.tga");

	meshlist[SKELETON_BOX] = MeshBuilder::GenerateText("MainBoyBox", 1, 1);
	meshlist[SKELETON_BOX]->textureID[0] = LoadTGA("Image//Sprite//Box//SkeletonBox.tga");

	meshlist[TURBAN_BOX] = MeshBuilder::GenerateText("MainBoyBox", 1, 1);
	meshlist[TURBAN_BOX]->textureID[0] = LoadTGA("Image//Sprite//Box//TurbanBox.tga");

	meshlist[WITCH_BOX] = MeshBuilder::GenerateText("MainBoyBox", 1, 1);
	meshlist[WITCH_BOX]->textureID[0] = LoadTGA("Image//Sprite//Box//WitchBox.tga");
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