#include "GameModel.h"

#include "MeshBuilder.h"
#include "LoadTGA.h"

GameModel::GameModel()
{
}

GameModel::~GameModel()
{
}

void GameModel::Init()
{
	Model::Init();

	for (int count = 0; count < PLAYER_TYPE::NUM_PLAYER; ++count)
	{
		meshPlayer[count] = new Mesh("null");
		meshPlayer[count]->textureID[0] = 0;
	}	
	MeshPlayer();
	ModelSwitch = 1;

	tile = MeshBuilder::GenerateText("tiles", 32, 32);
	tile->textureID[0] = LoadTGA("Image//tile.tga");

	m_tileMap = new TileMap();
	m_tileMap->Init(25, 32, 24, worldWidth, worldHeight);
	m_tileMap->LoadMap("Image//map.csv");

	commands = new bool[NUM_COMMANDS];
	for (int count = 0; count < NUM_COMMANDS; ++count)
		commands[count] = false;

	m_mapOffset_x = 0;
	m_mapOffset_y = 0;
	player = new PlayerCharacter(Vector3 (11, 11, 1));

	Text = MeshBuilder::GenerateText("text",16,16);
	Text->textureID[0] = LoadTGA("Image//Font.tga");

	inventory.Init();

	Aina.Set(1,"WHY",Vector3(3,4,1));
}

void GameModel::MeshPlayer()
{
	meshPlayer[PLAYERB] = MeshBuilder::GenerateText("MainBoyModel", 4, 4);
	meshPlayer[PLAYERB]->textureID[0] = LoadTGA("Image//Sprite//Model//MainBModel.tga");

	meshPlayer[PLAYERG] = MeshBuilder::GenerateText("MainGirlModel", 4, 4);
	meshPlayer[PLAYERG]->textureID[0] = LoadTGA("Image//Sprite//Model//MainGModel.tga");

	meshPlayer[BUTLER] = MeshBuilder::GenerateText("ButlerModel", 4, 4);
	meshPlayer[BUTLER]->textureID[0] = LoadTGA("Image//Sprite//Model//ButlerModel.tga");

	meshPlayer[CAT] = MeshBuilder::GenerateText("CatModel", 4, 4);
	meshPlayer[CAT]->textureID[0] = LoadTGA("Image//Sprite//Model//CatModel.tga");

	meshPlayer[CHARO] = MeshBuilder::GenerateText("CharoModel", 4, 4);
	meshPlayer[CHARO]->textureID[0] = LoadTGA("Image//Sprite//Model//CharoModel.tga");

	meshPlayer[CLOWN] = MeshBuilder::GenerateText("ClownModel", 4, 4);
	meshPlayer[CLOWN]->textureID[0] = LoadTGA("Image//Sprite//Model//ClownModel.tga");

	meshPlayer[DARK] = MeshBuilder::GenerateText("DarkModel", 4, 4);
	meshPlayer[DARK]->textureID[0] = LoadTGA("Image//Sprite//Model//DarkModel.tga");

	meshPlayer[EYES] = MeshBuilder::GenerateText("EyesModel", 4, 4);
	meshPlayer[EYES]->textureID[0] = LoadTGA("Image//Sprite//Model//EyesModel.tga");

	meshPlayer[GLOW] = MeshBuilder::GenerateText("GlowModel", 4, 4);
	meshPlayer[GLOW]->textureID[0] = LoadTGA("Image//Sprite//Model//GlowModel.tga");

	meshPlayer[HORN] = MeshBuilder::GenerateText("HornModel", 4, 4);
	meshPlayer[HORN]->textureID[0] = LoadTGA("Image//Sprite//Model//HornModel.tga");

	meshPlayer[MAID] = MeshBuilder::GenerateText("MaidModel", 4, 4);
	meshPlayer[MAID]->textureID[0] = LoadTGA("Image//Sprite//Model//MaidModel.tga");

	meshPlayer[MASK] = MeshBuilder::GenerateText("MaskModel", 4, 4);
	meshPlayer[MASK]->textureID[0] = LoadTGA("Image//Sprite//Model//MaskModel.tga");

	meshPlayer[NOEYES] = MeshBuilder::GenerateText("NoEyesModel", 4, 4);
	meshPlayer[NOEYES]->textureID[0] = LoadTGA("Image//Sprite//Model//NoEyesModel.tga");

	meshPlayer[SHINIGAMI] = MeshBuilder::GenerateText("ShinigamiModel", 4, 4);
	meshPlayer[SHINIGAMI]->textureID[0] = LoadTGA("Image//Sprite//Model//ShinigamiModel.tga");

	meshPlayer[SKELETON] = MeshBuilder::GenerateText("SkeletonModel", 4, 4);
	meshPlayer[SKELETON]->textureID[0] = LoadTGA("Image//Sprite//Model//SkeletonModel.tga");

	meshPlayer[TURBAN] = MeshBuilder::GenerateText("TurbanModel", 4, 4);
	meshPlayer[TURBAN]->textureID[0] = LoadTGA("Image//Sprite//Model//TurbanModel.tga");

	meshPlayer[WITCH] = MeshBuilder::GenerateText("WitchModel", 4, 4);
	meshPlayer[WITCH]->textureID[0] = LoadTGA("Image//Sprite//Model//WitchModel.tga");
}

void GameModel::Update(double dt)
{
	if (commands[INVENT])
	{
		inventory.Update();
	}

	if (inventory.showInvent)
	{
		if (commands[MOVE_UP] && inventory.InvCount > 3)
		{
			inventory.MoveUp();
		}
		if (commands[MOVE_DOWN] && inventory.InvCount < 6)
		{
			inventory.MoveDown();
		}
		if (commands[MOVE_LEFT] && inventory.InvCount > 0)
		{
			inventory.MoveLeft();
		}
		if (commands[MOVE_RIGHT] && inventory.InvCount < 9)
		{
			inventory.MoveRight();
		}
		if (commands[ACTION])
		{
			inventory.inventory.UseItem(inventory.InvCount);
		}
	}
	else
	{
		if (commands[MODEL_UP])
		{
			ModelSwitch--;
			if (ModelSwitch < 1)
				ModelSwitch = 17;
		}

		if (commands[MODEL_DOWN])
		{
			ModelSwitch++;
			if (ModelSwitch > 17)
				ModelSwitch = 1;
		}
		
		if (commands[MOVE_UP]) 
		{
			player->moveUp();
			Aina.Update(player->getPosition(),m_tileMap);
		}
		if (commands[MOVE_DOWN])
		{
			player->moveDown();
			Aina.Update(player->getPosition(),m_tileMap);
		}
		if (commands[MOVE_LEFT]) 
		{
			player->moveLeft();
			Aina.Update(player->getPosition(),m_tileMap);
		}
		if (commands[MOVE_RIGHT])
		{
			player->moveRight();
			Aina.Update(player->getPosition(),m_tileMap);
		}
	
		player->Update(dt, m_tileMap);
	}

	for (int count = 0; count < NUM_COMMANDS; ++count)
		commands[count] = false;

}

Mesh *GameModel::getTileMesh()
{
	return tile;
}

void GameModel::setCommands(int command)
{
	if (command >= 0 && command < NUM_COMMANDS)
		commands[command] = true;
}

TileMap* GameModel::getTileMap()
{
	return m_tileMap;
}

PlayerCharacter* GameModel::getPlayer()
{
	return player;
}

Mesh* GameModel::getPlayerMesh()
{
	if (ModelSwitch == 1)
	{
		return meshPlayer[PLAYERB];
	}
	else if (ModelSwitch == 2)
	{
		return meshPlayer[PLAYERG];
	}
	else if (ModelSwitch == 3)
	{
		return meshPlayer[BUTLER];
	}
	else if (ModelSwitch == 4)
	{
		return meshPlayer[CAT];
	}
	else if (ModelSwitch == 5)
	{
		return meshPlayer[CHARO];
	}
	else if (ModelSwitch == 6)
	{
		return meshPlayer[CLOWN];
	}
	else if (ModelSwitch == 7)
	{
		return meshPlayer[DARK];
	}
	else if (ModelSwitch == 8)
	{
		return meshPlayer[EYES];
	}
	else if (ModelSwitch == 9)
	{
		return meshPlayer[GLOW];
	}
	else if (ModelSwitch == 10)
	{
		return meshPlayer[HORN];
	}
	else if (ModelSwitch == 11)
	{
		return meshPlayer[MAID];
	}
	else if (ModelSwitch == 12)
	{
		return meshPlayer[MASK];
	}
	else if (ModelSwitch == 13)
	{
		return meshPlayer[NOEYES];
	}
	else if (ModelSwitch == 14)
	{
		return meshPlayer[SHINIGAMI];
	}
	else if (ModelSwitch == 15)
	{
		return meshPlayer[SKELETON];
	}
	else if (ModelSwitch == 16)
	{
		return meshPlayer[TURBAN];
	}
	else if (ModelSwitch == 17)
	{
		return meshPlayer[WITCH];
	}
}

void GameModel::getOffset(float& mapOffset_x, float& mapOffset_y)
{
	mapOffset_x = m_mapOffset_x;
	mapOffset_y = m_mapOffset_y;
}

Mesh *GameModel::getTextMesh()
{
	return Text;
}