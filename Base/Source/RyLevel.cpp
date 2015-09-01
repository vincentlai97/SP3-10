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
	inventory.inventory.AddToInvent(inventory.inventory.SKELETON_BOX);
	inventory.inventory.AddToInvent(inventory.inventory.TRAP);
	inventory.inventory.AddToInvent(inventory.inventory.MIRROR);

	AI* Aina = new AI(Vector3(28, 25, 0), 10, NULL, Vector3(7, 0, 0));
	AIList.push_back(Aina);

	AI* Bina = new AI(Vector3(4, 24, 0), 5, NULL, Vector3(5, 0, 0));
	AIList.push_back(Bina);
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
			{
				GameModel::updateHighscore(6);
				throw -1;
			}
		}

}
