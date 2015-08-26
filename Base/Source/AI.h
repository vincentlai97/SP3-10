#ifndef AI_H
#define AI_H

#include "Character.h"

class AI : public Character
{
public:
	enum AI_STATES
	{
		IDLE,
		CHASE,
		NUM_STATES,
	};

private:
	Vector3 m_target;
	int AI_State;
	bool AI_Active;
public:
	AI(Vector3 position = Vector3(), Mesh* sprite = NULL);
	~AI();

	void Update(Vector3 playerPos, const TileMap *tileMap);

	Vector3 getPos();
	Mesh* getMesh();

	bool getAiActive();
	void setAiActive(bool AI_Active);

	int TouchItem(const TileMap *tileMap);
	void RemoveItem(const TileMap *tileMap);

};

#endif