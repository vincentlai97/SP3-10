#ifndef NDLVL_H
#define NDLVL_H

#include "GameModel.h"

#include "MouseCharacter.h"

class NDlvl : public GameModel
{
public:
	NDlvl();
	~NDlvl();

	void Init();
	void Update(double dt);
	void RenderSpeech();
	GameModel * model;


};

#endif