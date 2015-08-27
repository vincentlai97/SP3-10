#ifndef TUTLVL_3_H
#define TUTLVL_3_H

#include "GameModel.h"

#include "MouseCharacter.h"

class TutLvl3 : public GameModel
{
private:

public:
	TutLvl3();
	~TutLvl3();

	void Init();
	void Update(double dt);
};

#endif