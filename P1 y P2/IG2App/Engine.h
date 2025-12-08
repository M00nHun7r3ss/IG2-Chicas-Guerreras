#pragma once
#include "IG2Object.h"
#include "DataSizes.h"

class Engine : public IG2Object {
public:
	explicit Engine(Vector3 pos, SceneNode* node, SceneManager* sceneMng);

private:
	SceneNode* _baseNode;
	Entity* _baseEntity;


};

