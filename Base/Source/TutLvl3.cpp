#include "TutLvl3.h"


TutLvl3::TutLvl3()
{
}


TutLvl3::~TutLvl3()
{
}

void TutLvl3::Init()
{
	Model::Init();
	GameModel::Init();

	m_tileMap = new TileMap();
	m_tileMap->Init(25, 32, 24, worldWidth, worldHeight);
	m_tileMap->LoadMap("Image//Tutorial3.csv");

	m_itemMap = new TileMap();
	m_itemMap->Init(25, 32, 24, worldWidth, worldHeight);
	m_itemMap->LoadMap("Image//Tutorial3Item.csv");

	GameModel::getKeys();

	player = new PlayerCharacter(Vector3(2, 16, 0));
}

void TutLvl3::Update(double dt)
{
	GameModel::Update(dt);
	if (GameModel::getwin()) throw 3;
	//if (commands[ACTION])
	//throw 1;
}