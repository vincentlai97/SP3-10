#include "PlayerCharacter.h"

PlayerCharacter::PlayerCharacter(Vector3 position, Mesh* sprite)
: m_acceleration(0, -9.8, 0)
, m_jumpState(NOT_JUMPING)
, m_jumpHeight(0)
, Character(position, sprite)
{
	m_size = SMALLSIZE;
}

PlayerCharacter::~PlayerCharacter()
{

}

void PlayerCharacter::UpdateVelocity(double dt)
{
	if (m_acceleration.x == 0)
	{
		m_velocity.x *= (1 - dt * 5);
		if (m_velocity.x > -0.1 && m_velocity.x < 0.1) m_velocity.x = 0;
	}

	if (m_jumpState == JUMPING)
	{
		m_acceleration.y += 30;
	}
	if (m_jumpHeight > 0.5 && m_jumpState == JUMPING)
		m_jumpState = FALLING;

	m_velocity += m_acceleration * dt;
	m_velocity.x = Math::Clamp<float>(m_velocity.x, -MAX_SPEED, MAX_SPEED);
	m_jumpHeight += m_velocity.y * dt;
}

void PlayerCharacter::UpdatePosition(double dt, const TileMap *tileMap)
{
	Vector3 position = m_position;
	position.x += m_velocity.x * dt;
	if (m_velocity.x < 0)
		position.x = floor(position.x + (1 - m_size.x));
	else if (m_velocity.x > 0)
		position.x = ceil(position.x - (1 - m_size.x));
	if (tileMap->getTile(position.x, floor(position.y)) || tileMap->getTile(position.x, ceil(position.y)))
	{
		m_position.x = position.x + (m_velocity.x < -0.0f ? m_size.x : -m_size.x);
		m_velocity.x = 0;
	}

	position = m_position;
	position.y += m_velocity.y * dt;
	if (m_velocity.y < 0)
		position.y = floor(position.y);
	else if (m_velocity.y > 0)
		position.y = ceil(position.y);
	if (tileMap->getTile(floor(position.x + (1 - m_size.x)), position.y) || tileMap->getTile(ceil(position.x - (1 - m_size.x)), position.y))
	{
		if (m_velocity.y < 0) m_jumpState = NOT_JUMPING;
		else if (m_velocity.y > 0) m_jumpState = FALLING;

		m_position.y = position.y + (m_velocity.y < -0.0f ? 1 : -1);
		m_velocity.y = 0;
	}

	m_position += m_velocity * dt;
}

void PlayerCharacter::UpdateSprite()
{
	if (m_jumpState == NOT_JUMPING)
	{
		if (m_acceleration.x < 0)
		{
			m_spriteState = m_spriteTime / WALKINGSPRITE_TIME;
			m_spriteState %= WALKING_NUMFRAMES;
			m_spriteState += WALKING_LEFT;
		}
		else if (m_acceleration.x > 0)
		{
			m_spriteState = m_spriteTime / WALKINGSPRITE_TIME;
			m_spriteState %= WALKING_NUMFRAMES;
			m_spriteState += WALKING_RIGHT;
		}
		else
		{
			if (m_spriteState >= IDLE_LEFT && m_spriteState <= CROUCHING_LEFT)
				m_spriteState = IDLE_LEFT;
			else m_spriteState = IDLE_RIGHT;
		}
	}
	else
	{
		if (m_acceleration.x < 0)
		{
			m_spriteState = JUMPING_LEFT;
		}
		else if (m_acceleration.x > 0)
		{
			m_spriteState = JUMPING_RIGHT;
		}
		else
		{
			if (m_spriteState >= IDLE_LEFT && m_spriteState <= CROUCHING_LEFT)
				m_spriteState = JUMPING_LEFT;
			else m_spriteState = JUMPING_RIGHT;
		}
	}
}

void PlayerCharacter::Update(double dt, const TileMap *tileMap)
{
	Character::Update(dt, tileMap);

	UpdateVelocity(dt);
	UpdatePosition(dt, tileMap);
	UpdateSprite();

	m_acceleration.Set(0, -9.8, 0);
}

void PlayerCharacter::moveUp()
{
	m_acceleration.y += 5;
}

void PlayerCharacter::moveDown()
{
	m_acceleration.y -= 5;
}

void PlayerCharacter::moveLeft()
{
	m_acceleration.x -= 5;
}

void PlayerCharacter::moveRight()
{
	m_acceleration.x += 5;
}

void PlayerCharacter::jump()
{
	if (m_jumpState == NOT_JUMPING)
	{
		m_jumpState = JUMPING;
		m_jumpHeight = 0;
	}
}