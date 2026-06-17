#pragma once
#include "IG2Object.h"
#include "OgreParticleSystem.h"
#include "OgreParticleEmitter.h"

#include "DataSizes.h"

class Engine : public IG2Object {
public:
	Engine(Vector3 pos, SceneNode* node, SceneManager* sm);
};