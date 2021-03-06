#include "JSlvl.h"

JSlvl::JSlvl()
{
}

JSlvl::~JSlvl()
{
}

void JSlvl::Init()
{
	GameModel::Init();

	m_tileMap = new TileMap();
	m_tileMap->Init(25, 40, 24, worldWidth, worldHeight);
	m_tileMap->LoadMap("Image//junsenlvl.csv");

	m_itemMap = new TileMap();
	m_itemMap->Init(25, 40, 24, worldWidth, worldHeight);
	m_itemMap->LoadMap("Image//junsenlvlitem.csv");

	GameModel::getKeys();
	GameModel::setLaser();
	
	player = new PlayerCharacter(Vector3(16, 3, 0));

	InstructFile = "SpeechText//Instruction//Switch.txt";
	InstructText = true;

	AI* Aina = new AI(Vector3(20, 14, 0), 10, NULL, Vector3(-10, 0, 0));
	AIList.push_back(Aina);

	m_gameState = GAME_STATE::SPEECH;
}

void JSlvl::Update(double dt)
{
	GameModel::Update(dt);
	if (GameModel::getwin()) //throw 5;
		if (GameModel::getNext())
		{
			if (GameModel::getDead())
				throw 4;
			else
			{
				GameModel::updateHighscore(4);
				throw 5;
			}
		}

}
