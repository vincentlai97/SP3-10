#include "Model.h"

#include "MeshBuilder.h"
#include "LoadTGA.h"

void Model::Init()
{
	camera.Init(Vector3(0, 0, 10), Vector3(), Vector3(0, 1, 0));
}

void Model::Update(double dt)
{

}

void Model::UpdateCameraPos(bool *cmds)
{
	if (cmds[0]) camera.position.y += 0.1;
	if (cmds[1]) camera.position.x -= 0.1;
	if (cmds[2]) camera.position.y -= 0.1;
	if (cmds[3]) camera.position.x += 0.1;
}