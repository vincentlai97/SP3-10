#include "GameView.h"

GameView::GameView(Model *model) : View(model)
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
	} modelStack.PopMatrix();

	modelStack.PushMatrix(); {
		modelStack.Translate(model->pos1);
		modelStack.Translate(0.5f, 0.5f, 5);

		RenderMesh(model->foo, false);
	} modelStack.PopMatrix();

	modelStack.PushMatrix(); {
		modelStack.Translate(model->pos2);
		modelStack.Translate(0.5f, 0.5f, 5);

		RenderMesh(model->foo, false);
	} modelStack.PopMatrix();
}

#define tileMap model->getTileMap()

void GameView::RenderTileMap()
{
	GameModel* model = dynamic_cast<GameModel *>(m_model);

	float mapOffset_x, mapOffset_y;
	model->getOffset(mapOffset_x, mapOffset_y);

	modelStack.Translate(0, 0, 1);
		static int seed = rand();
	srand(seed);
	for (int ccount = 0; ccount < tileMap->getNumOfTilesWidth() + 1; ++ccount)
	{
		for (int rcount = 0; rcount < tileMap->getNumOfTilesHeight() + 1; ++rcount)
		{
			modelStack.PushMatrix(); {
				modelStack.Translate(int(-(mapOffset_x - (int)mapOffset_x)), int(-(mapOffset_y - (int)mapOffset_y)), 0);
				modelStack.Translate(ccount, rcount, 0);
				modelStack.Translate(0.5f, 0.5f, 0);

				if (tileMap->getTile(ccount + (int)mapOffset_x, rcount + (int)mapOffset_y) >= 0)
					RenderMesh(model->getTileMesh(), false, 6 * tileMap->getTile(ccount + (int)mapOffset_x, rcount + (int)mapOffset_y), 6);
				else
				{
					RenderMesh(model->getTileMesh(), false, 6 * model->floorTiles[rand() % model->floorTiles.size()], 6);
					if (model->checkLineOfSight(model->pos1 + Vector3(.5f, .5f, 0), Vector3(ccount + (int)mapOffset_x, rcount + (int)mapOffset_y, 0) + Vector3(.5f, .5f, 0), tileMap) == 0)
					{
						modelStack.Translate(0, 0, 1);
						RenderMesh(model->shadow, false);
					}
				}
			} modelStack.PopMatrix();
		}
	}
}

#undef tileMap