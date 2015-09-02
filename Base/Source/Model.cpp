#include "Model.h"

#include "MeshBuilder.h"
#include "LoadTGA.h"

Model::Model()
{
}

Model::~Model()
{
}

void Model::Init()
{
	camera.Init(Vector3(0, 0, 10), Vector3(), Vector3(0, 1, 0));
}

void Model::Update(double dt)
{

}