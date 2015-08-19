#include "GameModel.h"

#include "MeshBuilder.h"
#include "LoadTGA.h"

GameModel::GameModel()
{
}

GameModel::~GameModel()
{
}

void GameModel::Init()
{
	Model::Init();

	for (int count = 0; count < GEOMETRY_TYPE::NUM_GEOMETRY; ++count)
	{
		meshList[count] = new Mesh("null");
		meshList[count]->textureID[0] = 0;
	}

	tile = MeshBuilder::GenerateText("tiles", 32, 32);
	tile->textureID[0] = LoadTGA("Image//tile.tga");

	meshList[PLAYER] = MeshBuilder::GenerateText("player", 8, 16);
	meshList[PLAYER]->textureID[0] = LoadTGA("Image//Player.tga");

	m_tileMap = new TileMap();
	m_tileMap->Init(25, 32, 24, worldWidth, worldHeight);
	m_tileMap->LoadMap("Image//map.csv");

	commands = new bool[NUM_COMMANDS];
	for (int count = 0; count < NUM_COMMANDS; ++count)
		commands[count] = false;

	m_mapOffset_x = 0;
	m_mapOffset_y = 0;
	player = new PlayerCharacter(Vector3 (11, 11, 1));
}

void GameModel::Update(double dt)
{
	if (commands[MOVE_UP]) player->moveUp();
	if (commands[MOVE_DOWN]) player->moveDown();
	if (commands[MOVE_LEFT]) player->moveLeft();
	if (commands[MOVE_RIGHT]) player->moveRight();

	player->Update(dt, m_tileMap);

	for (int count = 0; count < NUM_COMMANDS; ++count)
		commands[count] = false;

}

Mesh *GameModel::getTileMesh()
{
	return tile;
}

void GameModel::setCommands(int command)
{
	if (command >= 0 && command < NUM_COMMANDS)
		commands[command] = true;
}

TileMap* GameModel::getTileMap()
{
	return m_tileMap;
}

PlayerCharacter* GameModel::getPlayer()
{
	return player;
}

Mesh* GameModel::getPlayerMesh()
{
	return meshList[PLAYER];
}

void GameModel::getOffset(float& mapOffset_x, float& mapOffset_y)
{
	mapOffset_x = m_mapOffset_x;
	mapOffset_y = m_mapOffset_y;
}