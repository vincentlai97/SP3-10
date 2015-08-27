#include "GameModel.h"

#include "MeshBuilder.h"
#include "LoadTGA.h"
#include "Pathfinding.h"

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

	m_gameState = GAME_STATE::IDLE;

	tile = MeshBuilder::GenerateText("tiles", 32, 32);
	tile->textureID[0] = LoadTGA("Image//tile.tga");

	m_tileMap = new TileMap();
	m_tileMap->Init(25, 32, 24, worldWidth, worldHeight);
	m_tileMap->LoadMap("Image//mylevel.csv");

	m_itemMap = new TileMap();
	m_itemMap->Init(25, 32, 24, worldWidth, worldHeight);
	m_itemMap->LoadMap("Image//mylevelitems.csv");

	commands = new bool[NUM_COMMANDS];
	for (int count = 0; count < NUM_COMMANDS; ++count)
		commands[count] = false;

	m_mapOffset_x = 0;
	m_mapOffset_y = 0;
	player = new PlayerCharacter(Vector3(19, 11, 0));

	Text = MeshBuilder::GenerateText("text", 16, 16);
	Text->textureID[0] = LoadTGA("Image//Font.tga");

	floorTiles.push_back(112);
	floorTiles.push_back(309);
	floorTiles.push_back(402);
	floorTiles.push_back(405);

	shadow = MeshBuilder::GenerateQuad("shadow", Color());
	shadow->textureID[0] = LoadTGA("Image//shadow.tga");

	inventory.Init();
	InvenTime = 0;

	Aina = new AI(Vector3(3, 4, 0), NULL, Vector3(3, 0, 0));

	inventory.inventory.AddToInvent(inventory.inventory.PLAYERB_BOX);
	inventory.inventory.AddToInvent(inventory.inventory.CAT_BOX);

	PlaceItemState = false;

	win = false;
	numKey = 0;
	//getKeys();

	for (int count = 0; count < SPEECH_TYPE::NUM_SPEECH; ++count)
	{
		meshSpeech[count] = new Mesh("null");
		meshSpeech[count]->textureID[0] = 0;
	}
	MeshSpeech();

	speech.Textfile("SpeechText//CharacterFile.txt", true);
	speech.Textfile("SpeechText//HowToPlayFile.txt", false);

	InstructFile = "SpeechText//Instruction//MoveCharacter.txt";
	InstructText = true;

	mirror = Vector3(-1, -1, 0);
}

#define itemTouched(character) m_itemMap->getTile(character->getPosition().x, character->getPosition().y)

void GameModel::Update(double dt)
{
	switch (m_gameState)
	{
	case GAME_STATE::IDLE:
		//Movement
		if (commands[MOVE_UP]) player->moveUp();
		if (commands[MOVE_DOWN]) player->moveDown();
		if (commands[MOVE_LEFT]) player->moveLeft();
		if (commands[MOVE_RIGHT]) player->moveRight();
		if (!player->getAcceleration().IsZero()) { m_gameState = GAME_STATE::PLAYER_TURN; break; }

		//Open inventory
		if (commands[INVENT]) { m_gameState = GAME_STATE::INVENTORY; break; }

		//Item interaction with player
		if (itemTouched(player) >= 0 && itemTouched(player) < Inventory::TOTAL_ITEM)
		{
			if (itemTouched(player) == Inventory::KEY)
				Key = true;

			inventory.inventory.AddToInvent(itemTouched(player));
			speech.talking = true;
			speech.Obtain("SpeechText//Obtain.txt", true, inventory.inventory.DefaultItem[itemTouched(player)].getName());
			m_itemMap->SetTile(player->getPosition().x, player->getPosition().y, -1);
			m_gameState = SPEECH;
			break;
		}
		
		//Item interaction with enemies
		if (itemTouched(Aina) > Inventory::TOTAL_ITEM && itemTouched(Aina) < Inventory::TOTAL_ITEM * 2)
		{
			if (itemTouched(Aina) == Inventory::TRAP + Inventory::TOTAL_ITEM)
			{
				Aina->setAiActive(false);
				m_itemMap->SetTile(Aina->getPosition().x, Aina->getPosition().y, -1);
			}
		}

		//Initiate character speech
		if (commands[SPEECH_NEXTLINE])
		{
			speech.talking = true;
			const char* temp = speech.CharacterText[ModelSwitch - 1].c_str();
			speech.Dialogue(temp);
			m_gameState = GAME_STATE::SPEECH;
			break;
		}
		break;
	case GAME_STATE::PLAYER_TURN:
		player->Update(dt, m_tileMap);
		if (player->getVelocity().IsZero())
			m_gameState = GAME_STATE::AI_TURN;
		break;
	case GAME_STATE::AI_TURN:
		Aina->Update(player->getPosition(), m_tileMap);
		m_gameState = GAME_STATE::IDLE;
		break;
	case GAME_STATE::INVENTORY:
		if (commands[INVENT]) { m_gameState = GAME_STATE::IDLE; break; }
		if (commands[ACTION])
		{
			if (inventory.inventory.getItem(inventory.InvCount)->getID() >= Inventory::ITEM_TYPE::MIRROR
				&& inventory.inventory.getItem(inventory.InvCount)->getID() <= Inventory::ITEM_TYPE::THROWABLE)
				m_gameState = PLACE_ITEM;
			else if (inventory.inventory.getItem(inventory.InvCount)->getID() >= Inventory::ITEM_TYPE::PLAYERB_BOX
				&& inventory.inventory.getItem(inventory.InvCount)->getID() <= Inventory::ITEM_TYPE::WITCH_BOX)
			{
				ModelSwitch = inventory.inventory.getItem(inventory.InvCount)->getID() - 3;
				inventory.inventory.UseItem(inventory.InvCount);
				m_gameState = IDLE;
			}
		}
		if (commands[MOVE_UP]) inventory.MoveUp();
		if (commands[MOVE_DOWN]) inventory.MoveDown();
		if (commands[MOVE_LEFT]) inventory.MoveLeft();
		if (commands[MOVE_RIGHT]) inventory.MoveRight();
		break;
	case GAME_STATE::PLACE_ITEM:
		if ((inventory.inventory.getItem(inventory.InvCount)->getID() <= inventory.inventory.THROWABLE && inventory.inventory.getItem(inventory.InvCount)->getID() >= inventory.inventory.MIRROR))
		{
			if (!player->getDirection().IsZero())
			{
				Vector3 placePosition = player->getPosition() + player->getDirection();
				if (m_itemMap->getTile(placePosition.x, placePosition.y) < 0)
					m_itemMap->SetTile(placePosition.x, placePosition.y, inventory.inventory.getItem(inventory.InvCount)->getID() + Inventory::TOTAL_ITEM);
				if (inventory.inventory.getItem(inventory.InvCount)->getID() == Inventory::MIRROR) mirror = placePosition;
				speech.talking = true;
				speech.Obtain("SpeechText//Obtain.txt", false, inventory.inventory.getItem(inventory.InvCount)->getName());
				inventory.inventory.UseItem(inventory.InvCount);
				m_gameState = GAME_STATE::SPEECH;
			}
		}
		break;
	case GAME_STATE::SPEECH:
		if (commands[SPEECH_NEXTLINE]) speech.KeyPressed = true;
		if (speech.talking) speech.Update(dt);
		else m_gameState = GAME_STATE::IDLE;
		break;
	}

	/*if (!player->getWin())
	{

	m_mapOffset_x = player->getPosition().x - (float)m_tileMap->getNumOfTilesWidth() / 2.f;
	m_mapOffset_x = Math::Clamp(m_mapOffset_x, 0.f, (float)(m_tileMap->getMapWidth() - m_tileMap->getNumOfTilesWidth()));

	m_mapOffset_y = player->getPosition().y - (float)m_tileMap->getNumOfTilesHeight() / 2.f;
	m_mapOffset_y = Math::Clamp(m_mapOffset_y, 0.f, (float)(m_tileMap->getMapHeight() - m_tileMap->getNumOfTilesHeight()));

	if (commands[INVENT] && !player->getMove())
	{
	inventory.Update();
	}

	if (inventory.showInvent)
	{
	InvenTime -= (float)dt;

	if (InvenTime < 0)
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
	InvenTime = 0.4f;
	}

	if (!commands[MOVE_UP] && !commands[MOVE_DOWN] && !commands[MOVE_LEFT] && !commands[MOVE_RIGHT])
	InvenTime = 0.f;

	if (commands[ACTION])
	{
	if (inventory.inventory.getItem(inventory.InvCount)->getID() >= inventory.inventory.PLAYERB_BOX && inventory.inventory.getItem(inventory.InvCount)->getID() <= inventory.inventory.WITCH_BOX)
	{
	ModelSwitch = inventory.inventory.getItem(inventory.InvCount)->getID() - 3;
	inventory.inventory.UseItem(inventory.InvCount);
	inventory.showInvent = false;
	}

	if (ModelSwitch < 1)
	ModelSwitch = 15;

	if (ModelSwitch > 15)
	ModelSwitch = 1;

	if (inventory.inventory.getItem(inventory.InvCount)->getID() >= inventory.inventory.MIRROR && inventory.inventory.getItem(inventory.InvCount)->getID() <= inventory.inventory.THROWABLE)
	PlaceItemState = true;

	}
	}
	else
	{
	if (commands[MODEL_UP])
	{
	ModelSwitch--;
	if (ModelSwitch < 1)
	ModelSwitch = 15;
	}

	if (commands[MODEL_DOWN])
	{
	ModelSwitch++;
	if (ModelSwitch > 15)
	ModelSwitch = 1;
	}

	if (commands[MOVE_UP] && !speech.talking)
	{
	if (!player->getMove())
	if (player->moveUp())
	Aina->Update(player->getPosition(), m_tileMap);
	}
	if (commands[MOVE_DOWN] && !speech.talking)
	{
	if (!player->getMove())
	if (player->moveDown())
	Aina->Update(player->getPosition(), m_tileMap);
	}
	if (commands[MOVE_LEFT] && !speech.talking)
	{
	if (!player->getMove())
	if (player->moveLeft())
	Aina->Update(player->getPosition(), m_tileMap);
	}
	if (commands[MOVE_RIGHT] && !speech.talking)
	{
	if (!player->getMove())
	if (player->moveRight())
	Aina->Update(player->getPosition(), m_tileMap);
	}
	if (commands[IDLE_UP] && !speech.talking)
	{
	player->idleUp();
	}
	if (commands[IDLE_DOWN] && !speech.talking)
	{
	player->idleDown();
	}
	if (commands[IDLE_LEFT] && !speech.talking)
	{
	player->idleLeft();
	}
	if (commands[IDLE_RIGHT] && !speech.talking)
	{
	player->idleRight();
	}

	if (commands[SPEECH_NEXTLINE] && !speech.talking)
	{
	speech.talking = true;

	const char* temp = speech.CharacterText[ModelSwitch - 1].c_str();
	speech.Dialogue(temp);
	}
	else if (commands[SPEECH_NEXTLINE] && speech.talking)
	{
	speech.KeyPressed = true;
	}

	if (speech.talking)
	speech.Update(dt);


	player->Update(dt, m_tileMap);

	if (player->TouchItem(m_itemMap) > -1 && player->TouchItem(m_itemMap) < inventory.inventory.TOTAL_ITEM + inventory.inventory.TOTAL_ITEM)
	{
	if (player->TouchItem(m_itemMap) < inventory.inventory.TOTAL_ITEM)
	{
	if (player->TouchItem(m_itemMap) == inventory.inventory.KEY)
	Key = true;

	inventory.inventory.AddToInvent(player->TouchItem(m_itemMap));
	speech.talking = true;
	speech.Obtain("SpeechText//Obtain.txt", true, inventory.inventory.DefaultItem[(player->TouchItem(m_itemMap))].getName());
	player->RemoveItem(m_itemMap);
	}
	}
	if (Aina->TouchItem(m_itemMap) == 1 + inventory.inventory.TOTAL_ITEM)
	{
	Aina->setAiActive(false);
	Aina->RemoveItem(m_itemMap);

	}
	}

	if (PlaceItemState == true)
	{
	if ((inventory.inventory.getItem(inventory.InvCount)->getID() <= inventory.inventory.THROWABLE && inventory.inventory.getItem(inventory.InvCount)->getID() >= inventory.inventory.MIRROR))
	{
	if (player->PlayerDirUp())
	{
	if (m_itemMap->getTile(player->getPosition().x, floor(player->getPosition().y + 1)) < 0 && m_tileMap->getTile(player->getPosition().x, floor(player->getPosition().y + 1)) < 0)
	{
	m_itemMap->SetTile(player->getPosition().x, floor(player->getPosition().y + 1), inventory.inventory.getItem(inventory.InvCount)->getID() + Inventory::TOTAL_ITEM);
	speech.talking = true;
	speech.Obtain("SpeechText//Obtain.txt", false, inventory.inventory.getItem(inventory.InvCount)->getName());
	inventory.inventory.UseItem(inventory.InvCount);
	inventory.showInvent = false;
	}
	PlaceItemState = false;
	}
	else if (player->PlayerDirDown())
	{
	if (m_itemMap->getTile(player->getPosition().x, floor(player->getPosition().y - 1)) < 0 && m_tileMap->getTile(player->getPosition().x, floor(player->getPosition().y - 1)) < 0)
	{
	m_itemMap->SetTile(player->getPosition().x, floor(player->getPosition().y - 1), inventory.inventory.getItem(inventory.InvCount)->getID() + Inventory::TOTAL_ITEM);
	speech.talking = true;
	speech.Obtain("SpeechText//Obtain.txt", false, inventory.inventory.getItem(inventory.InvCount)->getName());
	inventory.inventory.UseItem(inventory.InvCount);
	inventory.showInvent = false;
	}
	PlaceItemState = false;
	}
	else if (player->PlayerDirLeft())
	{
	if (m_itemMap->getTile(player->getPosition().x - 1, floor(player->getPosition().y)) < 0 && m_tileMap->getTile(player->getPosition().x - 1, floor(player->getPosition().y)) < 0)
	{
	m_itemMap->SetTile(player->getPosition().x - 1, floor(player->getPosition().y), inventory.inventory.getItem(inventory.InvCount)->getID() + Inventory::TOTAL_ITEM);
	speech.talking = true;
	speech.Obtain("SpeechText//Obtain.txt", false, inventory.inventory.getItem(inventory.InvCount)->getName());
	inventory.inventory.UseItem(inventory.InvCount);
	inventory.showInvent = false;
	}
	PlaceItemState = false;
	}
	else if (player->PlayerDirRight())
	{
	if (m_itemMap->getTile(player->getPosition().x + 1, floor(player->getPosition().y)) < 0 && m_tileMap->getTile(player->getPosition().x + 1, floor(player->getPosition().y)) < 0)
	{
	m_itemMap->SetTile(player->getPosition().x + 1, floor(player->getPosition().y), inventory.inventory.getItem(inventory.InvCount)->getID() + Inventory::TOTAL_ITEM);
	speech.talking = true;
	speech.Obtain("SpeechText//Obtain.txt", false, inventory.inventory.getItem(inventory.InvCount)->getName());
	inventory.inventory.UseItem(inventory.InvCount);
	inventory.showInvent = false;
	}
	PlaceItemState = false;
	}
	}
	}
	}
	else if (player->getWin() && Key)
	{
	win = true;
	if (commands[ACTION])
	throw - 1;
	}
	else
	{
	player->setWin(false);
	}*/

	if (!speech.talking && InstructText)
	{
		for (int n = 0; n < speech.InstructionText.size(); n++)
		{
			if (speech.InstructionText[n] == InstructFile)
			{
				speech.talking = true;
				const char* temp = speech.InstructionText[n].c_str();
				speech.Dialogue(temp);
				speech.InstructionText[n] = " ";
			}
		}
		InstructFile = "";
		if (temp_InstructFile != "")
		{
			InstructFile = temp_InstructFile;
		}
		else
		{
			InstructText = false;
		}
	}
	if (commands[SPEECH_NEXTLINE] && speech.talking)
	{
		speech.KeyPressed = true;
	}

	for (int count = 0; count < NUM_COMMANDS; ++count)
		commands[count] = false;
}
#undef item

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

TileMap* GameModel::getItemMap()
{
	return m_itemMap;
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

PlayerCharacter* GameModel::getPlayer()
{
	return player;
}

Mesh* GameModel::getPlayerMesh()
{
	return meshPlayer[ModelSwitch - 1];
}

Mesh* GameModel::getAIMesh(int modelSwitch)
{
	return meshPlayer[modelSwitch - 1];
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

string GameModel::GetTextSpeech()
{
	return speech.GetText();
}

int GameModel::GetLineParagraph()
{
	return speech.GetParagraphLine();
}

void GameModel::MeshSpeech()
{
	meshSpeech[PLAYERB_FACE] = MeshBuilder::GenerateText("MainBoyFace", 4, 4);
	meshSpeech[PLAYERB_FACE]->textureID[0] = LoadTGA("Image//Sprite//Face//MainBFace.tga");

	meshSpeech[PLAYERG_FACE] = MeshBuilder::GenerateText("MainGirlFace", 2, 4);
	meshSpeech[PLAYERG_FACE]->textureID[0] = LoadTGA("Image//Sprite//Face//MainGFace.tga");

	meshSpeech[BUTLER_FACE] = MeshBuilder::GenerateText("ButlerFace", 1, 1);
	meshSpeech[BUTLER_FACE]->textureID[0] = LoadTGA("Image//Sprite//Face//ButlerFace.tga");

	meshSpeech[CAT_FACE] = MeshBuilder::GenerateText("CatFace", 2, 4);
	meshSpeech[CAT_FACE]->textureID[0] = LoadTGA("Image//Sprite//Face//CatFace.tga");

	meshSpeech[CHARO_FACE] = MeshBuilder::GenerateText("CharoFace", 1, 1);
	meshSpeech[CHARO_FACE]->textureID[0] = LoadTGA("Image//Sprite//Face//CharoFace.tga");

	meshSpeech[CLOWN_FACE] = MeshBuilder::GenerateText("ClownFace", 1, 1);
	meshSpeech[CLOWN_FACE]->textureID[0] = LoadTGA("Image//Sprite//Face//ClownFace.tga");

	meshSpeech[DARK_FACE] = MeshBuilder::GenerateText("DarkFace", 1, 1);
	meshSpeech[DARK_FACE]->textureID[0] = LoadTGA("Image//Sprite//Face//DarkFace.tga");

	meshSpeech[EYES_FACE] = MeshBuilder::GenerateText("EyesFace", 1, 1);
	meshSpeech[EYES_FACE]->textureID[0] = LoadTGA("Image//Sprite//Face//EyesFace.tga");

	meshSpeech[GLOW_FACE] = MeshBuilder::GenerateText("GlowFace", 1, 1);
	meshSpeech[GLOW_FACE]->textureID[0] = LoadTGA("Image//Sprite//Face//GlowFace.tga");

	meshSpeech[HORN_FACE] = MeshBuilder::GenerateText("HornFace", 1, 1);
	meshSpeech[HORN_FACE]->textureID[0] = LoadTGA("Image//Sprite//Face//HornFace.tga");

	meshSpeech[MASK_FACE] = MeshBuilder::GenerateText("MaskFace", 1, 1);
	meshSpeech[MASK_FACE]->textureID[0] = LoadTGA("Image//Sprite//Face//MaskFace.tga");

	meshSpeech[NOEYES_FACE] = MeshBuilder::GenerateText("NoEyesFace", 1, 1);
	meshSpeech[NOEYES_FACE]->textureID[0] = LoadTGA("Image//Sprite//Face//NoEyesFace.tga");

	meshSpeech[SKELETON_FACE] = MeshBuilder::GenerateText("SkeletonFace", 1, 1);
	meshSpeech[SKELETON_FACE]->textureID[0] = LoadTGA("Image//Sprite//Face//SkeletonFace.tga");

	meshSpeech[TURBAN_FACE] = MeshBuilder::GenerateText("TurbanFace", 1, 1);
	meshSpeech[TURBAN_FACE]->textureID[0] = LoadTGA("Image//Sprite//Face//TurbanFace.tga");

	meshSpeech[WITCH_FACE] = MeshBuilder::GenerateText("WitchFace", 1, 1);
	meshSpeech[WITCH_FACE]->textureID[0] = LoadTGA("Image//Sprite//Face//WitchFace.tga");

	meshSpeech[TEXTBOX] = MeshBuilder::GenerateText("Textbox", 1, 1);
	meshSpeech[TEXTBOX]->textureID[0] = LoadTGA("Image//Sprite//Textbox.tga");
}

Mesh* GameModel::getFaceMesh()
{
	return meshSpeech[ModelSwitch - 1];
}

Mesh* GameModel::getSpeechMesh()
{
	return meshSpeech[TEXTBOX];
}

bool GameModel::getwin()
{
	return win;
}

int GameModel::getKeys()
{
	totalKey = 0;
	for (int ccount = 0; ccount < m_itemMap->getMapWidth(); ++ccount)
	{
		for (int rcount = 0; rcount < m_itemMap->getMapHeight(); ++rcount)
		{
			if (m_itemMap->getTile(ccount , rcount) == inventory.inventory.KEY )
				totalKey++;
		}
	}

	return totalKey;
}
