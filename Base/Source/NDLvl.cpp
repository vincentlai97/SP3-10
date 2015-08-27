#include "NDLvl.h"

NDlvl::NDlvl()
{
}


NDlvl::~NDlvl()
{
}

void NDlvl::Init()
{
	Model::Init();
	GameModel::Init();

	m_tileMap = new TileMap();
	m_tileMap->Init(25, 32, 24, worldWidth, worldHeight);
	m_tileMap->LoadMap("Image//Tutorial1.csv");

	m_itemMap = new TileMap();
	m_itemMap->Init(25, 32, 24, worldWidth, worldHeight);
	m_itemMap->LoadMap("Image//BlankItem.csv");

	GameModel::getKeys();

	player = new PlayerCharacter(Vector3(11, 12 , 0));
}

void NDlvl::Update(double dt)
{
	GameModel::Update(dt);
	if (GameModel::getwin()) throw 1;
	//if (commands[ACTION])
	//throw 1;
}