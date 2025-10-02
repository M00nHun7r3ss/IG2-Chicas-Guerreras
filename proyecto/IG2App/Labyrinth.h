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
#include "Wall.h"
#include "Empty.h"
#include "Hero.h"

class Labyrinth : public OgreBites::IG2ApplicationContext, OgreBites::InputListener {
public:
    explicit Labyrinth(String file, SceneManager* sceneMng);

    Hero* getHero() { return _hero; };
    
private:
    Hero* _hero;
};

