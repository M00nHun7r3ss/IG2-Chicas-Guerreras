#pragma once

#include "IG2ApplicationContext.h"
#include "IG2Object.h"
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreTrays.h>
#include <OgreCameraMan.h>
#include <OgreEntity.h>
#include <OgreInput.h>
#include <SDL_keycode.h>
#include <OgreMeshManager.h>
#include <sstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <vector>
#include "Character.h"
#include "VillainHead.h"
#include "VillainBody.h"
#include "VillainHelix.h"

class Villain : public Character{
public:
	explicit Villain(Vector3 initPos, SceneNode* node, SceneManager* sceneMng);

	void frameRendered(const Ogre::FrameEvent& evt) override; // update

	Vector3 getDirection() { return _direction; }

	//void setCanGoForward(bool _canGo) { _canGoForward = _canGo; } TODO quiza


private:
	// Elementos del cuerpo del villano
	VillainHead* _vHead;
	VillainBody* _vBody;
	VillainHelix* _vHelix;


	// Elementos del movimiento del villano
	Vector3 _direction;
	const double VILLAIN_SPEED = 50.0;

	//bool _canGoForward; TODO quiza

	void move(double t) override;
	void rotate() override;

};