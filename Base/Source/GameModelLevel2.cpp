#include "GameModelLevel2.h"

GameModelLevel2::GameModelLevel2()
{
}

GameModelLevel2::~GameModelLevel2()
{
}

void GameModelLevel2::Init()
{
	Model::Init();
	GameModel2D::Init();

	m_tileMap = new TileMap();
	m_tileMap->Init(32, 96, 25, 32, 25);
	m_tileMap->LoadMap("Image//map2.csv");

	player = new PlayerCharacter(Vector3(2, 2, 0));

	Character *mob = new MouseCharacter(Vector3(16, 3, 0), NULL, -1, player);
	mobsList.push_back(mob);
	mob = new MouseCharacter(Vector3(31, 6, 0), NULL, -1, player);
	mobsList.push_back(mob);
	mob = new MouseCharacter(Vector3(39, 6, 0), NULL, -1, player);
	mobsList.push_back(mob);
	mob = new MouseCharacter(Vector3(40, 6, 0), NULL, -1, player);
	mobsList.push_back(mob);
	mob = new MouseCharacter(Vector3(50, 7, 0), NULL, -1, player);
	mobsList.push_back(mob);
	mob = new MouseCharacter(Vector3(51, 7, 0), NULL, -1, player);
	mobsList.push_back(mob);
	mob = new MouseCharacter(Vector3(60, 4, 0), NULL, -1, player);
	mobsList.push_back(mob);
	mob = new MouseCharacter(Vector3(61, 4, 0), NULL, -1, player);
	mobsList.push_back(mob);
}

void GameModelLevel2::Update(double dt)
{

	GameModel2D::Update(dt);
}
