#pragma once
#include "IG2Object.h"
#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include <string>

class Character : public IG2Object{
public:
	explicit Character(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, String mesh) : IG2Object(initPos, node, sceneMng, mesh){
		_traspasable = false;
	}

	explicit Character(Vector3 initPos, SceneNode* node, SceneManager* sceneMng) : IG2Object(initPos, node, sceneMng){
		_traspasable = false;
	}

protected:
	Vector3 _direction;

	virtual void move(double t) = 0;
	virtual void rotate() = 0;
};

