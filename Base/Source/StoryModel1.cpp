#include "StoryModel1.h"

StoryModel1::StoryModel1()
{
}

StoryModel1::~StoryModel1()
{
}

void StoryModel1::Init()
{
	GameModel::Init();

	m_tileMap = new TileMap();
	m_tileMap->Init(25, 32, 24, worldWidth, worldHeight);
	m_tileMap->LoadMap("Image//mylevel.csv");

	m_itemMap = new TileMap();
	m_itemMap->Init(25, 32, 24, worldWidth, worldHeight);
	m_itemMap->LoadMap("Image//mylevelitems.csv");

	player = new PlayerCharacter(Vector3(4, 20, 0));

	AI *ai = new AI(Vector3(10, 2, 0), 1, NULL, Vector3(0, 7, 0));
	AIList.push_back(ai);

	inventory.inventory.AddToInvent(7);

	GameModel::getKeys();
	GameModel::setLaser();
}

void StoryModel1::Update(double dt)
{
	GameModel::Update(dt);
	if (GameModel::getwin())
		if (GameModel::getNext())
		{
			if (GameModel::getDead())
				throw 3;
			else
			{
				GameModel::updateHighscore(3);
				throw 4;
			}
		}

	if (!speech.talking)
	{
		//speech
		InstructFile = "SpeechText//Instruction//Mirror.txt";
		InstructText = true;
		for (int n = 0; n < speech.InstructionText.size(); n++)
		{
			if (speech.InstructionText[n] == InstructFile)
			{
				m_gameState = GAME_STATE::SPEECH;
			}
		}
	}
}
