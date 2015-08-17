#ifndef GAMEMODEL2D_H
#define GAMEMODEL2D_H

#include "Model.h"

#include "TileMap.h"
#include "PlayerCharacter.h"

#include <vector>

class GameModel2D : public Model
{
public:
	enum COMMANDS {
		MOVE_UP,
		MOVE_DOWN,
		MOVE_LEFT,
		MOVE_RIGHT,
		JUMP,
		NUM_COMMANDS,
	};

protected:
	enum GEOMETRY_TYPE {
		TEXT,
		BACKGROUND,
		TILE,
		PLAYER,
		MOBS,
		TOTAL_GEOMETRY,
	};

	Mesh* meshList[TOTAL_GEOMETRY];

	TileMap* m_tileMap;
	float m_mapOffset_x;
	float m_mapOffset_y;

	PlayerCharacter *player;
	std::vector<Character *> mobsList;

	int score;

public:

	virtual void Init();
	virtual void Update(double dt);

	void setCommands(int command);

	Mesh* getTextMesh();

	Mesh* getBackgroundMesh();

	void getOffset(float& mapOffset_x, float& mapOffset_y);
	TileMap* getTileMap();
	Mesh* getTileMesh();

	PlayerCharacter* getPlayer();
	Mesh* getPlayerMesh();

	std::vector<Character *> getMobsList();
	Mesh* getMobsMesh();

	int getScore();

};

#endif