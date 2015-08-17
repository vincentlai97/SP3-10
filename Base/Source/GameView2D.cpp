#include "GameView2D.h"

GameView2D::GameView2D(Model* model) : View(model)
{
}

void GameView2D::Render()
{
	View::Render();

	Mtx44 perspective;
	perspective.SetToOrtho(0, 32, 0, 25, -1000, 1000);
	projectionStack.LoadMatrix(perspective);

	modelStack.PushMatrix(); {
		RenderBackground();
		RenderMobs();
		RenderTileMap();
		RenderPlayerCharacter();
		RenderScore();
	} modelStack.PopMatrix();
}

void GameView2D::RenderBackground()
{
	GameModel2D* model = dynamic_cast<GameModel2D *>(m_model);

	float mapOffset_x, mapOffset_y;
	model->getOffset(mapOffset_x, mapOffset_y);
	while (mapOffset_x > 64) mapOffset_x -= 64;
	mapOffset_x /= 2;

	modelStack.PushMatrix(); {
		modelStack.Translate(-mapOffset_x, -mapOffset_y, 0);
		modelStack.Scale(32, 25, 1);
		modelStack.Translate(.5, .5, -1);

		RenderMesh(model->getBackgroundMesh(), false);

		modelStack.PushMatrix(); {
			modelStack.Translate(1, 0, 0);

			RenderMesh(model->getBackgroundMesh(), false);
		} modelStack.PopMatrix();
	} modelStack.PopMatrix();
}

#define tileMap model->getTileMap()

void GameView2D::RenderTileMap()
{
	GameModel2D* model = dynamic_cast<GameModel2D *>(m_model);

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

void GameView2D::RenderPlayerCharacter()
{
	GameModel2D* model = dynamic_cast<GameModel2D *>(m_model);

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

#define mobsList model->getMobsList()

void GameView2D::RenderMobs()
{
	GameModel2D* model = dynamic_cast<GameModel2D *>(m_model);

	float mapOffset_x, mapOffset_y;
	model->getOffset(mapOffset_x, mapOffset_y);

	for (int count = 0; count < mobsList.size(); ++count)
	{
		if (mobsList[count]->isActive())
		{
			modelStack.PushMatrix(); {
				modelStack.Translate(-mapOffset_x, -mapOffset_y, 1);
				modelStack.Translate(mobsList[count]->getPosition());
				modelStack.Translate(0.5, 0.5, 0);

				RenderMesh(model->getMobsMesh(), false, 6 * mobsList[count]->getSpriteState(), 6);
			} modelStack.PopMatrix();
		}
	}
}

#undef mobsList

void GameView2D::RenderScore()
{
	GameModel2D* model = dynamic_cast<GameModel2D *>(m_model);

	std::ostringstream ss;
	ss << "Score: " << model->getScore();
	RenderTextOnScreen(model->getTextMesh(), ss.str(), Color(0, 0, 0), 50, 100, 700);
}