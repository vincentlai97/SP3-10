#include "jslvl2.h"

jslvl2::jslvl2()
{
}

jslvl2::~jslvl2()
{
}

void jslvl2::Init()
{
	GameModel::Init();

	m_tileMap = new TileMap();
	m_tileMap->Init(25, 32, 24, worldWidth, worldHeight);
	m_tileMap->LoadMap("Image//jslvl2.csv");

	m_itemMap = new TileMap();
	m_itemMap->Init(25, 32, 24, worldWidth, worldHeight);
	m_itemMap->LoadMap("Image//jslvl2Item.csv");

	GameModel::getKeys();

	GameModel::setLaser();

	player = new PlayerCharacter(Vector3(5, 3, 0));
}

void jslvl2::Update(double dt)
{
	GameModel::Update(dt);
	if (GameModel::getwin())
		if (GameModel::getNext())
			throw 6;
}
