#include "GameModel.h"

#include "MeshBuilder.h"
#include "LoadTGA.h"
#include "Pathfinding.h"
#include "LoS.h"

#include <sstream> 
#include <fstream>
#include <algorithm>

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
	ModelSwitch = 0;

	m_gameState = GAME_STATE::IDLE;

	tile = MeshBuilder::GenerateText("tiles", 32, 32);
	tile->textureID[0] = LoadTGA("Image//tile.tga");

	winMesh = MeshBuilder::GenerateText("tiles", 1, 1);
	winMesh->textureID[0] = LoadTGA("Image//win.tga");

	lose = MeshBuilder::GenerateText("tiles", 1, 1);
	lose->textureID[0] = LoadTGA("Image//lose.tga");

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

	PlaceItemState = false;

	AIList.clear();

	win = false;
	touchdoor = false;
	numKey = 0;
	//getKeys();

	goNext = false;

	died = false;

	steps = 0;

	for (int count = 0; count < SPEECH_TYPE::NUM_SPEECH; ++count)
	{
		meshSpeech[count] = new Mesh("null");
		meshSpeech[count]->textureID[0] = 0;
	}
	MeshSpeech();

	speech.Textfile("SpeechText//CharacterFile.txt", true);
	speech.Textfile("SpeechText//HowToPlayFile.txt", false);

	/*InstructFile = "SpeechText//Instruction//MoveCharacter.txt";
	InstructText = true;*/
}

enum AITARGET {
	PLAYER,
	HOLOGRAM,
};
AITARGET AITarget;

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
		if (!player->getAcceleration().IsZero()) { m_gameState = GAME_STATE::PLAYER_TURN; steps++; break; }

		//Open inventory
		if (commands[INVENT]) { m_gameState = GAME_STATE::INVENTORY; break; }

		//Item interaction with player
		if (itemTouched(player) >= 0 && itemTouched(player) < Inventory::TOTAL_ITEM)
		{
			if (itemTouched(player) == Inventory::KEY)
				numKey++;

			inventory.inventory.AddToInvent(itemTouched(player));
			speech.talking = true;
			speech.Obtain("SpeechText//Obtain.txt", true, inventory.inventory.DefaultItem[itemTouched(player)].getName());
			m_itemMap->SetTile(player->getPosition().x, player->getPosition().y, -1);
			m_gameState = SPEECH;
			break;
		}

		//Item interaction with enemies
		for (std::vector<AI *>::iterator it = AIList.begin(); it != AIList.end(); ++it)
		{
			if (itemTouched((*it)) > Inventory::TOTAL_ITEM && itemTouched((*it)) < Inventory::TOTAL_ITEM * 2)
			{
				if (itemTouched((*it)) == Inventory::TRAP + Inventory::TOTAL_ITEM)
				{
					(*it)->setAiActive(false);
					m_itemMap->SetTile((*it)->getPosition().x, (*it)->getPosition().y, -1);
				}
			}
		}

		//Initiate character speech
		if (commands[SPEECH_NEXTLINE])
		{
			speech.talking = true;
			const char* temp = speech.CharacterText[ModelSwitch].c_str();
			speech.Dialogue(temp);
			m_gameState = GAME_STATE::SPEECH;
			break;
		}

		//Laser switch
		if (commands[ACTION])
		{
			if (!player->getDirection().IsZero())
			{
				Vector3 switchPosition = player->getPosition() + player->getDirection();
				if (m_tileMap->getTile(switchPosition.x, switchPosition.y) == 299)
					laserswitch();
			}
		}

		if ((numKey == totalKey && touchdoor) || died)
			win = true;

		if (commands[ACTION] && win)
			goNext = true;

		if (!player->getDirection().IsZero())
		{
			if (m_itemMap->getTile(player->getPosition().x, player->getPosition().y) == 50 ||
				m_itemMap->getTile(player->getPosition().x, player->getPosition().y) == 183 ||
				m_itemMap->getTile(player->getPosition().x, player->getPosition().y) == 176 ||
				m_itemMap->getTile(player->getPosition().x, player->getPosition().y) == 88)
				touchdoor = true;
			else
				touchdoor = false;
		}

		break;
	case GAME_STATE::PLAYER_TURN:
		player->Update(dt, m_tileMap);
		if (player->getVelocity().IsZero())
		{
			m_gameState = GAME_STATE::AI_TURN;
			for (std::vector<AI *>::iterator it = AIList.begin(); it != AIList.end(); ++it)
			{
				if (checkLineOfSight((*it)->getPosition(), player->getPosition(), m_tileMap))
				{
					(*it)->UpdatePath(player->getPosition(), m_tileMap, ModelSwitch);
					AITarget = AITARGET::PLAYER;
				}
				else if (checkLineOfSight((*it)->getPosition(), hologram, m_tileMap))
				{
					(*it)->UpdatePath(hologram, m_tileMap, ModelSwitch);
					AITarget = AITARGET::HOLOGRAM;
				}
				else
				{
					if (AITarget == AITARGET::HOLOGRAM) (*it)->SetStateReturning();
					(*it)->UpdatePath(player->getPosition(), m_tileMap, ModelSwitch);
				}
			}
		}
		break;
	case GAME_STATE::AI_TURN:
	{
		int AIStopped = 0;
		for (std::vector<AI *>::iterator it = AIList.begin(); it != AIList.end(); ++it)
		{
			if ((*it)->getAiActive())
			{
				(*it)->Update(dt);
				if ((*it)->getSpot() == true)
					ModelSwitch = 0;
				if ((*it)->getPosition() == player->getPosition())
					died = true;
			}
			if (AIList[0]->getVelocity().IsZero())
				AIStopped++;
		}
		if (AIStopped == AIList.size())
			m_gameState = GAME_STATE::IDLE;
	}
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
				ModelSwitch = inventory.inventory.getItem(inventory.InvCount)->getID() - 4;
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
			if (commands[COMMANDS::MOVE_UP]) player->idleUp();
			if (commands[COMMANDS::MOVE_DOWN]) player->idleDown();
			if (commands[COMMANDS::MOVE_LEFT]) player->idleLeft();
			if (commands[COMMANDS::MOVE_RIGHT]) player->idleRight();
			if (commands[COMMANDS::ACTION])
			{
				Vector3 placePosition = player->getPosition() + player->getDirection();
				if (m_itemMap->getTile(placePosition.x, placePosition.y) < 0)
				{
					m_itemMap->SetTile(placePosition.x, placePosition.y, inventory.inventory.getItem(inventory.InvCount)->getID() + Inventory::TOTAL_ITEM);
					if (inventory.inventory.getItem(inventory.InvCount)->getID() == Inventory::MIRROR) mirror.push_back(placePosition);
					if (inventory.inventory.getItem(inventory.InvCount)->getID() == Inventory::HOLOGRAM) hologram = placePosition;
				}
				speech.talking = true;
				speech.Obtain("SpeechText//Obtain.txt", false, inventory.inventory.getItem(inventory.InvCount)->getName());
				inventory.inventory.UseItem(inventory.InvCount);
				m_gameState = GAME_STATE::SPEECH;
			}
		}
		break;
	case GAME_STATE::SPEECH:
		if (!speech.talking && InstructText)
		{
			for (int n = 0; n < speech.InstructionText.size(); n++)
			{
				cout << speech.InstructionText[n] << endl;
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

		if (speech.talking) speech.Update(dt);
		else m_gameState = GAME_STATE::IDLE;
		break;
	}

	m_mapOffset_x = player->getPosition().x - (float)m_tileMap->getNumOfTilesWidth() / 2.f;
	m_mapOffset_x = Math::Clamp(m_mapOffset_x, 0.f, (float)(m_tileMap->getMapWidth() - m_tileMap->getNumOfTilesWidth()));

	m_mapOffset_y = player->getPosition().y - (float)m_tileMap->getNumOfTilesHeight() / 2.f;
	m_mapOffset_y = Math::Clamp(m_mapOffset_y, 0.f, (float)(m_tileMap->getMapHeight() - m_tileMap->getNumOfTilesHeight()));

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
	return meshPlayer[ModelSwitch];
}

std::vector<AI *> GameModel::getAIList()
{
	return AIList;
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
	return meshSpeech[ModelSwitch];
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
			if (m_itemMap->getTile(ccount, rcount) == inventory.inventory.KEY)
				totalKey++;
		}
	}

	return totalKey;
}

void GameModel::laserswitch()
{
	for (int ccount = 0; ccount < m_tileMap->getMapWidth(); ++ccount)
	{
		for (int rcount = 0; rcount < m_tileMap->getMapHeight(); ++rcount)
		{
			if (m_tileMap->getTile(ccount, rcount) == -2)
				m_tileMap->SetTile(ccount, rcount, 301);
			else if (m_tileMap->getTile(ccount, rcount) == 301)
				m_tileMap->SetTile(ccount, rcount, -2);

			if (m_tileMap->getTile(ccount, rcount) == -3)
				m_tileMap->SetTile(ccount, rcount, 302);
			else if (m_tileMap->getTile(ccount, rcount) == 302)
				m_tileMap->SetTile(ccount, rcount, -3);

			if (m_tileMap->getTile(ccount, rcount) == -4)
				m_tileMap->SetTile(ccount, rcount, 303);
			else if (m_tileMap->getTile(ccount, rcount) == 303)
				m_tileMap->SetTile(ccount, rcount, -4);

			if (m_tileMap->getTile(ccount, rcount) == 313)
				m_tileMap->SetTile(ccount, rcount, 312);
			else if (m_tileMap->getTile(ccount, rcount) == 312)
				m_tileMap->SetTile(ccount, rcount, 313);
		}
	}
}

void GameModel::setLaser()
{
	for (int ccount = 0; ccount < m_tileMap->getMapWidth(); ++ccount)
	{
		for (int rcount = 0; rcount < m_tileMap->getMapHeight(); ++rcount)
		{
			if (m_tileMap->getTile(ccount, rcount) == 50){
				m_itemMap->SetTile(ccount, rcount, 50);
				m_tileMap->SetTile(ccount, rcount, -1);
			}
			else if (m_tileMap->getTile(ccount, rcount) == 183){
				m_itemMap->SetTile(ccount, rcount, 183);
				m_tileMap->SetTile(ccount, rcount, -1);
			}
			else if (m_tileMap->getTile(ccount, rcount) == 176){
				m_itemMap->SetTile(ccount, rcount, 176);
				m_tileMap->SetTile(ccount, rcount, -1);
			}
			else if (m_tileMap->getTile(ccount, rcount) == 88){
				m_itemMap->SetTile(ccount, rcount, 88);
				m_tileMap->SetTile(ccount, rcount, -1);
			}


			if (m_tileMap->getTile(ccount, rcount) == 300)
			{
				for (int i = ccount - 1; i > 0; --i)
				{
					if ((m_tileMap->getTile(i, rcount) < 0 || m_tileMap->getTile(i, rcount) == 301) && m_tileMap->getTile(i, rcount) != 300)
					{
						if (m_tileMap->getTile(i, rcount) == 301)
							m_tileMap->SetTile(i, rcount, 303);
						else if (m_tileMap->getTile(i, rcount) == -2)
							m_tileMap->SetTile(i, rcount, 313);
						else
							m_tileMap->SetTile(i, rcount, 302);
					}
					else
						break;
				}
				for (int i = ccount + 1; i < m_tileMap->getMapWidth(); ++i)
				{
					if ((m_tileMap->getTile(i, rcount) < 0 || m_tileMap->getTile(i, rcount) == 301) && m_tileMap->getTile(i, rcount) != 300)
					{
						if (m_tileMap->getTile(i, rcount) == 301)
							m_tileMap->SetTile(i, rcount, 303);
						else if (m_tileMap->getTile(i, rcount) == -2)
							m_tileMap->SetTile(i, rcount, 313);
						else
							m_tileMap->SetTile(i, rcount, 302);
					}
					else
						break;

				}
				for (int i = rcount - 1; i > 0; --i)
				{
					if ((m_tileMap->getTile(ccount, i) < 0 || m_tileMap->getTile(ccount, i) == 302) && m_tileMap->getTile(ccount, i) != 300)
					{
						if (m_tileMap->getTile(ccount, i) == 302)
							m_tileMap->SetTile(ccount, i, 303);
						else if (m_tileMap->getTile(ccount, i) == -3)
							m_tileMap->SetTile(ccount, i, 312);
						else
							m_tileMap->SetTile(ccount, i, 301);
					}
					else
						break;
				}
				for (int i = rcount + 1; i < m_tileMap->getMapHeight(); ++i)
				{
					if ((m_tileMap->getTile(ccount, i) < 0 || m_tileMap->getTile(ccount, i) == 302) && m_tileMap->getTile(ccount, i) != 300)
					{
						if (m_tileMap->getTile(ccount, i) == 302)
							m_tileMap->SetTile(ccount, i, 303);
						else if (m_tileMap->getTile(ccount, i) == -3)
							m_tileMap->SetTile(ccount, i, 312);
						else
							m_tileMap->SetTile(ccount, i, 301);
					}
					else
						break;
				}
			}
		}
	}
}

bool GameModel::getNext()
{
	return goNext;
}

bool GameModel::getTouchDoor()
{
	return touchdoor;
}

int  GameModel::getNumKeys()
{
	return numKey;
}
int GameModel::getTotalKeys()
{
	return totalKey;
}

Mesh* GameModel::getWinMesh()
{
	return winMesh;
}

bool GameModel::getDead()
{
	return died;
}

Mesh* GameModel::getLoseMesh()
{
	return lose;
}

int GameModel::getSteps()
{
	return steps;
}

bool GameModel::updateHighscore(int level)
{
	ifstream ifs;
	string buffer;

	vector <int> highscores;
	std::vector<string> text;

	ifs.open("highscore.txt");

	stringstream ss;
	int thelvl = level + 1;
	ss << "Level" << thelvl;

	int position = 0;

	if (ifs.is_open())
	{
		int temp = 0;
		while (!ifs.eof())
		{
			getline(ifs, buffer);
			text.push_back(buffer);
			++temp;
			if (buffer == ss.str())
			{
				position = temp;
				for (int count = 0; count < 5; ++count)
				{
					getline(ifs, buffer);
					highscores.push_back(stoi(buffer));
					text.push_back(buffer);
				}
			}
		}
		ifs.close();
	}

	highscores.push_back(steps);
	std::sort(highscores.begin(), highscores.end());

	for (int count = 0; count < 5; ++count)
	{
		ss.str("");
		ss << highscores[count];
		text[position + count] = ss.str();
	}

	ofstream writer;
	writer.open("highscore.txt");
	int count = 0;

	for (vector<string>::iterator it = text.begin(); it != text.end(); ++it)
	{
		writer << *it << endl;
	}

	writer.close();

	//vector <int> 

	//for (int i = 1; i < 5; i++)
	//{
	//	for (int k = 0; k < 5 - i; k++)
	//	{
	//		int scores = 0;
	//		scores = stoi(highscores[position + k + 1]);

	//		int scores2 = 0;
	//		scores2 = stoi(highscores[position + k + 2]);

	//		if (scores > scores2)
	//		{
	//			//Swap around
	//			string temp = highscores[position + k + 1];
	//			highscores[position + k + 1] = highscores[position + k + 2];
	//			highscores[position + k + 2] = temp;
	//		}
	//	}
	//}

	//for (int i = position)

	//int lowest = 999999;
	//int lowestPos = position + 1;
	////find position in the lvl to put
	//for (int i = position + 1; i < position + 6; i++)
	//{
	//	int scores = 0;
	//	scores = stoi(highscores[i]);

	//	if (lowest > scores && scores != 999999)
	//	{
	//		lowest = scores;
	//		lowestPos = i;
	//	}
	//}

	//overwrite
	/*if (lowestPos == position + 6)
	{
		string a = static_cast<ostringstream*>(&(ostringstream() << steps))->str();
		highscores[lowestPos] = a;
		wrote = true;
	}
	else
	{
		for (int i = lowestPos; i < (position + 6 - lowestPos); i++)
		{
			highscores[i + 1] = highscores[i];
		}

		string a = static_cast<ostringstream*>(&(ostringstream() << steps))->str();
		highscores[lowestPos] = a;
		wrote = true;
	}*/

	return true;
}
