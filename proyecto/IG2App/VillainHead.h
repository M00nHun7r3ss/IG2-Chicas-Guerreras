#pragma once

#include "IG2ApplicationContext.h"
#include "IG2Object.h"
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreTrays.h>
#include <OgreCameraMan.h>
#include <OgreEntity.h>
#include <OgreInput.h>
#include <SDL_keycode.h>
#include <OgreMeshManager.h>
#include <sstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <vector>
#include "Character.h"

class VillainHead : public IG2Object
{
public:
	explicit VillainHead(Vector3 initPos, SceneNode* node, SceneManager* sceneMng);
};
