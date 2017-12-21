#ifndef GAMECAMERA_H
#define GAMECAMERA_H
#include<irrlicht.h>

using namespace irr;
class GameCamera :public IEventReceiver {
public:
	GameCamera();
	GameCamera(scene::ICameraSceneNode* camera);
	virtual bool OnEvent(const SEvent& event);

private:
	u32 cameraMove = 10;
	scene::ICameraSceneNode* m_camera;

};
#endif // GAMEWINDOW_H
