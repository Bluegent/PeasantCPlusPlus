#include "GameWindow.h"

GameWindow::GameWindow() :
	m_driverType(video::EDT_OPENGL),
	m_width(800),
	m_height(600),
	m_caption(L"Peasants"),
	m_fullScreen(false),
	m_device(0),
	m_driver(0),
	m_sceneManager(0),
	m_guiEnvironment(0),
	m_camera(0)
{

}

GameWindow::GameWindow(video::E_DRIVER_TYPE driverType, u32 width, u32 heigth, wchar_t * caption,bool fullScreen) :
	m_driverType(driverType),
	m_width(width),
	m_height(heigth),
	m_caption(caption),
	m_fullScreen(fullScreen),
	m_device(0),
	m_driver(0),
	m_sceneManager(0),
	m_guiEnvironment(0),
	m_camera(0)

{

}

bool GameWindow::init()
{
	m_device = createDevice(m_driverType, core::dimension2d<u32>(m_width, m_height), 16, m_fullScreen, false, false, 0);
	if (!m_device)
		return false;
	m_device->setWindowCaption(m_caption);
	
	m_driver = m_device->getVideoDriver();
	if (!m_driver)
		return false;
	m_sceneManager = m_device->getSceneManager();
	
	if (!m_sceneManager)
		return false;
	
	m_guiEnvironment = m_device->getGUIEnvironment();
	if (!m_guiEnvironment)
		return false;


	return true;
}

void GameWindow::loop()
{
	while (m_device->run())
	{
		m_driver->beginScene(true, true, video::SColor(255, 100, 101, 140));

		m_sceneManager->drawAll();
		m_guiEnvironment->drawAll();

		m_driver->endScene();
	}
	m_device->drop();
}

void GameWindow::setCamera(scene::ICameraSceneNode* camera)
{
	m_camera = camera;
}

