#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include "View.h"
#include "GameModel.h"

class GameView : public View
{
private:

public:
	GameView(Model *model);
	~GameView();

	virtual void Render();
	void RenderTileMap();

};

#endif