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

	int getCount(void);
private:
	int counter;
	bool countminus;
	bool countplus;
	static bool ExitKey;
};

