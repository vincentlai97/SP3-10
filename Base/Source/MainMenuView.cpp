#include "MainMenuView.h"


CMainMenuView::CMainMenuView(Model* model) : View(model)
{
}


CMainMenuView::~CMainMenuView()
{
}

void CMainMenuView::Render()
{
	View::Render();

	modelStack.PushMatrix(); {
		RenderButton();
		RenderBackground();
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

		modelStack.PushMatrix();
		modelStack.Translate(2, -0.5, 0);
		modelStack.Scale(2.2, 1.5, 1);
		if (model->getCount() == 0)
		{
			Render2DMesh(model->getStartMesh2(), false);
			modelStack.Scale(1.2, 1.2, 1);
		}
		Render2DMesh(model->getStartMesh(), false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(2, -2.5, 0);
		modelStack.Scale(2.2, 1.5, 1);
		if (model->getCount() == 1)
		{
			Render2DMesh(model->getLoadMesh2(), false);
			modelStack.Scale(1.2, 1.2, 1);
		}
		Render2DMesh(model->getLoadMesh(), false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(2, -4.5, 0);
		modelStack.Scale(2.2, 1.5, 1);
		if (model->getCount() == 2)
		{
			Render2DMesh(model->getExitMesh2(), false);
			modelStack.Scale(1.2, 1.2, 1);
		}
		Render2DMesh(model->getExitMesh(), false);
		modelStack.PopMatrix();

	} modelStack.PopMatrix();
}