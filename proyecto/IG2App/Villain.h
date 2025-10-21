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

class Villain : public Character{
public:
	explicit Villain(Vector3 initPos, SceneNode* node, SceneManager* sceneMng);

	void frameRendered(const Ogre::FrameEvent& evt) override; // update

	Vector3 getDirection() { return _direction; }

	//void setCanGoForward(bool _canGo) { _canGoForward = _canGo; } TODO quiza


private:
	// Elementos del cuerpo del villano
	Entity* _vHead;
	Entity* _vBody;
	Entity* _vFeet;
	Entity* _vArm1R;
	Entity* _vArm1L;
	Entity* _vArm2R;
	Entity* _vArm2L;
	Entity* _vArm3R;
	Entity* _vArm3L;

	SceneNode* _nHead;
	SceneNode* _nBody;
	SceneNode* _nFeet;
	SceneNode* _nArm1R;
	SceneNode* _nArm2R;
	SceneNode* _nArm3R;
	SceneNode* _nArm1L;
	SceneNode* _nArm2L;
	SceneNode* _nArm3L;

	Timer* _timer;
	bool _animDir;
	double _angle;
	void armsRotation();

	SceneNode* createChildEntity(SceneNode* parentNode, std::string mesh,
		Vector3 pos, Vector3 scale,
		Degree angle = Degree(0), Vector3 rotateOn = Vector3(0, 0, 0));

	// Elementos del movimiento del villano
	Vector3 _direction;
	const double VILLAIN_SPEED = 50.0;

	//bool _canGoForward; TODO quiza


	void move(double t) override;
	void rotate() override;
};