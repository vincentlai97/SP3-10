#pragma once

#include "Model.h"

class CMainMenuModel : public Model
{
public:
	enum COMMANDS{
		MOVE_UP,
		MOVE_DOWN,
		ENTER,
		NUM_COMMANDS,

	};
protected:
	enum MainMenu{
		BACKGROUND,
		START_BUTTON,
		LOAD_BUTTON,
		EXIT_BUTTON,

		START_BUTTON2,
		LOAD_BUTTON2,
		EXIT_BUTTON2,

		NUM_MENU,
	};

	Mesh* meshList[NUM_MENU];

public:
	virtual void Init();
	virtual void Update(double dt);

	void setCommands(int command);

	Mesh* getBackgroundMesh();
	Mesh* getStartMesh();
	Mesh* getLoadMesh();
	Mesh* getExitMesh();

	Mesh* getStartMesh2();
	Mesh* getLoadMesh2();
	Mesh* getExitMesh2();

	int getCount(void);
private:
	int counter;
	bool countminus;
	bool countplus;
	static bool ExitKey;
};

