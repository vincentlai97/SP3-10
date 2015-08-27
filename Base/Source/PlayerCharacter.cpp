#include "PlayerCharacter.h"

PlayerCharacter::PlayerCharacter(Vector3 position, Mesh* sprite)
: m_acceleration(0, 0, 0)
, Character(position, sprite)
, move(false)
, gamewin(false)
{
	m_size = SMALLSIZE;
}

PlayerCharacter::~PlayerCharacter()
{
}

void PlayerCharacter::UpdateVelocity(double dt)
{
	m_velocity.SetZero();
	m_velocity += m_acceleration * MAX_SPEED;
}

void PlayerCharacter::UpdatePosition(double dt, const TileMap *tileMap)
{
	Vector3 position = m_position;
	position.x += m_velocity.x * dt;
	if (m_velocity.x < 0)
		position.x = floor(position.x);
	else if (m_velocity.x > 0)
		position.x = ceil(position.x);
	if (tileMap->getTile(position.x, position.y) > 0 //Collision Check X
		|| position != m_virtualPosition) //Check if player already reached his destination
	{
		if (position != m_virtualPosition) m_position.x = m_virtualPosition.x;
		m_velocity.x = 0;
		m_acceleration.x = 0;
	}

	position = m_position;
	position.y += m_velocity.y * dt;
	if (m_velocity.y < 0)
		position.y = floor(position.y);
	else if (m_velocity.y > 0)
		position.y = ceil(position.y);
	if (tileMap->getTile(position.x, position.y) > 0 //Collision Check Y
		|| position != m_virtualPosition) //Check if player already reached his destination
	{
		if (position != m_virtualPosition) m_position.y = m_virtualPosition.y;
		m_velocity.y = 0;
		m_acceleration.y = 0;
	}
	
	m_position += m_velocity * dt;
}

void PlayerCharacter::UpdateSprite()
{
	if (m_velocity.x < 0)
	{
		m_spriteState = m_spriteTime / WALKINGSPRITE_TIME;
		m_spriteState %= WALKING_NUMFRAMES;
		m_spriteState += WALKING_LEFT;
	}
	else if (m_velocity.x > 0)
	{
		m_spriteState = m_spriteTime / WALKINGSPRITE_TIME;
		m_spriteState %= WALKING_NUMFRAMES;
		m_spriteState += WALKING_RIGHT;
	}
	else if (m_velocity.y < 0)
	{
		m_spriteState = m_spriteTime / WALKINGSPRITE_TIME;
		m_spriteState %= WALKING_NUMFRAMES;
		m_spriteState += WALKING_DOWN;
	}
	else if (m_velocity.y > 0)
	{
		m_spriteState = m_spriteTime / WALKINGSPRITE_TIME;
		m_spriteState %= WALKING_NUMFRAMES;
		m_spriteState += WALKING_UP;
	}
	else
	{
		if (m_spriteState >= WALKING_UP && m_spriteState <= WALKING_UP_END)
			m_spriteState = IDLE_UP;
		else if (m_spriteState >= WALKING_DOWN && m_spriteState <= WALKING_DOWN_END)
			m_spriteState = IDLE_DOWN;
		else if (m_spriteState >= WALKING_LEFT && m_spriteState <= WALKING_LEFT_END)
			m_spriteState = IDLE_LEFT;
		else if (m_spriteState >= WALKING_RIGHT && m_spriteState <= WALKING_RIGHT_END)
			m_spriteState = IDLE_RIGHT;
	}
}

void PlayerCharacter::Update(double dt, const TileMap *tileMap)
{
	Character::Update(dt, tileMap);

	UpdateVelocity(dt);
	UpdatePosition(dt, tileMap);
	UpdateSprite();
}

Vector3 PlayerCharacter::getAcceleration() const
{
	return m_acceleration;
}

Vector3 PlayerCharacter::getDirection() const
{
	switch (m_spriteState)
	{
	case IDLE_UP: return Vector3(0, 1, 0);
	case IDLE_DOWN: return Vector3(0 , -1, 0);
	case IDLE_LEFT: return Vector3(-1, 0, 0);
	case IDLE_RIGHT: return Vector3(1, 0, 0);
	default: return Vector3();
	}
}


bool PlayerCharacter::moveUp()
{
	if (m_spriteState != IDLE_UP)
		m_spriteState = IDLE_UP;
	else
	{
		m_acceleration.y += 1;
		m_virtualPosition = m_position;
		m_virtualPosition.y = floor(m_virtualPosition.y) + 1;
		return true;
	}

	return false;
}

bool PlayerCharacter::moveDown()
{
	if (m_spriteState != IDLE_DOWN)
		m_spriteState = IDLE_DOWN;
	else
	{
		m_acceleration.y -= 1;
		m_virtualPosition = m_position;
		m_virtualPosition.y = ceil(m_virtualPosition.y) - 1;
		return true;
	}

	return false;
}

bool PlayerCharacter::moveLeft()
{
	if (m_spriteState != IDLE_LEFT)
		m_spriteState = IDLE_LEFT;
	else
	{
		m_acceleration.x -= 1;
		m_virtualPosition = m_position;
		m_virtualPosition.x = ceil(m_virtualPosition.x) - 1;
		return true;
	}
	return false;
}

bool PlayerCharacter::moveRight()
{
	if (m_spriteState != IDLE_RIGHT)
		m_spriteState = IDLE_RIGHT;
	else
	{
		m_acceleration.x += 1;
		m_virtualPosition = m_position;
		m_virtualPosition.x = floor(m_virtualPosition.x) + 1;
		return true;
	}
	return false;
}

void PlayerCharacter::idleUp()
{
	m_spriteState = IDLE_UP;
}

void PlayerCharacter::idleDown()
{
	m_spriteState = IDLE_DOWN;
}

void PlayerCharacter::idleLeft()
{
	m_spriteState = IDLE_LEFT;
}

void PlayerCharacter::idleRight()
{
	m_spriteState = IDLE_RIGHT;
}

bool PlayerCharacter::getWin()
{
	return gamewin;
}

void PlayerCharacter::setWin(bool a)
{
	gamewin = a;
}