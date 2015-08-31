#include "AI.h"

#include "LoS.h"
#include "Pathfinding.h"

AI::AI(Vector3 initialPosition, Mesh* sprite, Vector3 waypoint) : Character(initialPosition, sprite)
, m_intialPosition(initialPosition)
, waypoint(waypoint)
, AI_State(IDLE)
, AI_Active(true)
{
}

AI::~AI()
{
}

static int chaseTurns = -1;
static bool forward = true;

void AI::Update(Vector3 playerPos, const TileMap *tileMap)
{
	if (checkLineOfSight(playerPos, m_position, tileMap))
	{
		AI_State = CHASE;
		chaseTurns = 5;
		path = Pathfinding::Pathfind(m_position, playerPos, tileMap);
	}
	else
	{
		chaseTurns--;
		if (chaseTurns == 0)
		{
			AI_State = RETURNING;
			Vector3 closest = (m_intialPosition - m_position).LengthSquared() < (m_intialPosition + waypoint - m_position).LengthSquared() ? m_intialPosition : m_intialPosition + waypoint;
			path = Pathfinding::Pathfind(m_position, closest, tileMap);
		}
	}

	std::cout << AI_State;

	switch (AI_State)
	{
	case IDLE:
		if (!waypoint.IsZero())
		{
			if (m_position == m_intialPosition + waypoint) forward = false;
			else if (m_position == m_intialPosition) forward = true;
			switch (forward)
			{
			case true:
				m_position += waypoint.Normalized();
				break;
			case false:
				m_position -= waypoint.Normalized();
				break;
			}
		}
		break;
	case RETURNING:
		if (!path.size()) AI_State = IDLE;
		else
		{
			m_position = path.back();
			path.pop_back();
		}
		break;
	case CHASE:
	{
				  if (path.size())
				  {
					  m_position = path.back();
					 path.pop_back();
				  }
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

void AI::SetStateReturning()
{
	chaseTurns = 1;
}