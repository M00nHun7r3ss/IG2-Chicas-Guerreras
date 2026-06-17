#pragma once
#include "IG2Object.h"
#include "DataSizes.h"
#include "Engine.h"
class Airplane : public IG2Object {
public: 
	Airplane(Vector3 pos, SceneNode* node, SceneManager* sm);
	void update(float dt);
	void input(const OgreBites::KeyboardEvent& evt);
private:
	float _angle = 90.0f;
	float _rollSpeed = 0.0f;
	float _radius = 1000.0f;
};

