#ifndef STORYMODEL1_H
#define STORYMODEL1_H

#include "GameModel.h"

class StoryModel1 : public GameModel
{
public:
	StoryModel1();
	~StoryModel1();

	virtual void Init();
	virtual void Update(double dt);

};

#endif