#ifndef TUTLVL_2_H
#define TUTLVL_2_H

#include "GameModel.h"

#include "MouseCharacter.h"

class TutLvl2 : public GameModel
{
private:
	bool InstructText2;
	string InstructFile2;
	string temp_InstructFile2;

public:
	TutLvl2();
	~TutLvl2();

	void Init();
	void Update(double dt);
	void RenderSpeech();
};

#endif