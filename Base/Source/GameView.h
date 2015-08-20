#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include "View.h"
#include "GameModel.h"

class GameView : public View
{
private:
	void RenderTileMap();

public:
	GameView(Model *model);
	~GameView();

	virtual void Render();

};

#endif