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

public:
	GameView(Model *model);
	~GameView();

	virtual void Render();

};

#endif