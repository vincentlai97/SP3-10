#include "TutLvl3.h"
#define itemTouched(character) m_itemMap->getTile(character->getPosition().x, character->getPosition().y)

TutLvl3::TutLvl3()
{
}


TutLvl3::~TutLvl3()
{
}

void TutLvl3::Init()
{
	GameModel::Init();

	m_tileMap = new TileMap();
	m_tileMap->Init(25, 32, 24, worldWidth, worldHeight);
	m_tileMap->LoadMap("Image//Tutorial3.csv");

	m_itemMap = new TileMap();
	m_itemMap->Init(25, 32, 24, worldWidth, worldHeight);
	m_itemMap->LoadMap("Image//Tutorial3Item.csv");

	GameModel::getKeys();
	GameModel::setLaser();

	player = new PlayerCharacter(Vector3(2, 17, 0));

	InstructFile = "SpeechText//Instruction//AI.txt";
	InstructText = true;

	m_gameState = GAME_STATE::SPEECH;

	AI* Aina = new AI(Vector3(18, 17, 0), 10, NULL, Vector3(5, 0, 0));
	AIList.push_back(Aina);

	AI* Cina = new AI(Vector3(29, 17, 0), 6, NULL, Vector3(0, -5, 0));
	AIList.push_back(Cina);
}

void TutLvl3::Update(double dt)
{
	
	if (!speech.talking && !InstructText)
	{
		for (int n = 0; n < 10; n++)
		{
			if (inventory.inventory.getItem(n)->getID() == 1)
			{
				int temp = 0;
				//speech
				InstructFile = "SpeechText//Instruction//OpenInventory.txt";
				InstructText = true;
				for (int n = 0; n < speech.InstructionText.size(); n++)
				{
					if (speech.InstructionText[n] == InstructFile && m_gameState)
					{
						m_gameState = GAME_STATE::SPEECH;
						temp++;
					}
				}
				if (temp == 0)
				{
					InstructText = false;
				}
			}
		}
	}


	GameModel::Update(dt);
	if (GameModel::getwin())
		if (GameModel::getNext())
		{
			if (GameModel::getDead())
				throw 2;
			else
			{
				GameModel::updateHighscore(2);
				throw 3;
			}
		}

		

	
}
