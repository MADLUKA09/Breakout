#include "Entity.h"

GameManager* Entity::gm = GameManager::Get();

Entity::Entity()
{
	m_Position.x = 0;
	m_Position.y = 0;

	m_Active = true;
}

Entity::Entity(int x, int y)
{
	m_Position.x = x;
	m_Position.y = y;

	m_Active = true;
}

void Entity::entityInit() {}

void Entity::entityHandleEvents() {
	this->handleEvents();
}

void Entity::entityUpdate() 
{
	moveByVelocity();
	this->update();
	this->bodyUpdate();

}

void Entity::entityRender()
{
	this->render();
}

void Entity::moveByVelocity() {
	setPosition(getPosition().x + getVelocity().x, getPosition().y + getVelocity().y);
}