#include "NDLvl.h"

#pragma comment(lib, "irrKlang.lib")
using namespace irrklang;

//ISoundEngine* BGM1 = createIrrKlangDevice(ESOD_AUTO_DETECT, ESEO_MULTI_THREADED | ESEO_LOAD_PLUGINS | ESEO_USE_3D_BUFFERS);

NDlvl::NDlvl()
{
}


NDlvl::~NDlvl()
{
}

void NDlvl::Init()
{
	GameModel::Init();

	m_tileMap = new TileMap();
	m_tileMap->Init(25, 32, 24, worldWidth, worldHeight);
	m_tileMap->LoadMap("Image//Tutorial1.csv");

	m_itemMap = new TileMap();
	m_itemMap->Init(25, 32, 24, worldWidth, worldHeight);
	m_itemMap->LoadMap("Image//BlankItem.csv");

	GameModel::getKeys();
	GameModel::setLaser();

	player = new PlayerCharacter(Vector3(11, 12 , 0));

	//speech
	InstructFile = "SpeechText//Instruction//MoveCharacter.txt";
	InstructText = true;

	m_gameState = GAME_STATE::SPEECH;
}

void NDlvl::Update(double dt)
{
	GameModel::Update(dt);
	if (GameModel::getwin())
		if (GameModel::getNext())
		{
			if (GameModel::getDead())
				throw 0;
			else
			{
				GameModel::updateHighscore(0);
				throw 1;
			}
		}
}

