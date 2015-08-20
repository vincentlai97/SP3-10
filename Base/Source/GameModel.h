#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include "Model.h"

#include "TileMap.h"

#define worldWidth 32
#define worldHeight 24

class GameModel : public Model
{
public:
	enum COMMANDS {
		MOVE_UP,
		MOVE_DOWN,
		MOVE_LEFT,
		MOVE_RIGHT,
		NUM_COMMANDS,
	};

private:
	Mesh *tile;

	TileMap *m_tileMap;
	float m_mapOffset_x;
	float m_mapOffset_y;

public:
	GameModel();
	~GameModel();

	virtual void Init();
	virtual void Update(double dt);
	virtual void setCommands(int command);

	int getWorldWidth() { return worldWidth; }
	int getWorldHeight() { return worldHeight; }

	Mesh* getTileMesh();
	TileMap* getTileMap();
	void getOffset(float& mapOffset_x, float& mapOffset_y);

	bool checkLineOfSight(Vector3 point, Vector3 target, const TileMap* tileMap);

	Mesh* foo;
	Vector3 pos1;
	Vector3 pos2;

	std::vector<int> floorTiles;

	Mesh *shadow;
};

#endif