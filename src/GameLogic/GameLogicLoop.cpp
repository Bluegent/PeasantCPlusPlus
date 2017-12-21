#include "GameLogicLoop.h"

const double GameLogicLoop::m_baseTickTime = 0.010;

//i.e 3610.12 means an hour, 10 seconds and 12 ms.
double getTimeInSecondsAsDouble()
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() / 1000.0;
}


GameLogicLoop::GameLogicLoop(const double & interval)
	: m_running(false)
	, _internalThread(0)
	, m_updateInterval(interval)
{

}

GameLogicLoop::~GameLogicLoop()
{
	m_running = false;
	if (_internalThread)
	{
		_internalThread->join();
		delete _internalThread;
	}
}

void GameLogicLoop::loop()
{
	m_running = true;
	GameState prevState = m_internalState;
	m_renderState = m_internalState;
	
	double currentTime = getTimeInSecondsAsDouble();
	double accumulator = 0.0;
	double totalTime = 0.0;

	while (m_running)
	{
		double newTime = getTimeInSecondsAsDouble();
		//Calculate how much time we have to simulate.
		double timeSinceLastUpdate = newTime - currentTime;
		
		currentTime = newTime;
		accumulator += timeSinceLastUpdate;

		//Substep calculations for accuracy. 
		while (accumulator >= m_baseTickTime && m_running)
		{
			updateState(totalTime, m_baseTickTime);
			totalTime += m_baseTickTime;
			accumulator -= m_baseTickTime;
		}
		
		//Interpolate between the last two states for smoothness.
		//Some of this can be removed for performance.
		double alpha = accumulator / m_baseTickTime;
		{
			//Lock rendering state while updating it.
			std::lock_guard<std::mutex> guard(m_gameStateMutex);
			for (uint32_t index = 0; index < m_internalState.states.size(); ++index)
			{
				m_renderState.states[index] = m_internalState.states[index] * alpha + prevState.states[index] * (1.0 - alpha);
			}
		}
		
		prevState = m_internalState;
		std::this_thread::sleep_for(std::chrono::milliseconds((int)(1000.0*m_updateInterval)));
		
	}
}

void GameLogicLoop::startThread()
{
	_internalThread = new std::thread(&GameLogicLoop::loop,this);
}

