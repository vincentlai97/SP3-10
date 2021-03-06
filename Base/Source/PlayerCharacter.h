#ifndef PLAYERCHARACTER_H
#define PLAYERCHARACTER_H

#include "Character.h"

const Vector3 SMALLSIZE(0.7f, 0.8f, 0);
#define WALKING_NUMFRAMES 4
#define WALKINGSPRITE_TIME 0.08f

//#define MAX_SPEED 3

class PlayerCharacter : public Character
{
private:
	enum SPRITE
	{
		WALKING_DOWN = 0,
		WALKING_DOWN_END = WALKING_DOWN + WALKING_NUMFRAMES - 1,	
		WALKING_LEFT = 4,
		WALKING_LEFT_END = WALKING_LEFT + WALKING_NUMFRAMES - 1,	
		WALKING_RIGHT = 8,
		WALKING_RIGHT_END = WALKING_RIGHT + WALKING_NUMFRAMES - 1,		
		WALKING_UP = 12,
		WALKING_UP_END = WALKING_UP + WALKING_NUMFRAMES - 1,
		IDLE_DOWN = 1,
		IDLE_LEFT = 5,
		IDLE_RIGHT = 9,
		IDLE_UP = 13,
	};
	enum JUMP_STATE
	{
		NOT_JUMPING,
		JUMPING,
		FALLING,
	};

	Vector3 m_acceleration;
	bool move;
	bool gamewin;

	void UpdateVelocity(double dt);
	void UpdatePosition(double dt, const TileMap *tileMap);
	void UpdateSprite();

	float SPEED;

public:
	PlayerCharacter(Vector3 position = Vector3(), Mesh* sprite = NULL);
	~PlayerCharacter();

	void Update(double dt, const TileMap *tileMap);

	Vector3 getAcceleration() const;
	Vector3 getDirection() const;

	bool moveUp();
	bool moveDown();
	bool moveLeft();
	bool moveRight();

	void idleUp();
	void idleDown();
	void idleLeft();
	void idleRight();

	bool getMove();

	bool PlayerDirUp();
	bool PlayerDirDown();
	bool PlayerDirLeft();
	bool PlayerDirRight();
	bool getWin();
	void setWin(bool);

	int GetSpeed(void);
	void SetSpeed(int speed);
};

#endif