#include <Ogre.h>
#include <OgreApplicationContext.h>
#include <OgreInput.h>
#include <OgreRTShaderSystem.h>
#include <stdio.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <ctime>
#include <cstdlib>

#include "GameObject.h"

using namespace Ogre;
using namespace OgreBites;

struct GameState
{
	bool running;
	std::vector<Vector3> objects;
};
static const int tentXNum = 30, tentYNum = 30;

class OgreGame
	: public ApplicationContext
	, public InputListener
{
public:
	OgreGame();
	virtual ~OgreGame() {}
	SceneNode* camNode;
	SceneNode* lightNode;
	Ogre::RaySceneQuery* mRaySceneQuery;
	Ogre::SceneNode* myManualObjectNode;
	Ogre::ManualObject* myManualObject;
	GameState myCopy;
	GameState *external;
	Camera* cam;
	SceneManager* scnMgr;
	std::vector<SceneNode*> tents; 
	bool clicked, rClick;
	void setup();
	bool keyPressed(const KeyboardEvent& evt);
	bool mouseMoved(const MouseMotionEvent& evt);
	bool mouseWheelRolled(const MouseWheelEvent& evt);
	bool mousePressed(const MouseButtonEvent& evt) { if (evt.button == SDL_BUTTON_RIGHT) rClick = true; else clicked = true;  return true; }
	bool mouseReleased(const MouseButtonEvent& evt);
	void process();
	bool frameEnded(const Ogre::FrameEvent& evt);
};


OgreGame::OgreGame()
	: ApplicationContext()
	, clicked(0)
	, rClick(0)
	, lightNode(0)
{
}


void OgreGame::setup()
{
	// do not forget to call the base first
	ApplicationContext::setup();
	addInputListener(this);

	// get a pointer to the already created root
	Root* root = getRoot();
	scnMgr = root->createSceneManager();

	// register our scene with the RTSS
	RTShader::ShaderGenerator* shadergen = RTShader::ShaderGenerator::getSingletonPtr();
	shadergen->addSceneManager(scnMgr);

	// -- tutorial section start --
	//! [turnlights]
	scnMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));
	//! [turnlights]

	//! [newlight]
	Light* light = scnMgr->createLight("MainLight");
	lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
	lightNode->attachObject(light);
	//! [newlight]

	//! [lightpos]
	lightNode->setPosition(0, 0, 10);
	//! [lightpos]

	//! [camera]
	camNode = scnMgr->getRootSceneNode()->createChildSceneNode();

	// create the camera
	cam = scnMgr->createCamera("myCam");
	cam->setNearClipDistance(1); // specific to this sample
	cam->setAutoAspectRatio(true);
	camNode->attachObject(cam);

	getRenderWindow()->addViewport(cam);

	camNode->setPosition(0, 0, 5); 
		
	for (int i = 0; i < tentXNum; ++i)
	{
		for (int j = 0; j < tentYNum; ++j)
		{
				//Entity* ogreEntity3 = scnMgr->createEntity("Tent.mesh");
				GameObject object = scnMgr->createEntity("Tent.mesh");
				SceneNode* ogreNode3 = scnMgr->getRootSceneNode()->createChildSceneNode();
				tents.push_back(ogreNode3);
				ogreNode3->setPosition(i*2.5, j*2.5, 0);
				ogreNode3->attachObject(ogreEntity3);



		}
	}

	// -- tutorial section end --
}


bool OgreGame::keyPressed(const KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_ESCAPE)
	{
		getRoot()->queueEndRendering();
	}
	return true;
}

bool OgreGame::mouseMoved(const MouseMotionEvent& evt)
{
	if (clicked)
	{
		Ogre::Vector3 pos = camNode->getPosition();
		camNode->setPosition(pos.x + evt.xrel*-0.02, pos.y + evt.yrel*0.02, pos.z);
	}
	else if (rClick)
	{
			int modifier = evt.yrel != 0 ? abs(evt.yrel) / evt.yrel : 1;
			camNode->pitch(Degree(-0.5* modifier));
	}
	return true;
}

bool OgreGame::mouseWheelRolled(const MouseWheelEvent & evt)
{
	Ogre::Vector3 pos = camNode->getPosition();
	camNode->setPosition(pos.x, pos.y, camNode->getPosition().z + evt.y*10*-1);
	return true;
}

bool OgreGame::mouseReleased(const MouseButtonEvent & evt) { 
	if (evt.button == SDL_BUTTON_RIGHT) 
		rClick = false; 
	else 
		clicked = false; 
	Vector2 mousePos(evt.x, evt.y);
	if (evt.button == SDL_BUTTON_LEFT)
	{
		Vector2 scrSize(getRenderWindow()->getWidth(), getRenderWindow()->getHeight());
		Ray mouseRay = cam->getCameraToViewportRay(evt.x/ scrSize.x, evt.y/ scrSize.y);
	
		mRaySceneQuery = scnMgr->createRayQuery(mouseRay);
		mRaySceneQuery->setSortByDistance(true);
		Ogre::RaySceneQueryResult& result = mRaySceneQuery->execute();
		printf("obj hit %d\n", result.size());
		Ogre::RaySceneQueryResult::iterator it = result.begin();
		for (; it != result.end(); it++)
		{
			it->movable->getParentNode()->roll(Degree(45));
			break;
		}
		scnMgr->destroyQuery(mRaySceneQuery);
	}
	return true; 
}
std::mutex g_pages_mutex;
void OgreGame::process()
{
	//lock it
	g_pages_mutex.lock();
	//copy it
	myCopy.objects = external->objects;
	g_pages_mutex.unlock();
	//unlock it
	for (int i = 0; i < myCopy.objects.size(); ++i)
	{
		tents[i]->pitch(Degree(myCopy.objects[i].x));
		tents[i]->yaw(Degree(myCopy.objects[i].y));
		tents[i]->roll(Degree(myCopy.objects[i].z));
	}

}

bool OgreGame::frameEnded(const Ogre::FrameEvent & evt)
{
	process();
	return true;
}


void gameLogicLoop(GameState * state)
{
	state->running = true;
	std::chrono::system_clock::time_point start, end;
	std::chrono::duration<double> diff;
	for(int i=0;i<tentXNum*tentYNum;++i)
		state->objects.push_back(Vector3());
	while (state->running)
	{
		//printf("elapsed:%1.1lf ms\n", diff.count());
		start = std::chrono::system_clock::now();
		//update game logic
		g_pages_mutex.lock();
		for (int i = 0; i < state->objects.size(); ++i)
		{
			state->objects[i].x = 0.01;
			state->objects[i].y = 0.1;
			state->objects[i].z = 1;
		}
		g_pages_mutex.unlock();
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		end = std::chrono::system_clock::now();
		diff = end - start;
	}
}

int main(int argc, char **argv)
{
	/*std::srand(std::time(nullptr));
	GameState gameState;
	std::thread gameLogic(gameLogicLoop,&gameState);
	OgreGame app;
	app.external = &gameState;
	app.initApp();
	app.getRoot()->startRendering();
	app.closeApp();

	gameState.running = false;
	gameLogic.join();*/

	return 0;
}
