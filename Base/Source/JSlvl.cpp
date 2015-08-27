#include "JSlvl.h"

JSlvl::JSlvl()
{
}

JSlvl::~JSlvl()
{
}

void JSlvl::Init()
{
	Model::Init();
	GameModel::Init();

	m_tileMap = new TileMap();
	m_tileMap->Init(25, 40, 20, worldWidth, worldHeight);
	m_tileMap->LoadMap("Image//junsenlvl.csv");

	m_itemMap = new TileMap();
	m_itemMap->Init(25, 40, 20, worldWidth, worldHeight);
	m_itemMap->LoadMap("Image//junsenlvlitem.csv");

	GameModel::getKeys();

	GameModel::setLaser();
	
	player = new PlayerCharacter(Vector3(16, 3, 0));
}

void JSlvl::Update(double dt)
{
	GameModel::Update(dt);
	if(GameModel::getwin()) throw 1;
		//if (commands[ACTION])
			//throw 1;
}
