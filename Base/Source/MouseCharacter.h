#ifndef MOUSECHARACTER_H
#define MOUSECHARACTER_H

#include "Character.h"
#include "PlayerCharacter.h"

#define WALKING_NUMFRAMES 2
#define WALKINGSPRITE_TIME 0.3f

class MouseCharacter : public Character
{
private:
	enum SPRITE
	{
		WALKING_LEFT = 8,
		WALKING_LEFT_END = WALKING_LEFT + WALKING_NUMFRAMES - 1,
		WALKING_RIGHT = 10,
		WALKING_RIGHT_END = WALKING_RIGHT + WALKING_NUMFRAMES - 1,
		DEAD_LEFT = 12,
		DEAD_RIGHT,
	};

	bool m_active;
	PlayerCharacter *player;
	float m_deadTime;

	void UpdateVelocity(double dt);
	void UpdatePosition(double dt, const TileMap *tileMap);
	void UpdateSprite();

public:
	MouseCharacter(Vector3 position, Mesh *sprite = NULL, PlayerCharacter *player = NULL);
	MouseCharacter(Vector3 position, Mesh *sprite = NULL, float velocityx = 0, PlayerCharacter *player = NULL);
	~MouseCharacter();

	void Update(double dt, const TileMap *tileMap);

	virtual bool isActive() { return m_active; }
	void SetDead();
	virtual bool isDead() { return m_deadTime; }

};

#endif