#pragma once

#include "Vector3.h"
#include <vector>
#include "TileMap.h"

struct PathfindingNode
{
	Vector3 position;
	PathfindingNode *parent;
	float g_score;

	PathfindingNode(Vector3 position = Vector3())
		: position(position)
		, parent(NULL)
		, g_score(0)
	{
	}

	bool operator==(Vector3 pos)
	{
		return this->position == pos;
	}

	int h_score();
	int f_score();
};

class Pathfinding
{
private:
	static void Search(const TileMap* tileMap);
	static void CreatePath();

public:
	static std::vector<Vector3> Pathfind(Vector3 start, Vector3 end, const TileMap* tileMap);

};