#include "PlayerCharacter.h"

PlayerCharacter::PlayerCharacter(Vector3 position, Mesh* sprite)
: m_acceleration(0, 0, 0)
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

	m_velocity += m_acceleration * dt;
	m_velocity.x = Math::Clamp<float>(m_velocity.x, -MAX_SPEED, MAX_SPEED);
	m_jumpHeight += m_velocity.y * dt;
}

void PlayerCharacter::UpdatePosition(double dt, const TileMap *tileMap)
{
	Vector3 position = m_VirtualPosition;
	position.x += m_velocity.x * dt;
	if (m_velocity.x < 0)
		position.x = floor(position.x + (1 - m_size.x));
	else if (m_velocity.x > 0)
		position.x = ceil(position.x - (1 - m_size.x));
		
	if (tileMap->getTile(position.x, floor(position.y)) > 0 || tileMap->getTile(position.x, ceil(position.y)) > 0)
	{
		m_VirtualPosition.x = position.x + (m_velocity.x < -0.0f ? m_size.x : -m_size.x);
		m_velocity.x = 0;
	}

	position = m_VirtualPosition;
	position.y += m_velocity.y * dt;
	if (m_velocity.y < 0)
		position.y = floor(position.y);
	else if (m_velocity.y > 0)
		position.y = ceil(position.y);
	if (tileMap->getTile(floor(position.x + (1 - m_size.x)), position.y) > 0 || tileMap->getTile(ceil(position.x - (1 - m_size.x)), position.y) > 0)
	{
		m_VirtualPosition.y = position.y + (m_velocity.y < -0.0f ? 1 : -1);
		m_velocity.y = 0;
	}

	m_position += m_velocity * dt;
	float speed = 2;

	if (m_VirtualPosition != m_position)
	{
		if (m_position.x < m_VirtualPosition.x)
		{
			m_position.x += speed * dt;
			m_spriteState = m_spriteTime / WALKINGSPRITE_TIME;
			m_spriteState %= WALKING_NUMFRAMES;
			m_spriteState += WALKING_RIGHT;
			if (m_position.x >= m_VirtualPosition.x)
			{
				m_position.x = m_VirtualPosition.x;
				m_spriteState = IDLE_RIGHT;
			}
		}
		else if (m_position.x > m_VirtualPosition.x)
		{
			m_position.x -= speed * dt;
			m_spriteState = m_spriteTime / WALKINGSPRITE_TIME;
			m_spriteState %= WALKING_NUMFRAMES;
			m_spriteState += WALKING_LEFT;
			if (m_position.x <= m_VirtualPosition.x)
			{
				m_position.x = m_VirtualPosition.x;
				m_spriteState = IDLE_LEFT;
			}
		}
		else if(m_position.y < m_VirtualPosition.y)
		{
			m_position.y += speed * dt;
			m_spriteState = m_spriteTime / WALKINGSPRITE_TIME;
			m_spriteState %= WALKING_NUMFRAMES;
			m_spriteState += WALKING_UP;
			if (m_position.y >= m_VirtualPosition.y)
			{
				m_position.y = m_VirtualPosition.y;
				m_spriteState = IDLE_UP;
			}
		}
		else if(m_position.y > m_VirtualPosition.y)
		{
			m_position.y -= speed * dt;
			m_spriteState = m_spriteTime / WALKINGSPRITE_TIME;
			m_spriteState %= WALKING_NUMFRAMES;
			m_spriteState += WALKING_DOWN;
			if (m_position.y <= m_VirtualPosition.y)
			{
				m_position.y = m_VirtualPosition.y;
				m_spriteState = IDLE_DOWN;
			}
		}
	}
}

void PlayerCharacter::UpdateSprite()
{
	
}

void PlayerCharacter::Update(double dt, const TileMap *tileMap)
{
	Character::Update(dt, tileMap);

	UpdateVelocity(dt);
	UpdatePosition(dt, tileMap);
	UpdateSprite();

	m_acceleration.Set(0, 0, 0);
}

void PlayerCharacter::moveUp()
{
	m_VirtualPosition.y += 1;
}

void PlayerCharacter::moveDown()
{
	m_VirtualPosition.y -= 1;
}

void PlayerCharacter::moveLeft()
{
	m_VirtualPosition.x -= 1;
}

void PlayerCharacter::moveRight()
{
	m_VirtualPosition.x += 1;
}

void PlayerCharacter::jump()
{
	if (m_jumpState == NOT_JUMPING)
	{
		m_jumpState = JUMPING;
		m_jumpHeight = 0;
	}
}