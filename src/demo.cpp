#include<irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
int main()
{
	IrrlichtDevice *device =createDevice(video::EDT_OPENGL, dimension2d<u32>(640, 480), 16, false, false, false, 0);

	if (!device)
		return 1;

	device->setWindowCaption(L"Hello World! - Irrlicht Engine Demo");
	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();
	IGUIEnvironment* guienv = device->getGUIEnvironment();

	guienv->addStaticText(L"Hello World! This is the Irrlicht Software renderer!",
		rect<s32>(10, 10, 260, 22), true);
	scene::IMeshSceneNode* node = smgr->addMeshSceneNode(smgr->getMesh("cube.obj"), 0, -1, core::vector3df(0.f, 0.f, 0.f),
		core::vector3df(0.f, 0.f, 0.f), core::vector3df(10.0f, 10.0f, 10.0f));

	node->setMaterialFlag(video::EMF_LIGHTING, false);
	node->setMaterialTexture(0, driver->getTexture("cube.png"));
	ICameraSceneNode* camera = smgr->addCameraSceneNodeFPS(0);
		//smgr->addCameraSceneNode(0, vector3df(0, 50, -50), vector3df(0, 5, 0));
	camera->setFarValue(1000.f);
	while (device->run())
	{
		driver->beginScene(true, true, SColor(255, 100, 101, 140));

		smgr->drawAll();
		guienv->drawAll();

		driver->endScene();
	}
	device->drop();

	return 0;
}