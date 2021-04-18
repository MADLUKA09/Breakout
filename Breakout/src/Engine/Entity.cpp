#include "Entity.h"

GameManager* Entity::gm = GameManager::Get();

Entity::Entity()
{
	m_Position.x = 0;
	m_Position.y = 0;
}

Entity::Entity(int x, int y)
{
	m_Position.x = x;
	m_Position.y = y;
}

void Entity::entityInit() {}

void Entity::entityUpdate() 
{
	this->update();
}

void Entity::entityRender()
{
	this->render();
}