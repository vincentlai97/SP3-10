#include "PlayerCharacter.h"

PlayerCharacter::PlayerCharacter(Vector3 position, Mesh* sprite)
: m_acceleration(0, 0, 0)
, m_jumpState(NOT_JUMPING)
, m_jumpHeight(0)
, Character(position, sprite)
, move(false)
{
	m_size = SMALLSIZE;
}

PlayerCharacter::~PlayerCharacter()
{
}

void PlayerCharacter::UpdateVelocity(double dt)
{
	m_velocity = 0;
}

void PlayerCharacter::UpdatePosition(double dt, const TileMap *tileMap)
{

	Vector3 position = m_position;
	position.x += m_velocity.x ;
	
	if (tileMap->getTile(position.x, floor(position.y)) > 4 || tileMap->getTile(position.x, ceil(position.y)) > 4)
	{
		m_velocity.x = 0;
	}

	position = m_position;
	position.y += m_velocity.y;
	
	if (tileMap->getTile(floor(position.x + (1 - m_size.x)), position.y) > 4 || tileMap->getTile(ceil(position.x - (1 - m_size.x)), position.y) > 4)
	{
		m_velocity.y = 0;
	}
	
	m_position += m_velocity * dt;
	m_VirtualPosition += m_velocity;

	float speed = 2;

	if (m_VirtualPosition != m_position)
	{
		move = true;
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
				move = false;
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
				move = false;
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
				move = false;
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
				move = false;
			}
		}
	}
	
	UpdateVelocity(dt);
}

void PlayerCharacter::UpdateSprite()
{
}

void PlayerCharacter::Update(double dt, const TileMap *tileMap)
{
	Character::Update(dt, tileMap);
	UpdatePosition(dt, tileMap);
}

void PlayerCharacter::moveUp()
{
	m_velocity.y += 1;
}

void PlayerCharacter::moveDown()
{
	m_velocity.y -= 1;
}

void PlayerCharacter::moveLeft()
{
	m_velocity.x -= 1;
}

void PlayerCharacter::moveRight()
{
	m_velocity.x += 1;
}

void PlayerCharacter::jump()
{
	if (m_jumpState == NOT_JUMPING)
	{
		m_jumpState = JUMPING;
		m_jumpHeight = 0;
	}
}

int PlayerCharacter::TouchItem(const TileMap *tileMap)
{
	return tileMap->getTile(m_position.x, floor(m_position.y));
}

void PlayerCharacter::RemoveItem(const TileMap *tileMap)
{
	tileMap->SetTile(m_position.x, floor(m_position.y),-1);
}

bool PlayerCharacter::getMove()
{
	return move;
}