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

protected:
	Mesh* meshList[NUM_MENU];
	Mesh* Text;
public:
	virtual void Init();
	virtual void Update(double dt);

	void setCommands(int command);

	Mesh* getBackgroundMesh();

	Mesh* getMesh(int a);

	int getCount(void);

	bool getChoose(void);

	Mesh* getTextMesh();

private:
	int counter;
	bool chooselvl;
};

