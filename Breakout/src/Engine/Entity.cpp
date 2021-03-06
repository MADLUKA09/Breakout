#include "Entity.h"
#include <math.h>

GameManager* Entity::gm = GameManager::Get();

Entity::Entity()
{
	m_Position.x = 0;
	m_Position.y = 0;

	m_Active = true;
}

Entity::Entity(float x, float y)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Active = true;
}

Entity::~Entity() {}

void Entity::entityInit() {
	this->init();
}

void Entity::entityOnKeyboardDown(const SDL_Keycode& KC)
{
	this->onKeyboardDown(KC);
}

void Entity::entityOnKeyboardUp(const SDL_Keycode& KC)
{
	this->onKeyboardUp(KC);
}

void Entity::entityUpdate() 
{
	if (!this->isActive())
		return;
	this->update();
	this->bodyUpdate();
}

void Entity::entityRender()
{
	if (!this->isActive())
		return;
	this->render();
}

void Entity::destroy() {
	this->m_Active = false;
	this->bodyDestroy();
}