#pragma once
#include "IG2ApplicationContext.h"
#include "IG2Object.h"
#include "Labyrinth.h"
#include "Hero.h"
#include "Villain.h"
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
#include "OgreBillboardSet.h"
#include "OgreParticleSystem.h"

#include "OgreAnimation.h"
#include <OgreSkeletonInstance.h>
#include <OgreBone.h>
#include <OgreKeyFrame.h>

#include "Bomb.h"

class Scene {

public:
    explicit Scene(SceneManager* sm, OgreBites::TrayManager* tm, 
        Light* l, SceneNode* lp, SceneNode* ln,
        SceneNode* cn, OgreBites::CameraMan* cm);
    virtual ~Scene() = default; // TODO eliminar bien las cosas luego.

protected:

    Ogre::SceneManager* _sceneMgr = nullptr;
    OgreBites::TrayManager* _trayMgr = nullptr;

    Ogre::Light* _light = nullptr;
    Ogre::SceneNode* _lightParent = nullptr;
    Ogre::SceneNode* _lightNode = nullptr;

    Ogre::SceneNode* _camNode = nullptr;
    OgreBites::CameraMan* _camMgr = nullptr;

    void createPlane(string mat, Vector3 pos, float width, float height);

    //Directional la comparten tanto la intro como el juego, asi que es general
    void createDirectionalLight();

};