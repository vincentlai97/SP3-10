#include "GameView.h"

#pragma comment(lib, "irrKlang.lib")
using namespace irrklang;
ISoundEngine* BGM1 = createIrrKlangDevice(ESOD_AUTO_DETECT, ESEO_MULTI_THREADED | ESEO_LOAD_PLUGINS | ESEO_USE_3D_BUFFERS);

GameView::GameView(Model *model) : View(model) 
, BGMusic(true)
{
}

GameView::~GameView()
{
}

void GameView::Render()
{
	GameModel* model = dynamic_cast<GameModel *>(m_model);

	View::Render();

	Mtx44 perspertive;
	perspertive.SetToOrtho(0, model->getWorldWidth(), 0, model->getWorldHeight(), -10, 10);
	projectionStack.LoadMatrix(perspertive);

	modelStack.PushMatrix(); {
		RenderTileMap();
		RenderPlayer();
		RenderMusic();
	} modelStack.PopMatrix();
}

#define tileMap model->getTileMap()

void GameView::RenderTileMap()
{
	GameModel* model = dynamic_cast<GameModel *>(m_model);

	float mapOffset_x, mapOffset_y;
	model->getOffset(mapOffset_x, mapOffset_y);

	modelStack.Translate(0, 0, 1);
	for (int ccount = 0; ccount < tileMap->getNumOfTilesWidth() + 1; ++ccount)
	{
		for (int rcount = 0; rcount < tileMap->getNumOfTilesHeight() + 1; ++rcount)
		{
			modelStack.PushMatrix(); {
				modelStack.Translate(-(mapOffset_x - (int)mapOffset_x), -(mapOffset_y - (int)mapOffset_y), 0);
				modelStack.Translate(ccount, rcount, 0);
				modelStack.Translate(0.5f, 0.5f, 0);

				if (tileMap->getTile(ccount + (int)mapOffset_x, rcount + (int)mapOffset_y))
					RenderMesh(model->getTileMesh(), false, 6 * tileMap->getTile(ccount + (int)mapOffset_x, rcount + (int)mapOffset_y), 6);
			} modelStack.PopMatrix();
		}
	}
}
#undef tileMap

#define player model->getPlayer()

void GameView::RenderPlayer()
{
	GameModel* model = dynamic_cast<GameModel *>(m_model);

	float mapOffset_x, mapOffset_y;
	model->getOffset(mapOffset_x, mapOffset_y);

	modelStack.Translate(0, 0, 1);
	modelStack.PushMatrix(); {
		modelStack.Translate(-mapOffset_x, -mapOffset_y, 0);
		modelStack.Translate(player->getPosition());
		modelStack.Translate(0.5, 0.5, 0);

		RenderMesh(model->getPlayerMesh(), false, 6 * player->getSpriteState(), 6);
	} modelStack.PopMatrix();
}
#undef player

void GameView::RenderMusic()
{
	if (BGMusic)
	{
		BGM1->play2D("../irrKlang/media/Bgm2.mp3", true);
		BGMusic = false;
	}
}
	