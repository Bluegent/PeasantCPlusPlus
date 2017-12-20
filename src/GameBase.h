#ifndef GAME_BASE_H
#define GAME_BASE_H

#include <Ogre.h>
#include <OgreInput.h>

class GameBase
{
private:
	std::shared_ptr<Ogre::Entity> m_gameEntity;

public:
	GameBase();

	GameBase(const GameBase& obj);
	GameBase (const GameBase && obj);

	virtual ~GameBase();

	GameBase& operator=(const GameBase& obj);
	GameBase& operator=(const GameBase&& obj);
};

#endif