#ifndef AI_H
#define AI_H

#include "Character.h"

#include <vector>

class AI : public Character
{
public:
	enum AI_STATES
	{
		IDLE,
		RETURNING,
		CHASE,
		NUM_STATES,
	};

private:
	Vector3 m_intialPosition;
	Vector3 waypoint;
	Vector3 m_target;
	int AI_State;
	bool AI_Active;
	std::vector<Vector3> path;
	
public:
	AI(Vector3 initialPosition = Vector3(), Mesh* sprite = NULL, Vector3 waypoint = Vector3());
	~AI();

	void Update(Vector3 playerPos, const TileMap *tileMap);

	Vector3 getPos();
	Mesh* getMesh();

	bool getAiActive();
	void setAiActive(bool AI_Active);

};

#endif