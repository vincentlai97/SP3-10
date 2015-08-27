#ifndef NDLVL_H
#define NDLVL_H

#include "GameModel.h"

#include "MouseCharacter.h"

class NDlvl : public GameModel
{
private:

public:
	NDlvl();
	~NDlvl();

	void Init();
	void Update(double dt);
};

#endif