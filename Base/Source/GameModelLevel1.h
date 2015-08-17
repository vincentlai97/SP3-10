#ifndef GAMEMODELLEVEL1_H
#define GAMEMODELLEVEL1_H

#include "GameModel2D.h"

#include "MouseCharacter.h"

class GameModelLevel1 : public GameModel2D
{
private:

public:
	GameModelLevel1();
	~GameModelLevel1();

	void Init();
	void Update(double dt);
};

#endif
