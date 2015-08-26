#include "AI.h"

#include "LoS.h"

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
				  Vector3 dir = (m_target - m_position);
				  Vector3 vel;
				  vel.x = (dir.x == 0) ? 0 : ((dir.x > 0) ? 1 : -1);
				  vel.y = (dir.y == 0) ? 0 : ((dir.y > 0) ? 1 : -1);

				  if (abs(dir.x) >= abs(dir.y))
				  {
					  if (tileMap->getTile(m_position.x + vel.x, m_position.y) > 0)
					  {
						  if (dir.y)
						  {
							  if (tileMap->getTile(m_position.x, m_position.y + vel.y) > 0) break;
							  else m_position.y += vel.y;
						  }
					  }
					  else m_position.x += vel.x;
				  }
				  else
				  {
					  if (tileMap->getTile(m_position.x, m_position.y + vel.y) > 0)
					  {
						  if (dir.x)
						  {
							  if (tileMap->getTile(m_position.x + vel.x, m_position.y) > 0) break;
							  else m_position.x += vel.x;
						  }
					  }
					  else m_position.y += vel.y;
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

int AI::TouchItem(const TileMap *tileMap)
{
	return tileMap->getTile(m_position.x, floor(m_position.y));
}
void AI::RemoveItem(const TileMap *tileMap)
{
	tileMap->SetTile(m_position.x, floor(m_position.y), -1);
}