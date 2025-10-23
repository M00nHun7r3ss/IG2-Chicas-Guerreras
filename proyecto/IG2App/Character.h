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

class Character : public IG2Object
{
public:
	explicit Character(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, String mesh) : IG2Object(initPos, node, sceneMng, mesh){
		_traspasable = false;
	}

	explicit Character(Vector3 initPos, SceneNode* node, SceneManager* sceneMng) : IG2Object(initPos, node, sceneMng){
		_traspasable = false;
	}

	inline Vector3 getDirection() { return _direction; }
	inline void setDirection(Vector3 d) { _direction = d; }

protected:
	Vector3 _direction;


	virtual void move(double t) = 0;
	virtual void rotate() = 0;

};

