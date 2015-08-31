#ifndef AI_H
#define AI_H

#include "Character.h"
#include "MeshBuilder.h"
#include "LoadTGA.h"

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

	enum AI_TYPE
	{
		BUTLER,
		CAT,
		CHARO,
		CLOWN,
		DARK,
		EYES,
		GLOW,
		HORN,
		MASK,
		NOEYES,
		SKELETON,
		TURBAN,
		WITCH,

		MAID,
		SHINIGAMI,
		NUM_AI,
	};

private:
	Vector3 m_intialPosition;
	Vector3 waypoint;
	Vector3 m_target;
	int AI_State;
	bool AI_Active;
	bool spotted;
	std::vector<Vector3> path;
	Mesh* meshAI[NUM_AI];
	int modelswitch;

public:
	AI(Vector3 initialPosition = Vector3(), int modelswitch = 1, Mesh* sprite = NULL, Vector3 waypoint = Vector3());
	~AI();

	void Update(Vector3 playerPos, const TileMap *tileMap, int ModelSwitch);

	Vector3 getPos();
	Mesh* getMesh();

	bool getAiActive();
	void setAiActive(bool AI_Active);
	bool getSpot();
};

#endif