#ifndef JSLVL_H
#define JSLVL_H

#include "GameModel.h"

#include "MouseCharacter.h"

class JSlvl : public GameModel
{
public:
	JSlvl();
	~JSlvl();

	void Init();
	void Update(double dt);
};

#endif
