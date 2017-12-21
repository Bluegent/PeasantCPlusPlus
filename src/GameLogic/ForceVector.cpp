#include "ForceVector.h"

DirectionalForceVector::DirectionalForceVector(const uint32_t & componentNum, accelFunc accel)
	: m_components(componentNum)
	, accelerate(accel)
{

}

DirectionalForceVector DirectionalForceVector::getDerivate(const double & currentTime, const float & deltaTime, const DirectionalForceVector & derivate) const
{
	DirectionalForceVector res(m_components.size());
	for (uint32_t index = 0; index < m_components.size(); ++index)
	{
		res.m_components[index].first = m_components[index].first + derivate.m_components[index].first * deltaTime;
		res.m_components[index].second = m_components[index].second + derivate.m_components[index].second * deltaTime;
	}
	DirectionalForceVector output(m_components.size());
	for (uint32_t index = 0; index < m_components.size(); ++index)
	{
		output.m_components[index].first = res.m_components[index].second;
		if(accelerate)
			output.m_components[index].second = accelerate(res.m_components[index], currentTime+ deltaTime);
	}
	return output;
}

void DirectionalForceVector::integrate(const double & currentTime, const double & deltaTime)
{
	//RK4, more time consuming but more accurate.
	//Yes, I do realise this is way too complex for a game with barely anything moving, but hey, extensibility~
	/*
	DirectionalForceVector a = getDerivate(currentTime, 0.0, DirectionalForceVector(m_components.size()));
	DirectionalForceVector b = getDerivate(currentTime, deltaTime*0.5f, a);
	DirectionalForceVector c = getDerivate(currentTime, deltaTime*0.5f, b);
	DirectionalForceVector d = getDerivate(currentTime, deltaTime, c);

	for (uint32_t index = 0; index < m_components.size(); ++index)
	{
		double dxdt = 1.0 / 6.0 *(a.m_components[index].first + 2.0 * (b.m_components[index].first + c.m_components[index].first) + d.m_components[index].first);
		double dvdt = 1.0 / 6.0 *(a.m_components[index].second + 2.0 * (b.m_components[index].second + c.m_components[index].second) + d.m_components[index].second);
		m_components[index].first += dxdt * deltaTime;
		m_components[index].second += dvdt * deltaTime;
	}*/

	//implicit Euler integration.
	for (uint32_t index = 0; index < m_components.size(); ++index)
	{
		m_components[index].first += m_components[index].second * deltaTime;
		if(accelerate)
			m_components[index].second += accelerate(m_components[index], deltaTime) * deltaTime; 
	}

}

DirectionalForceVector &  DirectionalForceVector::operator*=(const double & scalar)
{
	for (uint32_t index = 0; index < m_components.size(); ++index)
	{
		m_components[index].first *= scalar;
		m_components[index].second *= scalar;
	}
	return *this;
}

DirectionalForceVector DirectionalForceVector::operator*(const double & scalar) const
{
	return  DirectionalForceVector(*this) *= scalar;
}

DirectionalForceVector &  DirectionalForceVector::operator+=(const DirectionalForceVector & other)
{
	for (uint32_t index = 0; index < m_components.size(); ++index)
	{
		m_components[index].first += other.m_components[index].first;
		m_components[index].second += other.m_components[index].second;
	}
	return *this;
}

DirectionalForceVector  DirectionalForceVector::operator+(const DirectionalForceVector & other) const
{
	return DirectionalForceVector(*this) += other;
}