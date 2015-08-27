#ifndef JSLVL2_H
#define JSLVL2_H

#include "GameModel.h"

#include "MouseCharacter.h"

class jslvl2 : public GameModel
{
private:

public:
	jslvl2();
	~jslvl2();

	void Init();
	void Update(double dt);
};

#endif
