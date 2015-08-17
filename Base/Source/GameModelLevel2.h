#ifndef GAMEMODELLEVEL2_H
#define GAMEMODELLEVEL2_H

#include "GameModel2D.h"

#include "MouseCharacter.h"

class GameModelLevel2 : public GameModel2D
{
private:

public:
	GameModelLevel2();
	~GameModelLevel2();

	void Init();
	void Update(double dt);
};

#endif
