#include "GameView.h"
#pragma comment(lib, "irrKlang.lib")
using namespace irrklang;
ISoundEngine* BGM1 = createIrrKlangDevice(ESOD_AUTO_DETECT, ESEO_MULTI_THREADED | ESEO_LOAD_PLUGINS | ESEO_USE_3D_BUFFERS);

#include "LoS.h"

#include "Pathfinding.h"

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
		if (model->isShowInventory())
			RenderInventory();
		RenderAI();
		if (model->getwin())
			RenderWin();
		if (model->GetLineParagraph() > 0 && model->GetLineParagraph() < 4)
			RenderSpeech();
	} modelStack.PopMatrix();
}

#define tileMap model->getTileMap()
#define itemMap model->getItemMap()

static int seed = rand();

void GameView::RenderTileMap()
{
	GameModel* model = dynamic_cast<GameModel *>(m_model);

	float mapOffset_x, mapOffset_y;
	model->getOffset(mapOffset_x, mapOffset_y);

	modelStack.Translate(0, 0, 1);
	srand(seed);
	for (int ccount = 0; ccount < tileMap->getNumOfTilesWidth() + 1; ++ccount)
	{
		for (int rcount = 0; rcount < tileMap->getNumOfTilesHeight() + 1; ++rcount)
		{
			modelStack.PushMatrix(); {
				modelStack.Translate(-(mapOffset_x - (int)mapOffset_x), -(mapOffset_y - (int)mapOffset_y), 0);
				modelStack.Translate(ccount, rcount, 0);
				modelStack.Translate(0.5f, 0.5f, 0);

				RenderMesh(model->getTileMesh(), false, 6 * model->floorTiles[rand() % model->floorTiles.size()], 6); //Render Ground
				modelStack.Translate(0, 0, 1);
				if (tileMap->getTile(ccount + (int)mapOffset_x, rcount + (int)mapOffset_y) >= 0){

					RenderMesh(model->getTileMesh(), false, 6 * tileMap->getTile(ccount + (int)mapOffset_x, rcount + (int)mapOffset_y), 6); //Render Terrain
				}
				else if (itemMap->getTile(ccount + (int)mapOffset_x, rcount + (int)mapOffset_y) > 49)
				{
					RenderMesh(model->getTileMesh(), false, 6 * itemMap->getTile(ccount + (int)mapOffset_x, rcount + (int)mapOffset_y), 6);
				}
				else
				{

					RenderMesh(model->getTileMesh(), false, 6 * model->floorTiles[rand() % model->floorTiles.size()], 6); //Render Ground
					bool renderShadow = true;
					if (checkLineOfSight(model->getPlayer()->getPosition() + Vector3(.5f, .5f, 0), Vector3(ccount + (int)mapOffset_x, rcount + (int)mapOffset_y, 0) + Vector3(.5f, .5f, 0), tileMap)) //Check LoS with player
						renderShadow = false;
					for (std::vector<Vector3>::iterator it = model->mirror.begin(); it != model->mirror.end(); ++it)
					{
						if ((checkLineOfSight(model->getPlayer()->getPosition() + Vector3(.5f, .5f, 0), (*it) + Vector3(.5f, .5f, 0), tileMap)
							&& checkLineOfSight((*it) + Vector3(.5f, .5f, 0), Vector3(ccount + (int)mapOffset_x, rcount + (int)mapOffset_y, 0) + Vector3(.5f, .5f, 0), tileMap)))
							renderShadow = false;
					}
					if (renderShadow)
					{
						modelStack.PushMatrix(); {
							modelStack.Translate(0, 0, 5);

							RenderMesh(model->shadow, false); //Render Shadow
						} modelStack.PopMatrix();
					}

				}

				modelStack.Translate(0, 0, 1);
				if (itemMap->getTile(ccount + (int)mapOffset_x, rcount + (int)mapOffset_y) < model->inventory.inventory.TOTAL_ITEM + model->inventory.inventory.TOTAL_ITEM && itemMap->getTile(ccount + (int)mapOffset_x, rcount + (int)mapOffset_y) > -1)
				{
					if (itemMap->getTile(ccount + (int)mapOffset_x, rcount + (int)mapOffset_y) < model->inventory.inventory.TOTAL_ITEM)
						RenderMesh(model->inventory.inventory.meshlist[model->inventory.inventory.DefaultItem[itemMap->getTile(ccount + (int)mapOffset_x, rcount + (int)mapOffset_y)].getID()], false);
					else
						RenderMesh(model->inventory.inventory.meshlist[model->inventory.inventory.DefaultItem[itemMap->getTile(ccount + (int)mapOffset_x, rcount + (int)mapOffset_y) - model->inventory.inventory.TOTAL_ITEM].getID()], false);
				}

			} modelStack.PopMatrix();
		}
	}

	modelStack.PushMatrix();
	std::ostringstream ss;
	if (model->getNumKeys() == model->getTotalKeys())
		ss << "All keys obtained! ";
	else
		ss << "Keys : " << model->getNumKeys() << " / " << model->getTotalKeys();
	RenderTextOnScreen(model->getTextMesh(), ss.str(), Color(1, 1, 0), 30, 50,750, 10);
	modelStack.PopMatrix();

}
#undef tileMap

#define player model->getPlayer()

void GameView::RenderPlayer()
{
	GameModel* model = dynamic_cast<GameModel *>(m_model);

	float mapOffset_x, mapOffset_y;
	model->getOffset(mapOffset_x, mapOffset_y);

	modelStack.Translate(0, 0, 2);
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
		//BGM1->play2D("../irrKlang/media/Bgm2.mp3", true);
		BGMusic = false;
	}

}

void GameView::RenderInventory()
{
	GameModel* model = dynamic_cast<GameModel *>(m_model);

	modelStack.Translate(0, 0, 10);
	modelStack.PushMatrix();
	modelStack.Translate(model->getWorldWidth() * 0.5 + 2, model->getWorldHeight() * 0.5, 0);
	modelStack.PushMatrix();
	{
		//background
		modelStack.PushMatrix();
		modelStack.Translate(-4, 1.8, 0);
		modelStack.Scale(22, 13, 1);
		RenderMesh(model->inventory.getInventMesh(), false);
		modelStack.PopMatrix();

		for (int i = 0; i < 10; i++)
		{
			if (model->inventory.inventory.getItem(i)->getID() != -1 && model->inventory.inventory.getItem(i)->getCount() != 0)
			{
				//item mesh
				modelStack.PushMatrix();
				modelStack.Translate(model->inventory.InventPos[i].x, model->inventory.InventPos[i].y, 1);
				modelStack.Scale(2, 2, 2);
				RenderMesh(model->inventory.inventory.getItem(i)->getMesh(), false);
				modelStack.PopMatrix();

				//item count
				modelStack.PushMatrix();
				std::ostringstream ss;
				ss << model->inventory.inventory.getItem(i)->getCount();
				RenderTextOnScreen(model->getTextMesh(), ss.str(), Color(1, 1, 0), 30, model->inventory.InventPos[i].x * 32 + 570 - model->getWorldWidth() * 0.5, model->inventory.InventPos[i].y * 37 + 370 - model->getWorldHeight() * 0.5, 10);
				modelStack.PopMatrix();
			}
			else
				break;
		}
		// selector*
		modelStack.PushMatrix();
		modelStack.Translate(model->inventory.InventPos[model->inventory.InvCount].x, model->inventory.InventPos[model->inventory.InvCount].y, 2);
		modelStack.Scale(2, 2, 2);
		RenderMesh(model->inventory.getborderMesh(), false);
		modelStack.PopMatrix();

		//Item selected
		if (model->inventory.inventory.getItem(model->inventory.InvCount)->getID() != -1)
		{
			modelStack.PushMatrix();
			modelStack.Translate(-11.5, 5, 2);
			modelStack.Scale(4, 4, 4);
			RenderMesh(model->inventory.inventory.getItem(model->inventory.InvCount)->getMesh(), false);
			modelStack.PopMatrix();
		}
	}
	modelStack.PopMatrix();

	if (model->inventory.inventory.getItem(model->inventory.InvCount)->getID() != -1)
	{
		//print name of item selected
		modelStack.PushMatrix();
		std::ostringstream ss1;
		ss1 << model->inventory.inventory.getItem(model->inventory.InvCount)->getName();
		RenderTextOnScreen(model->getTextMesh(), ss1.str(), Color(1, 1, 0), 22, 130, 450, 10);
		modelStack.PopMatrix();

		//print count of item selected
		modelStack.PushMatrix();
		std::ostringstream ss2;
		ss2 << model->inventory.inventory.getItem(model->inventory.InvCount)->getCount();
		RenderTextOnScreen(model->getTextMesh(), ss2.str(), Color(1, 1, 0), 25, 200, 420, 10);
		modelStack.PopMatrix();
	}
	modelStack.PopMatrix();
}

void GameView::RenderAI()
{
	GameModel* model = dynamic_cast<GameModel *>(m_model);

	float mapOffset_x, mapOffset_y;
	model->getOffset(mapOffset_x, mapOffset_y);

	modelStack.Translate(0, 0, 2);
	modelStack.PushMatrix(); {
		modelStack.Translate(-mapOffset_x, -mapOffset_y, -1);

		/*std::vector<Vector3> foo = Pathfinding::Pathfind(model->Aina->getPosition(), Vector3(floor(model->getPlayer()->getPosition().x), floor(model->getPlayer()->getPosition().y), 0), model->getTileMap());
		for (std::vector<Vector3>::iterator it = foo.begin(); it != foo.end(); ++it)
		{
		modelStack.PushMatrix(); {
		modelStack.Translate((*it));
		modelStack.Translate(0.5, 0.5, 0);

		RenderMesh(model->getAIMesh(13), false);
		} modelStack.PopMatrix();
		}*/

		modelStack.Translate(model->Aina->getPosition());
		modelStack.Translate(0.5, 0.5, 0);
		if (model->Aina->getAiActive() == true)
		{
			RenderMesh(model->getAIMesh(13), false);
		}
	} modelStack.PopMatrix();
}

void GameView::RenderSpeech()
{
	GameModel* model = dynamic_cast<GameModel *>(m_model);

	modelStack.Translate(0, 0, 11);
	modelStack.PushMatrix(); {
		modelStack.Translate(model->getWorldWidth() / 2, model->getWorldHeight() / 8, 0);
		modelStack.Scale(model->getWorldWidth(), model->getWorldHeight() / 4, 1);
		RenderMesh(model->getSpeechMesh(), false, 6 * 0, 6);
	} modelStack.PopMatrix();

	modelStack.Translate(0, 0, 1);
	modelStack.PushMatrix(); {
		modelStack.Translate(model->getWorldWidth() / 8, model->getWorldHeight() / 8, 0);
		modelStack.Scale(model->getWorldWidth() / 5, model->getWorldHeight() / 4.5, 1);
		RenderMesh(model->getFaceMesh(), false, 6 * 0, 6);
	} modelStack.PopMatrix();

	float transX = model->getWorldWidth() * 8;

	if (model->GetLineParagraph() == 1)
	{
		strcopy.str("");
		strcopy << model->GetTextSpeech();
		RenderTextOnScreen(model->getTextMesh(), strcopy.str(), Color(1, 1, 1), 30, transX, 140, 10);
	}
	else if (model->GetLineParagraph() == 2)
	{
		RenderTextOnScreen(model->getTextMesh(), strcopy.str(), Color(1, 1, 1), 30, transX, 140, 10);

		strcopy2.str("");
		strcopy2 << model->GetTextSpeech();
		RenderTextOnScreen(model->getTextMesh(), strcopy2.str(), Color(1, 1, 1), 30, transX, 80, 10);
	}
	else if (model->GetLineParagraph() == 3)
	{
		RenderTextOnScreen(model->getTextMesh(), strcopy.str(), Color(1, 1, 1), 30, transX, 140, 10);
		RenderTextOnScreen(model->getTextMesh(), strcopy2.str(), Color(1, 1, 1), 30, transX, 80, 10);

		std::ostringstream strcopy3;
		strcopy3 << model->GetTextSpeech();
		RenderTextOnScreen(model->getTextMesh(), strcopy3.str(), Color(1, 1, 1), 30, transX, 20, 10);
	}
}

void GameView::RenderWin()
{
	GameModel* model = dynamic_cast<GameModel *>(m_model);

	modelStack.PushMatrix();
	modelStack.Translate(model->getWorldWidth() * 0.5, model->getWorldHeight() * 0.5, 12);
	modelStack.Scale(model->getWorldWidth(), model->getWorldHeight(), 10);
	if (!model->getDead())
		RenderMesh(model->getWinMesh(), false);
	else 
		RenderMesh(model->getLoseMesh(), false);
	modelStack.PopMatrix();
}