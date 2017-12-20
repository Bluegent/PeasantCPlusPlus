#include <Ogre.h>
#include <OgreApplicationContext.h>
#include <OgreInput.h>
#include <OgreRTShaderSystem.h>
#include <stdio.h>
#include<iostream>

using namespace Ogre;
using namespace OgreBites;

class BasicTutorial1
	: public ApplicationContext
	, public InputListener
{
public:
	BasicTutorial1();
	virtual ~BasicTutorial1() {}

	void setup();
	bool keyPressed(const KeyboardEvent& evt);
	bool mouseMoved(const MouseMotionEvent& evt);
};


BasicTutorial1::BasicTutorial1()
	: ApplicationContext()
{
}


void BasicTutorial1::setup()
{
	// do not forget to call the base first
	ApplicationContext::setup();
	addInputListener(this);

	// get a pointer to the already created root
	Root* root = getRoot();
	SceneManager* scnMgr = root->createSceneManager();

	// register our scene with the RTSS
	RTShader::ShaderGenerator* shadergen = RTShader::ShaderGenerator::getSingletonPtr();
	shadergen->addSceneManager(scnMgr);

	// -- tutorial section start --
	//! [turnlights]
	scnMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));
	//! [turnlights]

	//! [newlight]
	Light* light = scnMgr->createLight("MainLight");
	SceneNode* lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
	lightNode->attachObject(light);
	//! [newlight]

	//! [lightpos]
	lightNode->setPosition(20, 80, 50);
	//! [lightpos]

	//! [camera]
	SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();

	// create the camera
	Camera* cam = scnMgr->createCamera("myCam");
	cam->setNearClipDistance(1); // specific to this sample
	cam->setAutoAspectRatio(true);
	camNode->attachObject(cam);

	// and tell it to render into the main window
	getRenderWindow()->addViewport(cam);
	//! [camera]

	//! [entity1]
	Entity* ogreEntity = scnMgr->createEntity("Tent.mesh");
	//! [entity1]

	//! [cameramove]
	camNode->setPosition(0, 0, 2.1); 
	//camNode->pitch(Degree(180));
	//! [cameramove]


	//! [entity3]
	Entity* ogreEntity3 = scnMgr->createEntity("Tent.mesh");
	SceneNode* ogreNode3 = scnMgr->getRootSceneNode()->createChildSceneNode();
	ogreNode3->setPosition(0, 0, 0);
	ogreNode3->scale(1, 1, 1);
	ogreNode3->attachObject(ogreEntity3);
	//! [entity3]


	// -- tutorial section end --
}


bool BasicTutorial1::keyPressed(const KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_ESCAPE)
	{
		getRoot()->queueEndRendering();
	}
	return true;
}

bool BasicTutorial1::mouseMoved(const MouseMotionEvent& evt)
{
	printf("%d\n",evt.xrel);
	return true;
}


int main(int argc, char **argv)
{
	BasicTutorial1 app;
	app.initApp();
	app.getRoot()->startRendering();
	app.closeApp();
	return 0;
}
