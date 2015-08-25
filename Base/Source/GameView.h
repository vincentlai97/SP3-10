#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include "View.h"
#include "GameModel.h"
#include <irrKlang.h>

class GameView : public View
{
private:
	bool BGMusic;
	
	void RenderTileMap();
	void RenderPlayer();
	void RenderMusic();
	void RenderInventory();
	void RenderAI();
	void RenderWin();

public:
	GameView(Model *model);
	~GameView();

	GameModel *model;

	virtual void Render();

};

#endif