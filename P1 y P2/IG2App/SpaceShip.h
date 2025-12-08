#pragma once
#include "IG2Object.h"
#include "DataSizes.h"

class SpaceShip : public IG2Object {
public:
	explicit SpaceShip(Vector3 pos, SceneNode* node, SceneManager* sceneMng);
private:
	SceneNode* _sphereNode;
	Entity* _sphereEntity;
};

