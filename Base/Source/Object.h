#ifndef OBJECT_H
#define OBJECT_H

#include "Mesh.h"
#include "Mtx44.h"

struct Object
{
	Mesh* mesh;
	Mtx44 translation, rotation, scale;

	Object(Mesh *mesh = NULL) : mesh(mesh)
	{
		translation.SetToIdentity();
		rotation.SetToIdentity();
		scale.SetToIdentity();
	}
};

#endif