#include "Entity.h"
#include <math.h>

GameManager* Entity::gm = GameManager::Get();

Entity::Entity()
{
	m_Position.x = 0;
	m_Position.y = 0;
	m_Parent = nullptr;

	m_Active = true;
}

Entity::Entity(float x, float y, std::shared_ptr<Entity> parent)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Parent = parent;

	m_Active = true;
}

void Entity::entityInit() {}

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
	this->update();
	this->bodyUpdate();
	for (SubObjectVector::const_iterator it = m_SubObjects.begin(); it != m_SubObjects.end(); ++it)
		(*it)->entityUpdate();
}

void Entity::entityRender()
{
	this->render();
	for (SubObjectVector::const_iterator it = m_SubObjects.begin(); it != m_SubObjects.end(); ++it)
		(*it)->entityRender();
}

void Entity::addSubObject(std::shared_ptr<Entity> ent)
{
	m_SubObjects.push_back(ent);
}

void Entity::removeSubobject(std::shared_ptr<Entity> ent) {
	for (EntityVector::const_iterator it = m_SubObjects.begin(); it != m_SubObjects.end(); ++it) {
		if (*it == ent)
			m_SubObjects.erase(it);
	}
}

void Entity::destroy() {
	this->m_Active = false;
	if (m_Parent != nullptr)
		m_Parent->removeSubobject(std::shared_ptr<Entity> (this));
}