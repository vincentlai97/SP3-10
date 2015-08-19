#pragma once
#include <string>
#include "Mesh.h"

using namespace std;

class Item
{
private:
	string Name;
	int ID;
	int count;
	bool onground;

	Mesh* itemMesh;
public:
	
	Item(void);
	~Item(void);

	Item(string,int,int,bool);

	string getName(void);
	int getID(void);
	int getCount(void);
	bool getOnground(void);

	void SetName(string);
	void SetID(int);
	void SetCount(int);
	void SetOnground(bool);

	void SetNull(void);
	void Looted(void);
	void Set(string,int,int,bool);

	void Loot(Item);
	
	void setMesh(Mesh*);
	Mesh* getMesh();
};

