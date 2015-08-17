#include "Character.h"

Character::Character(Vector3 position, Mesh* sprite)
: m_position(position)
, m_velocity(0, 0, 0)
, m_size(0, 0, 0)
, m_sprite(sprite)
, m_spriteState(0)
, m_spriteTime(0)
{
}

Character::~Character()
{
}

const Vector3 Character::getPosition() const
{
	return m_position;
}

const Vector3 Character::getVelocity() const
{
	return m_velocity;
}

int Character::getSpriteState()
{
	return m_spriteState;
}

bool CheckCollision(Character *first, Character *second)
{
	if (first->m_position.x < (second->m_position.x + second->m_size.x / 2) &&
		(first->m_position.x + first->m_size.x / 2) > second->m_position.x)
	if (first->m_position.y < (second->m_position.y + second->m_size.y / 2) &&
		(first->m_position.y + first->m_size.y / 2) > second->m_position.y)
		return true;
	return false;
}