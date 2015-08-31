#ifndef NDLVL_H
#define NDLVL_H

#include "GameModel.h"

#include "MouseCharacter.h"

class NDlvl : public GameModel
{
private:
	bool InstructText;
	string InstructFile;
	string temp_InstructFile;

public:
	NDlvl();
	~NDlvl();

	void Init();
	void Update(double dt);
	void RenderSpeech();
	GameModel * model;


};

#endif