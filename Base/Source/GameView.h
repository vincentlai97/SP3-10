#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include "View.h"
#include "GameModel.h"


class GameView : public View
{
private:
	bool BGMusic;
	
	void RenderTileMap();
	void RenderPlayer();
	void RenderMusic();
	void RenderInventory();
	void RenderAI();
	void RenderSpeech();
	void RenderWin();

public:
	GameView(Model *model);
	~GameView();

	GameModel *model;

	virtual void Render();
	std::ostringstream strcopy;
	std::ostringstream strcopy2;
	std::ostringstream strcopy3;
};

#endif