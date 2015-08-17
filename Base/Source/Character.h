#ifndef CHARACTER_H
#define CHARACTER_H

#include "Mesh.h"
#include "Vector3.h"
#include "TileMap.h"

class Character
{
protected:
	Vector3 m_position;
	Vector3 m_velocity;
	Vector3 m_size;
	Mesh* m_sprite;
	int m_spriteState;
	float m_spriteTime;

public:
	Character(Vector3 position = Vector3(), Mesh* sprite = NULL);
	~Character();

	virtual void Update(double dt, const TileMap *tilemap) { m_spriteTime += dt; }

	const Vector3 getPosition() const;
	const Vector3 getVelocity() const;
	int getSpriteState();

	friend bool CheckCollision(Character *first, Character *second);

	virtual bool isActive() { return false; }
	virtual void SetDead() {}
	virtual bool isDead() { return false; }

};

#endif