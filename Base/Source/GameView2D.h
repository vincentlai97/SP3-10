#ifndef GAMEVIEW2D_H
#define GAMEVIEW2D_H

#include "View.h"
#include "GameModel2D.h"

class GameView2D : public View
{
private:

public:
	GameView2D(Model* model = NULL);

	void Render();
	void RenderBackground();
	void RenderTileMap();
	void RenderPlayerCharacter();
	void RenderMobs();
	void RenderScore();

};

#endif