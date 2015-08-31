#ifndef RYLEVEL_H
#define RYLEVEL_H

#include "GameModel.h"

#include "MouseCharacter.h"

class RyLevel : public GameModel
{
private:

public:
	RyLevel();
	~RyLevel();

	void Init();
	void Update(double dt);
};

#endif
