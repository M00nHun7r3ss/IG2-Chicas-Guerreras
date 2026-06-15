#pragma once
#include "IG2Object.h"
#include "DataSizes.h"
#include "Engine.h"
class Airplane : public IG2Object {
public: 
	Airplane(Vector3 pos, SceneNode* node, SceneManager* sm);
};

