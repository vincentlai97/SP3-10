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

	tile = MeshBuilder::GenerateText("tiles", 32, 32);
	tile->textureID[0] = LoadTGA("Image//tile.tga");

	m_tileMap = new TileMap();
	m_tileMap->Init(25, 32, 24, worldWidth, worldHeight);
	m_tileMap->LoadMap("Image//map.csv");

	m_mapOffset_x = 0;
	m_mapOffset_y = 0;

	foo = MeshBuilder::GenerateSphere("test", Color(), 16, 16, 0.5f);

	commands = new bool[NUM_COMMANDS];
	for (int count = 0; count < NUM_COMMANDS; ++count)
		commands[count] = false;

	pos1.Set(21, 10, 0);
	pos2.Set(25, 12, 0);
	//pos2.Set(21, 12, 0);
	//pos2.Set(14, 19, 0);
	//pos2.Set(14, 5, 0);

	floorTiles.push_back(112);
	floorTiles.push_back(309);
	floorTiles.push_back(402);
	floorTiles.push_back(405);

	shadow = MeshBuilder::GenerateQuad("shadow", Color());
	shadow->textureID[0] = LoadTGA("Image//shadow.tga");
}

bool b_buttonDown = false;

void GameModel::Update(double dt)
{
	if (!b_buttonDown)
	{
		if (commands[COMMANDS::MOVE_UP])
		{
			pos1.y++;
			b_buttonDown = true;
		}
		if (commands[COMMANDS::MOVE_DOWN])
		{
			pos1.y--;
			b_buttonDown = true;
		}
		if (commands[COMMANDS::MOVE_LEFT])
		{
			pos1.x--;
			b_buttonDown = true;
		}
		if (commands[COMMANDS::MOVE_RIGHT])
		{
			pos1.x++;
			b_buttonDown = true;
		}
	}
	else
	{
		b_buttonDown = false;
		for (int count = 0; count < NUM_COMMANDS; ++count)
		{
			if (commands[count])
				b_buttonDown = true;
		}
	}
	std::cout << checkLineOfSight(pos1 + Vector3(0.5f, 0.5f, 0), pos2 + Vector3(0.5f, 0.5f, 0), m_tileMap);
	std::cout << checkLineOfSight(pos2 + Vector3(0.5f, 0.5f, 0), pos1 + Vector3(0.5f, 0.5f, 0), m_tileMap) << std::endl;

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

void GameModel::getOffset(float& mapOffset_x, float& mapOffset_y)
{
	mapOffset_x = m_mapOffset_x;
	mapOffset_y = m_mapOffset_y;
}

bool GameModel::checkLineOfSight(Vector3 point, Vector3 target, const TileMap* tileMap)
{
	if (point == target) return true;
	Vector3 view = (target - point).Normalized();
	if (view.x < 0)
	{
		point += target;
		target = point - target;
		point -= target;
		(view = target - point).Normalize();
	}

	Vector3 temp(point);
	/*float diff_x = ceil(temp.x) - temp.x;
	temp.x = ceil(temp.x);
	temp.y += view.y * diff_x * (1 / view.x);*/
	while (temp.x < floor(target.x))
	{
		if (temp.y - (int) temp.y)
		if (tileMap->getTile(temp.x, floor(temp.y)) > 0)
			return false;
		++temp.x;
		temp.y += view.y * (1 / view.x);
	}

	view = (target - point).Normalized();
	if (view.y < 0)
	{
		point += target;
		target = point - target;
		point -= target;
		(view = target - point).Normalize();
	}

	temp = point;
	/*float diff_y = ceil(temp.y) - temp.y;
	temp.y = ceil(temp.y);
	temp.x += view.x * diff_y * (1 / view.y);*/
	while (temp.y < floor(target.y))
	{
		if (temp.x - (int)temp.x)
		if (tileMap->getTile(floor(temp.x), temp.y) > 0)
			return false;
		++temp.y;
		temp.x += view.x * (1 / view.y);
	}

	return true;
}