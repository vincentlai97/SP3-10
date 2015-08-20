#ifndef AI_H
#define AI_H

#include "Model.h"
#include <string>
#include <iostream>

#include "LoadTGA.h"
#include "MeshBuilder.h"
#include "TileMap.h"

class AI
{
private:
	int ID;
	std::string Name;

	Vector3 Pos,Destination,OriginalPos;

	Mesh* mesh;

	int AI_State;
public:

	enum AI_STATES
	{
		IDLE,
		CHASE,
		NUM_STATES,
	};

	AI(void);
	~AI(void);

	AI(int,std::string,Vector3);

	void Set(int,std::string,Vector3);
	void Update(Vector3,const TileMap *tileMap);

	Vector3 getPos();
	Mesh* getMesh();

};

#endif