#ifndef GAME_LOGIC_LOOP_H
#define GAME_LOGIC_LOOP_H
#include "GameState.h"

#include <mutex>

/* 
Class for running game logic independent of rendering times.
You should only implement the constructor and the updateState methods, 
everything else should be usable out of the box. */
class GameLogicLoop 
{
public:
	

	//Where interval is tick rate in seconds (i.e. 0.010 means we update every 10 ms).
	GameLogicLoop(const double & interval = 10);
	~GameLogicLoop();

	//Entry point.
	void startThread();
	
	/*
	Retrieve a game state that contains instructions on how to process current game objects
	The mapping from GameState.object  to a rendered object should be done externally.
	*/
	const GameState & getRenderState() const { return m_renderState; }

	//Lock state for current scope to retrieve a game state for rendering.
	std::lock_guard<std::mutex> & getStateLock() { return std::lock_guard<std::mutex>(m_gameStateMutex); }

private:
	//Substep interval for physics calculation.
	static const double m_baseTickTime;

	std::thread * _internalThread;
	bool m_running;

	void loop();

protected:
	virtual void updateState(const double & currentTime, const double & deltaTime) = 0;

	GameState m_renderState; 
	GameState m_internalState;
	std::mutex m_gameStateMutex;

	const double m_updateInterval;
};
#endif // !GAME_LOGIC_LOOP_H
