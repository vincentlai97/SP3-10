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

	Aina = new AI(Vector3(10, 2, 0), NULL, Vector3(0, 7, 0));
}

void StoryModel1::Update(double dt)
{
	GameModel::Update(dt);
	if (GameModel::getwin()) throw 4;
	//if (commands[ACTION])
	//throw 1;
}
