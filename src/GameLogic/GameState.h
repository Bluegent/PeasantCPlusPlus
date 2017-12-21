#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "Utils/MathUtils.h"
#include "ForceVector.h"

#include <vector>

//This is purely for testing's sake. Applies a force that moves an object back and forth.
class BackAndForthFV : public DirectionalForceVector
{
public:
	BackAndForthFV()
		: DirectionalForceVector(1, std::bind(&BackAndForthFV::accel, this, std::placeholders::_1, std::placeholders::_2))
		, modifier(1)
	{
	}
	BackAndForthFV(const BackAndForthFV & other)
		: DirectionalForceVector(other)
		, modifier(other.modifier)
	{
		accelerate = std::bind(&BackAndForthFV::accel, this, std::placeholders::_1, std::placeholders::_2);
	}
	BackAndForthFV & operator*=(const double & scalar) { (*this) *= scalar; return *this; }
	BackAndForthFV operator*(const double & scalar) const { return BackAndForthFV(*this) *= scalar; }
	BackAndForthFV & operator+=(const BackAndForthFV & other) { (*this) += other; return *this; }
	BackAndForthFV operator+(const BackAndForthFV & other) const { return BackAndForthFV(*this) += other; }
protected:
	int modifier;
	double accel(const std::pair<double,double> component, const double & currentTime)
	{
		if (component.second >= 5)
			modifier = -1;
		if (component.second <= -5)
			modifier = 1;
		double accel;
		if (MathUtils::getSign(modifier) == MathUtils::getSign(component.second))
			accel = 4;		
		else
			accel = 10;
		return accel*modifier;
	}
};

class GameState
{
public:
	std::vector<BackAndForthFV> states;
	GameState()
	{
		
	}
	GameState(const GameState & other)
		:states(other.states)
	{

	}
	GameState & operator=(const GameState & other)
	{
		states = other.states;
		return *this;
	}

	void update(const double & currentTime, const double & deltaTime)
	{
		for (uint32_t index = 0; index < states.size(); ++index)
		{
			states[index].integrate(currentTime, deltaTime);
		}
	}

};
#endif // ! GAME_STATE_CLASS
