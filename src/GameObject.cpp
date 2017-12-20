#include "GameObject.h"

GameObject::GameObject()
{
}

GameObject::GameObject(const GameObject& obj) 
{
	
}

GameObject::GameObject(const GameObject && obj)
{

}

GameObject::~GameObject()
{
}

GameObject & GameObject::operator=(const GameObject & obj)
{
	return *this;
}

GameObject & GameObject::operator=(const GameObject && obj)
{
	return *this;
}
