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
		if(model->inventory.getInvent())
			RenderInventory();
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

void GameView::RenderInventory()
{
	GameModel* model = dynamic_cast<GameModel *>(m_model);

	modelStack.Translate(model->getWorldWidth() * 0.5 , model->getWorldHeight() * 0.5, 10);
	modelStack.PushMatrix(); 
	{
		modelStack.PushMatrix(); 
		modelStack.Translate(0,1.8,0);
		modelStack.Scale(15,13,1);
		RenderMesh(model->inventory.getInventMesh(), false);
		modelStack.PopMatrix();

		for(int i = 0 ; i < 10; i++)
		{
			if(model->inventory.inventory.getItem(i)->getID() != -1 && model->inventory.inventory.getItem(i)->getCount() != 0)
			{
				modelStack.PushMatrix();
				modelStack.Translate(model->inventory.InventPos[i].x,model->inventory.InventPos[i].y, 1);
				modelStack.Scale(2,2,2);
				RenderMesh(model->inventory.inventory.getItem(i)->getMesh(), false);
				modelStack.PopMatrix();

				modelStack.PushMatrix();
				std::ostringstream ss;
				ss << model->inventory.inventory.getItem(i)->getCount() ; 
				RenderTextOnScreen(model->getTextMesh(), ss.str(), Color(1, 1, 0), 30, model->inventory.InventPos[i].x * 32 + 540 - model->getWorldWidth() * 0.5 , model->inventory.InventPos[i].y + 480 - model->getWorldHeight() * 0.5 ,10);
				modelStack.PopMatrix();
			}
			else
				break;
		}

		modelStack.PushMatrix();
		modelStack.Translate(model->inventory.InventPos[model->inventory.InvCount].x,model->inventory.InventPos[model->inventory.InvCount].y, 2);
		modelStack.Scale(2,2,2);
		RenderMesh(model->inventory.getborderMesh(), false);
		modelStack.PopMatrix();
	} 
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	std::ostringstream ss1;
	ss1 << model->inventory.inventory.getItem(model->inventory.InvCount)->getName() ; 
	RenderTextOnScreen(model->getTextMesh(), ss1.str(), Color(1, 1, 0), 60, 20,0 ,10);
	modelStack.PopMatrix();

}