#pragma once

#include <OgreTrays.h>
#include "IG2Object.h"
#include "OgreBillboardSet.h"
#include "OgreParticleSystem.h"

#include "IG2ApplicationContext.h"
//#include "OgreApplicationContext.h" //TODO
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreTrays.h>
#include <OgreCameraMan.h>
#include <OgreInput.h>

#include <OgreEntity.h>
#include <OgreInput.h>
#include <OgreMath.h>
#include <OgreFrameListener.h>
#include <OgreMeshManager.h>
#include <SDL_keycode.h>
#include <iostream>


class Explosion : public IG2Object
{
public:
	explicit Explosion(Vector3 pos, SceneNode* node, SceneManager* sceneMng, int index);

private:
	SceneNode* _explosionParticles;

};

