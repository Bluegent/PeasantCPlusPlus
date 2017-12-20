#include "GameObject.h"

GameObject::GameObject(Ogre::SceneNode* node):m_node(node)
{
}

GameObject::GameObject(const GameObject& obj) 
{
	if (*this != obj) 
	{
		*this = obj;
	}
}

GameObject::GameObject(const GameObject && obj)
{
//TODO
}

GameObject::~GameObject()
{

}

GameObject & GameObject::operator=(const GameObject & obj)
{
	if (*this != obj)
	{
		m_node = obj.m_node;
	}

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
	if (m_node != rhs.m_node)
		return false;

	return true;
}

void GameObject::createChild(const std::string &name, const Ogre::Vector3 &translate, const Ogre::Quaternion &rotation)
{
	m_node->createChildSceneNode(name, translate, rotation);
}

void GameObject::attachEntity(Ogre::MovableObject * entity)
{
	if (m_node != nullptr) 
	{
		m_node->attachObject(entity);
	}
}
