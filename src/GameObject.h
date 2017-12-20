#ifndef GAME_BASE_H
#define GAME_BASE_H

#include <Ogre.h>
#include <OgreInput.h>

#include <string>

class GameObject
{
private:
	std::shared_ptr<Ogre::Entity> m_gameEntity;
	std::string m_nameObject;
public:
	GameObject();

	GameObject(const GameObject& obj);
	GameObject (const GameObject && obj);

	virtual ~GameObject();

	GameObject& operator=(const GameObject& obj);
	GameObject& operator=(const GameObject&& obj);
};

#endif