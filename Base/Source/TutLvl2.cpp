#include "TutLvl2.h"

TutLvl2::TutLvl2()
{
}


TutLvl2::~TutLvl2()
{
}

void TutLvl2::Init()
{
	GameModel::Init();

	m_tileMap = new TileMap();
	m_tileMap->Init(25, 32, 24, worldWidth, worldHeight);
	m_tileMap->LoadMap("Image//Tutorial2.csv");

	m_itemMap = new TileMap();
	m_itemMap->Init(25, 32, 24, worldWidth, worldHeight);
	m_itemMap->LoadMap("Image//Tutorial2Item.csv");

	GameModel::getKeys();
	GameModel::setLaser();

	GameModel::setLaser();

	player = new PlayerCharacter(Vector3(28, 18, 0));

	InstructFile = "SpeechText//Instruction//SeeKey.txt";
	InstructText = true;

	m_gameState = GAME_STATE::SPEECH;
}

void TutLvl2::Update(double dt)
{
	if ((getNumKeys() != getTotalKeys() && getTouchDoor()) && !InstructText)
	{
		InstructFile = "SpeechText//Instruction//BeforeKey.txt";
		InstructText = true;
		for (int n = 0; n < speech.InstructionText.size(); n++)
		{
			if (speech.InstructionText[n] == InstructFile)
			{
				m_gameState = GAME_STATE::SPEECH;
			}
		}
	}

	if ((getNumKeys() == getTotalKeys() && !getTouchDoor()) && !InstructText)
	{
		InstructFile = "SpeechText//Instruction//AfterKey.txt";
		InstructText = true;
		for (int n = 0; n < speech.InstructionText.size(); n++)
		{
			if (speech.InstructionText[n] == InstructFile)
			{
				m_gameState = GAME_STATE::SPEECH;
			}
		}
	}

	GameModel::Update(dt);
	if (GameModel::getwin())
		if (GameModel::getNext())
		{
			if (GameModel::getDead())
				throw 1;
			else
			{
				GameModel::updateHighscore(1);
				throw 2;
			}
		}

}