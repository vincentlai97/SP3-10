#include "AI.h"

const Vector3 SMALLSIZE(0.7f, 0.8f, 0);

AI::AI()
{
	ID = -1;
	Name = "";

	Pos = Destination = OriginalPos = Vector3(0,0,0);

	AI_State = CHASE;
}

AI::~AI()
{
}

AI::AI(int ID,std::string Name, Vector3 Pos)
{
	this->ID = ID;
	this->Name = Name;

	this->Pos = this->OriginalPos = Pos;
}

void AI::Set(int ID,std::string Name, Vector3 Pos)
{
	this->ID = ID;
	this->Name = Name;

	this->Pos = Pos;
	this->OriginalPos = Pos;

	mesh = MeshBuilder::GenerateText("border",1,1);
	mesh->textureID[0] = LoadTGA("Image//Holo.tga");
}

void AI::Update(Vector3 PlayerPos,const TileMap *tileMap)
{
	Destination = PlayerPos;

	switch(AI_State)
	{
	case IDLE:
		break;
	case CHASE:
		{
			Vector3 dir = (Destination - Pos);
			Vector3 vel(0,0,0);
			if( abs(dir.x) > abs(dir.y))
				vel.x += (dir.x > 0) ? 1 : -1;
			else 
				vel.y += (dir.y > 0) ? 1 : -1;

			Vector3 position = Pos + vel;

			if (tileMap->getTile(position.x, floor(position.y)) > 0 || tileMap->getTile(position.x, ceil(position.y)) > 0)
			{
				vel.x = 0;
			}
			if (tileMap->getTile(floor(position.x + (1 - SMALLSIZE.x)), position.y) > 0 || tileMap->getTile(ceil(position.x - (1 - SMALLSIZE.x)), position.y) > 0)
			{
				vel.y = 0;
			}

			Pos += vel;

			//if(Destination == Pos)
			//	AI_State = IDLE;

		}
		break;
	}

}

Vector3 AI::getPos()
{
	return Pos;
}

Mesh* AI::getMesh()
{
	return mesh;
}
