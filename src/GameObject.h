#ifndef GAME_BASE_H
#define GAME_BASE_H

#include <Ogre.h>
#include <OgreInput.h>

class GameObject
{
private:
	Ogre::Entity* m_gameEntity;
	std::string m_nameObject;
public:
	GameObject(Ogre::Entity* gameEntity);

	GameObject(const GameObject& obj);
	GameObject (const GameObject && obj);

	virtual ~GameObject();

	GameObject& operator=(const GameObject& obj);
	GameObject& operator=(const GameObject&& obj);

	bool operator!=(const GameObject& obj);
	bool operator ==(const GameObject& obj);
};

#endif