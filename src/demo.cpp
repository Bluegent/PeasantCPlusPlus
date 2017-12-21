#include<irrlicht.h>
#include <GameWindow.h>
#include <GameCamera.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
int main()
{
	GameWindow game(video::EDT_OPENGL,1366,768,L"Peasants",false);
	game.init();

	ISceneManager* smgr = game.getSceneManager();
	IGUIEnvironment* guienv = game.getGuiEnvironment();

	guienv->addStaticText(L"Hello World! This is the Irrlicht Software renderer!",
		rect<s32>(10, 10, 260, 22), true);
	scene::IMeshSceneNode* node = smgr->addMeshSceneNode(smgr->getMesh("cube.obj"), 0, -1, core::vector3df(0.f, 0.f, 0.f),
		core::vector3df(0.f, 0.f, 0.f), core::vector3df(10.0f, 10.0f, 10.0f));

	node->setMaterialFlag(video::EMF_LIGHTING, false);
	//node->setMaterialTexture(0, driver->getTexture("cube.png"));
	ICameraSceneNode* camera =smgr->addCameraSceneNode(0, vector3df(0, 50, -50), vector3df(0, 5, 0));
	GameCamera* gc=new GameCamera(camera);
	camera->setFarValue(1000.f);
	game.getDevice()->setEventReceiver(gc);
	game.loop();

	return 0;
}