#include "GameObject.h"

GameObject::GameObject(Ogre::Entity* gameEntity)
{
	m_gameEntity = gameEntity;
}

GameObject::GameObject(const GameObject& obj) 
{
	if (*this != obj) 
	{
		m_gameEntity = obj.m_gameEntity;
	}
}

GameObject::GameObject(const GameObject && obj)
{

}

GameObject::~GameObject()
{
}

GameObject & GameObject::operator=(const GameObject & obj)
{
	return *this;
}

GameObject & GameObject::operator=(const GameObject && obj)
{
	return *this;
}

bool GameObject::operator!=(const GameObject & rhs)
{
	return !(*this == rhs);
}

bool GameObject::operator==(const GameObject& rhs) 
{
	if (m_gameEntity != rhs.m_gameEntity)
		return false;
	if (m_nameObject != rhs.m_nameObject)
		return false;

	return true;
}

