#ifndef MENUMODEL_H
#define MENUMODEL_H

#include "Model.h"

class MenuModel : public Model
{
public:
	enum COMMANDS {
		MOVE_UP,
		MOVE_DOWN,
		ENTER,
		NUM_COMMANDS,
	};

private:
	Mesh *menuScreen;
	Mesh *arrow;

	int arrowPosition;

public:
	MenuModel();
	~MenuModel();

	void Init();
	void Update(double dt);

	void setCommands(int command);

	Mesh* getMenuMesh();

	Mesh* getArrowMesh();
	int getArrowPosition();

};

#endif