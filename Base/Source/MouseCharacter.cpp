#include "MouseCharacter.h"

#include "MyMath.h"

MouseCharacter::MouseCharacter(Vector3 position, Mesh* sprite, PlayerCharacter *player)
: m_active(false)
, player(player)
, m_deadTime(0.f)
, Character(position, sprite)
{
	m_size.Set(1, 0.5f, 0);
}

MouseCharacter::MouseCharacter(Vector3 position, Mesh* sprite, float velocityx, PlayerCharacter *player)
: m_active(false)
, player(player)
, m_deadTime(0.f)
, Character(position, sprite)
{
	m_size.Set(1, 0.5f, 0);
	m_velocity.Set(velocityx, 0, 0);
}

MouseCharacter::~MouseCharacter()
{
}

#define diff player->getPosition().x - m_position.x

void MouseCharacter::UpdateVelocity(double dt)
{
	if (m_deadTime == 0.f)
	{
		m_velocity.y += -9.8 * dt;
		//m_velocity.x = 3 * (diff) / abs(diff);
	}
	else if (m_deadTime < .5f)
	{
		m_velocity.y += 9.8 * dt;
	}
	else if (m_deadTime < 1.5f)
	{
		m_velocity.y -= 9.8 * dt;
	}
	else
	{
		m_active = false;
	}
}

#undef diff

void MouseCharacter::UpdatePosition(double dt, const TileMap *tileMap)
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
		m_velocity.x *= -1;
	}

	position = m_position;
	position.y += m_velocity.y * dt;
	if (m_velocity.y < 0)
		position.y = floor(position.y);
	else if (m_velocity.y > 0)
		position.y = ceil(position.y);
	if (tileMap->getTile(floor(position.x + (1 - m_size.x)), position.y) || tileMap->getTile(ceil(position.x - (1 - m_size.x)), position.y))
	{
		m_position.y = position.y + (m_velocity.y < -0.0f ? 1 : -1);
		m_velocity.y = 0;
	}

	m_position += m_velocity * dt;
}

void MouseCharacter::UpdateSprite()
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
}

void MouseCharacter::Update(double dt, const TileMap *tileMap)
{
	Character::Update(dt, tileMap);

	if (!m_active && m_deadTime == 0.f)
	{
		Vector3 target(player->getPosition());
		target.x = Math::Clamp(target.x, (float)tileMap->getNumOfTilesWidth() / 2.f, (float)tileMap->getMapWidth() - (float)tileMap->getNumOfTilesWidth() / 2.f);
		target.y = Math::Clamp(target.y, (float)tileMap->getNumOfTilesHeight() / 2.f, (float)tileMap->getMapHeight() - (float)tileMap->getNumOfTilesHeight() / 2.f);
		if (abs(m_position.x - target.x) < (float)tileMap->getNumOfTilesWidth() / 2.f)
		if (abs(m_position.y - target.y) < (float)tileMap->getNumOfTilesHeight() / 2.f)
			m_active = true;
	}
	else
	{
		UpdateVelocity(dt);
		UpdatePosition(dt, tileMap);
		if (m_deadTime == 0.f) UpdateSprite();
	}
	if (m_deadTime > 0.f)
		m_deadTime += dt;
}

void MouseCharacter::SetDead()
{
	if (m_deadTime == 0.f)
	{
		m_deadTime = 0.1f;
		m_velocity.SetZero();
		m_spriteState = (m_spriteState - 8) / 2 + DEAD_LEFT;
	}
}