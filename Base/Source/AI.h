#ifndef AI_H
#define AI_H

#include "Character.h"
#include "MeshBuilder.h"
#include "LoadTGA.h"

#include <vector>

#define WALKING_NUMFRAMES 4
#define WALKINGSPRITE_TIME 0.1f

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

	enum SPRITE
	{
		WALKING_DOWN = 0,
		WALKING_DOWN_END = WALKING_DOWN + WALKING_NUMFRAMES - 1,
		WALKING_LEFT = 4,
		WALKING_LEFT_END = WALKING_LEFT + WALKING_NUMFRAMES - 1,
		WALKING_RIGHT = 8,
		WALKING_RIGHT_END = WALKING_RIGHT + WALKING_NUMFRAMES - 1,
		WALKING_UP = 12,
		WALKING_UP_END = WALKING_UP + WALKING_NUMFRAMES - 1,
		IDLE_DOWN = 1,
		IDLE_LEFT = 5,
		IDLE_RIGHT = 9,
		IDLE_UP = 13,
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
	std::vector<Vector3> path;
	int chaseTurns;
	Mesh* meshAI[NUM_AI];
	int modelswitch;

public:
	AI(Vector3 initialPosition = Vector3(), int modelswitch = 1, Mesh* sprite = NULL, Vector3 waypoint = Vector3());
	~AI();

	void Update(double dt);

	Vector3 getPos();
	Mesh* getMesh();

	bool getAiActive();
	void setAiActive(bool AI_Active);

	void SetStateReturning();
	
	bool getSpot();
	void UpdatePath(Vector3 playerPos, const TileMap *tileMap, int ModelSwitch);
	void UpdatePosition(double dt);
	void UpdateSprite();
	void UpdateVelocity(double dt);

};

#endif