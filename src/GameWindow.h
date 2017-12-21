#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H
#include<irrlicht.h>
using namespace irr;




class GameWindow {
private:

public:
	GameWindow();
	GameWindow(video::E_DRIVER_TYPE driverType, u32 width, u32 heigth, wchar_t* caption,bool fullScreen);
	bool init();
	void loop();
	void setCamera(scene::ICameraSceneNode* camera);
	
	
	scene::ISceneManager* getSceneManager() {
		return m_sceneManager;
	}
	scene::ICameraSceneNode* getCamera()
	{
		return m_camera;
	}
	gui::IGUIEnvironment * getGuiEnvironment()
	{
		return m_guiEnvironment;
	}
	IrrlichtDevice* getDevice() {
		return m_device;
	}



private:
	u32 m_width;
	u32 m_height;
	wchar_t* m_caption;
	bool m_fullScreen;

	video::E_DRIVER_TYPE m_driverType;
	IrrlichtDevice * m_device;
	video::IVideoDriver* m_driver;
	scene::ISceneManager* m_sceneManager;
	gui::IGUIEnvironment* m_guiEnvironment;

	scene::ICameraSceneNode* m_camera;
	
};
#endif // GAMEWINDOW_H
