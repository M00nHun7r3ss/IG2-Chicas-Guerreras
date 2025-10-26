#pragma once
#include "IG2Object.h"
#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include <string>

class Character : public IG2Object{
public:
	explicit Character(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, String mesh) : IG2Object(initPos, node, sceneMng, mesh){
		_traspasable = false;
		_direction = Vector3::ZERO;
	}

	explicit Character(Vector3 initPos, SceneNode* node, SceneManager* sceneMng) : IG2Object(initPos, node, sceneMng){
		_traspasable = false;
		_direction = Vector3::ZERO;
	}

	Vector3 getDirection() { return _direction; }
	void setDirection(Vector3 newDir) { _direction = newDir; }

protected:
	Vector3 _direction;

	virtual void move(double t) = 0;
	virtual void rotate() = 0;
};

