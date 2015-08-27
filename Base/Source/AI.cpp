#include "AI.h"

#include "LoS.h"
#include "Pathfinding.h"

AI::AI(Vector3 position, Mesh* sprite) : Character(position, sprite), AI_Active(true)
{
}

AI::~AI()
{
}

static int chaseTurns;

void AI::Update(Vector3 playerPos, const TileMap *tileMap)
{
	if (checkLineOfSight(playerPos, m_position, tileMap))
	{
		m_target = playerPos;
		AI_State = CHASE;
		chaseTurns = 5;
		path = Pathfinding::Pathfind(m_position, playerPos, tileMap);
	}
	else
	{
		chaseTurns--;
		if (chaseTurns <= 0) AI_State = IDLE;
	}

	switch (AI_State)
	{
	case IDLE:
		break;
	case CHASE:
	{
				  m_position = path.back();
				  path.pop_back();
	}
		break;
	}

}

bool AI::getAiActive()
{
	return AI_Active;
}

void AI::setAiActive(bool AI_Active)
{
	this->AI_Active = AI_Active;
}