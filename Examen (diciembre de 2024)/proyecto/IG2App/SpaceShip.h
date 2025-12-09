#pragma once
#include "IG2Object.h"
#include "DataSizes.h"
#include "Engine.h"

class SpaceShip : public IG2Object {
public:
	explicit SpaceShip(Vector3 pos, SceneNode* node, SceneManager* sceneMng);

	void update();
private:
	SceneNode* _sphereNode;
	Entity* _sphereEntity;

	Engine* _engine;

	Timer* _timer;
};

