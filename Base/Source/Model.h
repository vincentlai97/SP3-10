#ifndef MODEL_H
#define MODEL_H

#include "Object.h"
#include "Camera3.h"

#include <vector>

class Model
{
protected:
	std::vector<Object *> m_objectList;

	Camera3 camera;

	bool *commands;

public:
	virtual void Init();
	virtual void Update(double dt);

	virtual void setCommands(int command) {}

	void UpdateCameraPos(bool* cmds);

	const std::vector<Object *>& getObjectList() const { return m_objectList; }
	const Camera3& getCamera() const { return camera; }

};

#endif