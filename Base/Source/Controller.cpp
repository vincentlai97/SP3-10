#include "Controller.h"

// GLEW & GLFW
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "timer.h"
#include <map>
bool Controller::ExitKey = false;

//Define an error callback
static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
	_fgetchar();
}

//Define the key input callback
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

//Define the cursor enter callback
static void cursor_enter_callback(GLFWwindow* window, int entered)
{
	if (entered == GL_FALSE)
	{
		glfwSetCursorPos(window, 400, 300);
	}
}

//Define the window resize callback
static void resize_callback(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, w, h);
}

void Controller::Init(GLFWwindow* a)
{
	//Set error callback
	glfwSetErrorCallback(error_callback);

	//Initialise GLFW
	if (!glfwInit()) exit(EXIT_FAILURE);

	//Set the GLFW window creation hints - these are optional
	glfwWindowHint(GLFW_SAMPLES, 4); //Request 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Request a specific OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Request a specific OpenGL version
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 

	if(a == NULL)
		view->createWindow(1024, 768, "Scene", glfwGetPrimaryMonitor());
	else
		view->setWindow(a);

	m_dElapsedTime = 0.0; // delta time
	m_dAccumulatedTime_ThreadOne = 0.0;
	m_dAccumulatedTime_ThreadTwo = 0.0;
}


const unsigned char FPS = 60; // FPS of this game
const unsigned int frameTime = 1000 / FPS; // time for each frame
StopWatch m_timer;

void Controller::RunLoop()
{
	m_timer.startTimer();
	while ((!glfwWindowShouldClose(glfwGetCurrentContext()) && !ExitKey) && !IsKeyPressed(VK_ESCAPE) )
	{
		// Get the elapsed time
		m_dElapsedTime = m_timer.getElapsedTime();
		m_dAccumulatedTime_ThreadOne += m_dElapsedTime;
		m_dAccumulatedTime_ThreadTwo += m_dElapsedTime;
		Update();
		view->Render();
		//Swap buffers
		glfwSwapBuffers(view->getWindow());
		glfwPollEvents();
		m_timer.waitUntil(frameTime); // Frame rate limiter. Limits each frame to a specified time in ms.   
	}
	if(IsKeyPressed(VK_ESCAPE))
		throw -1;
	if(glfwWindowShouldClose(glfwGetCurrentContext()) || ExitKey)
		throw -2;
}

void Controller::Update()
{
	model->Update(m_dElapsedTime);
}