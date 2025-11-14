#pragma once

#include <OgreTrays.h>
#include "IG2Object.h"
#include "OgreBillboardSet.h"
#include "OgreParticleSystem.h"


class Explosion : public IG2Object
{
public:
	explicit Explosion(Vector3 pos, SceneNode* node, SceneManager* sceneMng);

private:
	SceneNode* _explosionParticles;

};

