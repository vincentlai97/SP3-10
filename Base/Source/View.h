#ifndef VIEW_H
#define VIEW_H

#include "Model.h"

//Include GLEW & GLFW
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Light.h"
#include "MatrixStack.h"

class View
{
	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,
		U_LIGHTENABLED,
		U_NUMLIGHTS,
		U_LIGHT0_TYPE,
		U_LIGHT0_POSITION,
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,
		U_LIGHT0_SPOTDIRECTION,
		U_LIGHT0_COSCUTOFF,
		U_LIGHT0_COSINNER,
		U_LIGHT0_EXPONENT,
		U_LIGHT1_TYPE,
		U_LIGHT1_POSITION,
		U_LIGHT1_COLOR,
		U_LIGHT1_POWER,
		U_LIGHT1_KC,
		U_LIGHT1_KL,
		U_LIGHT1_KQ,
		U_LIGHT1_SPOTDIRECTION,
		U_LIGHT1_COSCUTOFF,
		U_LIGHT1_COSINNER,
		U_LIGHT1_EXPONENT,
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE_ENABLED1,
		U_COLOR_TEXTURE,
		U_COLOR_TEXTURE1,
		U_TEXT_ENABLED,
		U_TEXT_COLOR,
		U_TOTAL,
	};

protected:
	Model *m_model;

	GLFWwindow *m_window;

	unsigned m_vertexArrayID;
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	Light lights[2];

	MS modelStack, viewStack, projectionStack;

public:
	View(Model* model) : m_model(model) {}

	bool createWindow(const int &window_width, const int &window_height, const char *window_title, GLFWmonitor *monitor = NULL, GLFWwindow *share = NULL);
	GLFWwindow* getWindow() { return m_window; }

	virtual void Init();
	virtual void Render();

	void RenderMesh(Mesh *mesh, bool lightEnabled, unsigned offset = 0, unsigned count = 0);
	void Render2DMesh(Mesh *mesh, bool lightEnabled, unsigned offset = 0, unsigned count = 0);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
};

#endif