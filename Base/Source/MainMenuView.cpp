#include "MainMenuView.h"
#include <sstream>

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
		RenderBackground();
		if (model->getChoose())
			RenderLevel();
		else
			RenderButton();
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


