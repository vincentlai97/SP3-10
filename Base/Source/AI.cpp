#include "AI.h"

#include "LoS.h"
#include "Pathfinding.h"

AI::AI(Vector3 initialPosition, int modelswitch, Mesh* sprite, Vector3 waypoint) : Character(initialPosition, sprite)
, m_intialPosition(initialPosition)
, waypoint(waypoint)
, AI_State(IDLE)
, AI_Active(true)
, modelswitch(modelswitch)
, spotted(false)
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
}

AI::~AI()
{
}

static int chaseTurns = -1;
static bool forward = true;

void AI::Update(Vector3 playerPos, const TileMap *tileMap, int ModelSwitch)
{
	if (checkLineOfSight(playerPos, m_position, tileMap))
	{
		if (ModelSwitch == modelswitch)
		{
			if ((m_position - playerPos).Length() < 5)
			{
				AI_State = CHASE;
				chaseTurns = 5;
				path = Pathfinding::Pathfind(m_position, playerPos, tileMap);
			}
			else
			{
				if (AI_State != IDLE)
				{
					chaseTurns--;
					if (chaseTurns == 0)
					{
						AI_State = RETURNING;
						Vector3 closest = (m_intialPosition - m_position).LengthSquared() < (m_intialPosition + waypoint - m_position).LengthSquared() ? m_intialPosition : m_intialPosition + waypoint;
						path = Pathfinding::Pathfind(m_position, closest, tileMap);
					}
				}
			}
		}
		else
		{
			AI_State = CHASE;
			chaseTurns = 5;
			path = Pathfinding::Pathfind(m_position, playerPos, tileMap);
		}
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
		spotted = false;
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
		spotted = false;
		if (!path.size()) AI_State = IDLE;
		else
		{
			m_position = path.back();
			path.pop_back();
		}
		break;
	case CHASE:
	{
				  spotted = true;
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

Mesh* AI::getMesh()
{
	return meshAI[modelswitch - 3];
}

bool AI::getSpot()
{
	return spotted;
}