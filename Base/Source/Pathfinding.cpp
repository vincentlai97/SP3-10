#include "Pathfinding.h"

#include <algorithm>

Vector3 _start, _end, _current;
TileMap *_tileMap;
std::vector<PathfindingNode *> open;
std::vector<PathfindingNode *> closed;
PathfindingNode *__start, *__current;
std::vector<Vector3> path;

int PathfindingNode::h_score()
{
	return abs(_end.x - position.x) + abs(_end.y - position.y);
}

int PathfindingNode::f_score()
{
	return h_score() + g_score;
}

std::vector<Vector3> Pathfinding::Pathfind(Vector3 start, Vector3 end, const TileMap* tileMap)
{
	if (start == end) { path.clear(); return path; }
	_start = start;
	_end = end;
	_tileMap = new TileMap(*tileMap);
	open.clear();
	closed.clear();
	PathfindingNode *node = new PathfindingNode(start);
	open.push_back(node);
	_current = node->position;
	while (_current != _end && open.size() != 0) Search();
	__start = node;
	__current = closed.back();
	CreatePath();
	return path;
}

void Pathfinding::Search()
{
	//Find node with smallest g_score
	PathfindingNode *current = new PathfindingNode(_start);
	for (std::vector<PathfindingNode *>::iterator it = open.begin(); it != open.end(); ++it)
	{
		if ((*it)->f_score() <= current->f_score())
			current = *it;
	}

	//Remove node from open and add into closed
	open.erase(std::remove(open.begin(), open.end(), current), open.end());
	closed.push_back(current);

	_current = current->position;

	//Deal with adjacent nodes
	for (int x = -1; x < 2; ++x)
	{
		for (int y = -1; y < 2; ++y)
		{
			if (abs(x) != abs(y))
			{
				if (current->position.x + x < 0 || current->position.x + x >= _tileMap->getMapWidth()
					|| current->position.y + y < 0 || current->position.y + y >= _tileMap->getMapHeight()); //Check out of bounds
				else if (_tileMap->getTile(current->position.x + x, current->position.y + y) >= 0); //Check for obstacles
				else
				{
					bool exists = false;
					for (std::vector<PathfindingNode *>::iterator it = open.begin(); it != open.end(); ++it)
					{
						if (*(*it) == current->position + Vector3(x, y, 0)) //Check if already found in open list
						{
							if ((current->g_score + 1) < (*it)->g_score)
							{
								(*it)->parent = current;
								(*it)->g_score = current->g_score + 1;
							}
							exists = true;
							break;
						}
					}
					if (!exists)
					{
						PathfindingNode *node = new PathfindingNode(current->position + Vector3(x, y, 0));
						node->parent = current;
						node->g_score = current->g_score + 1;
						open.push_back(node);
					}
				}
			}
		}
	}
}

void Pathfinding::CreatePath()
{
	path.clear();
	path.push_back(_end);
	while (__current != __start)
	{
		path.push_back(__current->position);
		__current = __current->parent;
	}
}