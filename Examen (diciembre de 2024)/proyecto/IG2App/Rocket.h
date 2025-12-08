#pragma once
#include "IG2Object.h"
#include "DataSizes.h"

class Rocket : public IG2Object {
public:
	explicit Rocket(Vector3 pos, SceneNode* node, SceneManager* sceneMng);
private:
	SceneNode* _cubeNode;
	Entity* _cubeEntity;

	SceneNode* _sphereNode;
	Entity* _sphereEntity;
};

