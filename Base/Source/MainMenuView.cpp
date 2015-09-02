#include "MainMenuView.h"

#include <sstream>
#include <fstream>

CMainMenuView::CMainMenuView(Model* model) : View(model)
{
}

CMainMenuView::~CMainMenuView()
{
}

void CMainMenuView::Render()
{
	CMainMenuModel* model = dynamic_cast<CMainMenuModel *>(m_model);

	View::Render();

	modelStack.PushMatrix(); {
		if (!model->getHighscore())
		{
			RenderBackground();
			if (model->getChoose())
				RenderLevel();
			else
				RenderButton();
		}
		else
			RenderHighScore();
	} modelStack.PopMatrix();
}

void CMainMenuView::RenderBackground()
{
	CMainMenuModel* model = dynamic_cast<CMainMenuModel *>(m_model);

	int windowWidth, windowHeight;
	glfwGetWindowSize(m_window, &windowWidth, &windowHeight);

	modelStack.PushMatrix(); {

		modelStack.Scale(windowWidth, windowHeight, 1);
		Render2DMesh(model->getBackgroundMesh(), false);
	} modelStack.PopMatrix();
}

void CMainMenuView::RenderButton()
{
	CMainMenuModel* model = dynamic_cast<CMainMenuModel *>(m_model);

	int windowWidth, windowHeight;
	glfwGetWindowSize(m_window, &windowWidth, &windowHeight);

	modelStack.PushMatrix(); {
		modelStack.Scale(windowWidth / 12, windowHeight / 12, 1);

		for (int i = 0; i < model->EXIT_BUTTON; i++)
		{
			modelStack.PushMatrix();
			modelStack.Translate(2, -0.5 - 2 * i, 1);
			modelStack.Scale(2.2, 1.5, 1);
			if (model->getCount() == i)
			{
				Render2DMesh(model->getMesh(i + 4), false);
				modelStack.Scale(1.2, 1.2, 1);
			}
			else
				Render2DMesh(model->getMesh(i + 1), false);
			modelStack.PopMatrix();
		}

	} modelStack.PopMatrix();
}

void CMainMenuView::RenderLevel()
{
	CMainMenuModel* model = dynamic_cast<CMainMenuModel *>(m_model);

	modelStack.PushMatrix(); {

		for (int i = 0; i < 7; i++)
		{
			modelStack.PushMatrix();
			std::ostringstream ss;
			ss << "Level " << i + 1;

			if (model->getCount() == i)
			{
				RenderTextOnScreen(model->getTextMesh(), ss.str(), Color(1, 0, 0), 35, 590, 400 - i * 50, 10);
			}
			else
				RenderTextOnScreen(model->getTextMesh(), ss.str(), Color(1, 1, 0), 30, 600, 400 - i * 50, 10);
			modelStack.PopMatrix();
		}
	} modelStack.PopMatrix();
}

void CMainMenuView::RenderHighScore()
{
	CMainMenuModel* model = dynamic_cast<CMainMenuModel *>(m_model);

	std::ifstream datafile;
	std::string line = "hello";
	std::vector <std::string> highscores;
	datafile.open("highscore.txt");
	if (datafile.is_open())
	{
		while (!datafile.eof())
		{
			getline(datafile, line);

			highscores.push_back(line);
		}
		datafile.close();
	}

	std::ostringstream ss;
	ss << 999999;

	int nextcolumn = 0;
	int max = 21;

	modelStack.PushMatrix(); {
		for (int i = 0; i < highscores.size(); i++)
		{
			nextcolumn = i  / max;
			modelStack.PushMatrix();
			if (highscores[i] == ss.str())
				RenderTextOnScreen(model->getTextMesh(), "-----", Color(1, 0, 0), 35, 100 + nextcolumn * 300, 750 - (i- nextcolumn * max) * 30, 10);
			else
				RenderTextOnScreen(model->getTextMesh(), highscores[i], Color(1, 0, 0), 35, 100 + nextcolumn * 300, 750 - (i - nextcolumn * max) * 30, 10);
			modelStack.PopMatrix();
		}
	} modelStack.PopMatrix();
}