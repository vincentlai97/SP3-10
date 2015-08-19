#include "Item.h"

Item::Item(void)
{
	Name = "";
	ID = -1;
	count = 0;
	onground = false;
}

Item::~Item(void)
{
}

Item::Item(string Name,int ID, int count, bool onground)
{
	this->Name = Name;
	this->ID = ID;
	this->count = count;
	this->onground = onground;
}

string Item::getName(void)
{
	return Name;
}

int Item::getID(void)
{
	return ID;
}

int Item::getCount(void)
{
	return count;
}

bool Item::getOnground(void)
{
	return onground;
}

void Item::SetName(string Name)
{
	this->Name = Name;
}

void Item::SetID(int ID)
{
	this->ID = ID;
}

void Item::SetCount(int count)
{
	this->count = count;
}

void Item::SetOnground(bool onground)
{
	this->onground = onground;
}

void Item::SetNull(void)
{
	Name = "";
	ID = -1;
	count = 0;
	onground = false;
}

void Item::Looted(void)
{
	onground = false;
}

void Item::Set(string Name,int ID,int count , bool onground)
{
	this->Name = Name;
	this->ID = ID;
	this->count = count;
	this->onground = onground;

}

void Item::Loot(Item a)
{
	this->Name = a.Name;
	this->ID = a.ID;
	this->count += a.count;
	this->onground = a.onground;
}

void Item::setMesh(Mesh* a)
{
	itemMesh = a;
}

Mesh* Item::getMesh()
{
	return itemMesh;
}