#ifndef MULTI_STATE_H
#define MULTI_STATE_H
#include <vector>
#include <functional>

//Function that calculates acceleration.
typedef std::function<double(const std::pair<double, double> &, const double &)> accelFunc;
typedef std::pair<double, double> positionAndVelocity;


/*
Self contained force vector that can calculate its value for the next simulation step.
*/
class DirectionalForceVector
{
public:
	DirectionalForceVector(const uint32_t & componentNum, accelFunc accel = nullptr);

	DirectionalForceVector & operator*=(const double & scalar);
	DirectionalForceVector operator*(const double & scalar) const; 
	DirectionalForceVector & operator+=(const DirectionalForceVector & other);
	DirectionalForceVector operator+(const DirectionalForceVector & other) const;

	void integrate(const double & currentTime, const double & deltaTime);

	const positionAndVelocity & operator[](const uint32_t & index) const
	{
		return m_components[index];
	}
	accelFunc accelerate;

protected:
	DirectionalForceVector getDerivate(const double & currentTime, const float & deltaTime, const DirectionalForceVector & derivate) const;
	std::vector<positionAndVelocity> m_components;
	

};

#endif