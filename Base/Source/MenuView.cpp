#include "MenuView.h"

MenuView::MenuView(Model* model) : View(model)
{
}

MenuView::~MenuView()
{
}

void MenuView::Render()
{
	View::Render();

	MenuModel *model = dynamic_cast<MenuModel *>(m_model);

	int windowWidth, windowHeight;
	glfwGetWindowSize(m_window, &windowWidth, &windowHeight);

	modelStack.PushMatrix(); {
		modelStack.Scale(windowWidth, windowHeight, 1);

		Render2DMesh(model->getMenuMesh(), false);
	} modelStack.PopMatrix();

	modelStack.PushMatrix(); {
		modelStack.Translate(-120, -80 - 40 * model->getArrowPosition(), 1);
		modelStack.Scale(40, 30, 1);

		Render2DMesh(model->getArrowMesh(), false);
	} modelStack.PopMatrix();
}