#ifndef PLAYERCHARACTER_H
#define PLAYERCHARACTER_H

#include "Character.h"

const Vector3 SMALLSIZE(0.7f, 0.8f, 0);
#define WALKING_NUMFRAMES 5
#define WALKINGSPRITE_TIME 0.3f

#define MAX_SPEED 3

class PlayerCharacter : public Character
{
private:
	enum SPRITE
	{
		IDLE_RIGHT = 0,
		WALKING_RIGHT,
		WALKING_RIGHT_END = WALKING_RIGHT + WALKING_NUMFRAMES - 1,
		JUMPING_RIGHT,
		CROUCHING_RIGHT,
		IDLE_LEFT = 16,
		WALKING_LEFT,
		WALKING_LEFT_END = WALKING_LEFT + WALKING_NUMFRAMES - 1,
		JUMPING_LEFT,
		CROUCHING_LEFT,
	};
	enum JUMP_STATE
	{
		NOT_JUMPING,
		JUMPING,
		FALLING,
	};

	Vector3 m_acceleration;
	JUMP_STATE m_jumpState;
	float m_jumpHeight;

	void UpdateVelocity(double dt);
	void UpdatePosition(double dt, const TileMap *tileMap);
	void UpdateSprite();

public:
	PlayerCharacter(Vector3 position = Vector3(), Mesh* sprite = NULL);
	~PlayerCharacter();

	void Update(double dt, const TileMap *tileMap);

	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	void jump();

};

#endif