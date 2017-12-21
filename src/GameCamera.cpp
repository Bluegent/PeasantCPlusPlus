#include<GameCamera.h>

GameCamera::GameCamera():
	m_camera(0)
{
}

GameCamera::GameCamera(scene::ICameraSceneNode * camera) :
	m_camera(camera)
{
}

bool GameCamera::OnEvent(const SEvent & event)
{
	core::vector3df position = m_camera->getPosition();
	switch (event.KeyInput.Key)
	{
	case irr::KEY_UP:
		position.Z += cameraMove;
		break;
	case irr::KEY_DOWN:
		position.Z -= cameraMove;
		break;
	case irr::KEY_LEFT:
		position.X -= cameraMove;
		break;
	case irr::KEY_RIGHT:
		position.X += cameraMove;
		break;
	}
	m_camera->setPosition(position);
	//m_camera->setRotation()
	return true;
}
