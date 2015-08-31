#ifndef TUTLVL_3_H
#define TUTLVL_3_H

#include "GameModel.h"

#include "MouseCharacter.h"

class TutLvl3 : public GameModel
{
private:
	bool InstructText3;
	string InstructFile3;
	string temp_InstructFile3;
public:
	TutLvl3();
	~TutLvl3();

	void Init();
	void Update(double dt);
	void RenderSpeech();
};

#endif