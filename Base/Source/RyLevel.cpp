#include "RyLevel.h"

RyLevel::RyLevel()
{
}

RyLevel::~RyLevel()
{
}

void RyLevel::Init()
{
	GameModel::Init();

	m_tileMap = new TileMap();
	m_tileMap->Init(25, 64, 32, worldWidth, worldHeight);
	m_tileMap->LoadMap("Image//Where.csv");

	m_itemMap = new TileMap();
	m_itemMap->Init(25, 64, 32, worldWidth, worldHeight);
	m_itemMap->LoadMap("Image//WhereItem.csv");

	GameModel::getKeys();

	GameModel::setLaser();

	player = new PlayerCharacter(Vector3(5, 3, 0));
}

void RyLevel::Update(double dt)
{
	GameModel::Update(dt);
	if (GameModel::getwin())
		if (GameModel::getNext())
		{
			if (GameModel::getDead())
				throw 6;
			else
				throw -1;
		}

}
