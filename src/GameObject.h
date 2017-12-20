#ifndef GAME_BASE_H
#define GAME_BASE_H

#include <Ogre.h>
#include <OgreMovableObject.h>

#include <OgreInput.h>

class GameObject
{
private:
	Ogre::SceneNode* m_node;
public:
	GameObject(Ogre::SceneNode* m_node);
	virtual ~GameObject();

	GameObject(const GameObject& obj);
	GameObject (const GameObject && obj);

	GameObject& operator=(const GameObject& obj);
	GameObject& operator=(const GameObject&& obj);

	bool operator!=(const GameObject& obj);
	bool operator ==(const GameObject& obj);

	Ogre::SceneNode* getSceneNode() const 
	{
		return m_node;
	}

	void setPosition(Ogre::Real x, Ogre::Real y, Ogre::Real z) 
	{
		m_node->setPosition(Ogre::Vector3(x,y,z));
	}

	void createChild(const std::string &name, const Ogre::Vector3 &translate = Ogre::Vector3::ZERO, const Ogre::Quaternion &rotate = Ogre::Quaternion::IDENTITY);

	void attachEntity(Ogre::MovableObject* entity);
};

#endif