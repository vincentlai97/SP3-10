#include "AI.h"

#include "LoS.h"
#include "Pathfinding.h"

AI::AI(Vector3 initialPosition, int modelswitch, Mesh* sprite, Vector3 waypoint) : Character(initialPosition, sprite)
, m_intialPosition(initialPosition)
, waypoint(waypoint)
, AI_State(IDLE)
, AI_Active(true)
, modelswitch(modelswitch)
{
	meshAI[BUTLER] = MeshBuilder::GenerateText("ButlerModel", 4, 4);
	meshAI[BUTLER]->textureID[0] = LoadTGA("Image//Sprite//Model//ButlerModel.tga");

	meshAI[CAT] = MeshBuilder::GenerateText("CatModel", 4, 4);
	meshAI[CAT]->textureID[0] = LoadTGA("Image//Sprite//Model//CatModel.tga");

	meshAI[CHARO] = MeshBuilder::GenerateText("CharoModel", 4, 4);
	meshAI[CHARO]->textureID[0] = LoadTGA("Image//Sprite//Model//CharoModel.tga");

	meshAI[CLOWN] = MeshBuilder::GenerateText("ClownModel", 4, 4);
	meshAI[CLOWN]->textureID[0] = LoadTGA("Image//Sprite//Model//ClownModel.tga");

	meshAI[DARK] = MeshBuilder::GenerateText("DarkModel", 4, 4);
	meshAI[DARK]->textureID[0] = LoadTGA("Image//Sprite//Model//DarkModel.tga");

	meshAI[EYES] = MeshBuilder::GenerateText("EyesModel", 4, 4);
	meshAI[EYES]->textureID[0] = LoadTGA("Image//Sprite//Model//EyesModel.tga");

	meshAI[GLOW] = MeshBuilder::GenerateText("GlowModel", 4, 4);
	meshAI[GLOW]->textureID[0] = LoadTGA("Image//Sprite//Model//GlowModel.tga");

	meshAI[HORN] = MeshBuilder::GenerateText("HornModel", 4, 4);
	meshAI[HORN]->textureID[0] = LoadTGA("Image//Sprite//Model//HornModel.tga");

	meshAI[MAID] = MeshBuilder::GenerateText("MaidModel", 4, 4);
	meshAI[MAID]->textureID[0] = LoadTGA("Image//Sprite//Model//MaidModel.tga");

	meshAI[MASK] = MeshBuilder::GenerateText("MaskModel", 4, 4);
	meshAI[MASK]->textureID[0] = LoadTGA("Image//Sprite//Model//MaskModel.tga");

	meshAI[NOEYES] = MeshBuilder::GenerateText("NoEyesModel", 4, 4);
	meshAI[NOEYES]->textureID[0] = LoadTGA("Image//Sprite//Model//NoEyesModel.tga");

	meshAI[SHINIGAMI] = MeshBuilder::GenerateText("ShinigamiModel", 4, 4);
	meshAI[SHINIGAMI]->textureID[0] = LoadTGA("Image//Sprite//Model//ShinigamiModel.tga");

	meshAI[SKELETON] = MeshBuilder::GenerateText("SkeletonModel", 4, 4);
	meshAI[SKELETON]->textureID[0] = LoadTGA("Image//Sprite//Model//SkeletonModel.tga");

	meshAI[TURBAN] = MeshBuilder::GenerateText("TurbanModel", 4, 4);
	meshAI[TURBAN]->textureID[0] = LoadTGA("Image//Sprite//Model//TurbanModel.tga");

	meshAI[WITCH] = MeshBuilder::GenerateText("WitchModel", 4, 4);
	meshAI[WITCH]->textureID[0] = LoadTGA("Image//Sprite//Model//WitchModel.tga");

	chaseTurns = -1;
}

AI::~AI()
{
}

static bool forward = true;

void AI::UpdatePath(Vector3 playerPos, const TileMap *tileMap, int ModelSwitch)
{
	if (checkLineOfSight(playerPos, m_virtualPosition, tileMap))
	{
		if (ModelSwitch == modelswitch + 2)
		{
			if ((m_virtualPosition - playerPos).Length() < 5)
			{
				AI_State = CHASE;
				chaseTurns = 5;
				path = Pathfinding::Pathfind(m_virtualPosition, playerPos, tileMap);
			}
			else
			{
				if (AI_State != IDLE)
				{
					chaseTurns--;
					if (chaseTurns == 0)
					{
						AI_State = RETURNING;
						Vector3 closest = (m_intialPosition - m_virtualPosition).LengthSquared() < (m_intialPosition + waypoint - m_virtualPosition).LengthSquared() ? m_intialPosition : m_intialPosition + waypoint;
						path = Pathfinding::Pathfind(m_virtualPosition, closest, tileMap);
					}
				}
			}
		}
		else
		{
			AI_State = CHASE;
			chaseTurns = 5;
			path = Pathfinding::Pathfind(m_virtualPosition, playerPos, tileMap);
		}
	}
	else
	{
		chaseTurns--;
		if (chaseTurns == 0)
		{
			AI_State = RETURNING;
			Vector3 closest = (m_intialPosition - m_virtualPosition).LengthSquared() < (m_intialPosition + waypoint - m_virtualPosition).LengthSquared() ? m_intialPosition : m_intialPosition + waypoint;
			path = Pathfinding::Pathfind(m_virtualPosition, closest, tileMap);
		}
	}

	std::cout << AI_State;

	switch (AI_State)
	{
	case IDLE:
		if (!waypoint.IsZero())
		{
			if (m_virtualPosition == m_intialPosition + waypoint) forward = false;
			else if (m_virtualPosition == m_intialPosition) forward = true;
			switch (forward)
			{
			case true:
				m_virtualPosition += waypoint.Normalized();
				break;
			case false:
				m_virtualPosition -= waypoint.Normalized();
				break;
			}
		}
		break;
	case RETURNING:
		if (!path.size()) AI_State = IDLE;
		else
		{
			m_virtualPosition = path.back();
			path.pop_back();
		}
		break;
	case CHASE:
	{
		if (path.size())
		{
			m_virtualPosition = path.back();
			path.pop_back();
		}
	}
		break;
	}
}

void AI::UpdatePosition(double dt)
{
	Vector3 position = m_position;
	position.x += m_velocity.x * dt;
	if (m_velocity.x < 0)
		position.x = floor(position.x);
	else if (m_velocity.x > 0)
		position.x = ceil(position.x);
	if (position != m_virtualPosition) //Check if player already reached his destination
	{
		if (position != m_virtualPosition) m_position.x = m_virtualPosition.x;
		m_velocity.x = 0;
	}

	position = m_position;
	position.y += m_velocity.y * dt;
	if (m_velocity.y < 0)
		position.y = floor(position.y);
	else if (m_velocity.y > 0)
		position.y = ceil(position.y);
	if (position != m_virtualPosition) //Check if player already reached his destination
	{
		if (position != m_virtualPosition) m_position.y = m_virtualPosition.y;
		m_velocity.y = 0;
	}

	m_position += m_velocity * dt;
}

void AI::UpdateSprite()
{
	if (m_velocity.x < 0)
	{
		m_spriteState = m_spriteTime / WALKINGSPRITE_TIME;
		m_spriteState %= WALKING_NUMFRAMES;
		m_spriteState += WALKING_LEFT;
	}
	else if (m_velocity.x > 0)
	{
		m_spriteState = m_spriteTime / WALKINGSPRITE_TIME;
		m_spriteState %= WALKING_NUMFRAMES;
		m_spriteState += WALKING_RIGHT;
	}
	else if (m_velocity.y < 0)
	{
		m_spriteState = m_spriteTime / WALKINGSPRITE_TIME;
		m_spriteState %= WALKING_NUMFRAMES;
		m_spriteState += WALKING_DOWN;
	}
	else if (m_velocity.y > 0)
	{
		m_spriteState = m_spriteTime / WALKINGSPRITE_TIME;
		m_spriteState %= WALKING_NUMFRAMES;
		m_spriteState += WALKING_UP;
	}
	else
	{
		if (m_spriteState >= WALKING_UP && m_spriteState <= WALKING_UP_END)
			m_spriteState = IDLE_UP;
		else if (m_spriteState >= WALKING_DOWN && m_spriteState <= WALKING_DOWN_END)
			m_spriteState = IDLE_DOWN;
		else if (m_spriteState >= WALKING_LEFT && m_spriteState <= WALKING_LEFT_END)
			m_spriteState = IDLE_LEFT;
		else if (m_spriteState >= WALKING_RIGHT && m_spriteState <= WALKING_RIGHT_END)
			m_spriteState = IDLE_RIGHT;
	}
}

void AI::UpdateVelocity(double dt)
{
	m_velocity.SetZero();
	if (m_virtualPosition != m_position)
		m_velocity += (m_virtualPosition - m_position).Normalized() * 5;
}

void AI::Update(double dt)
{
	Character::Update(dt);

	UpdateVelocity(dt);
	UpdatePosition(dt);
	UpdateSprite();
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

Mesh* AI::getMesh()
{
	return meshAI[modelswitch];
}

bool AI::getSpot()
{
	return chaseTurns > 0;
}