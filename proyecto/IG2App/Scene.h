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
        SceneNode* cn, OgreBites::CameraMan* cm, bool sceneType);
    virtual ~Scene() = default; // TODO eliminar bien las cosas luego.

    virtual void setVisible(bool visible) {}
    bool getVisible() const { return _sceneType; };


protected:
    bool _sceneType; //False - IntroScene, True - GameScene

    SceneManager* _sceneMgr = nullptr;
    OgreBites::TrayManager* _trayMgr = nullptr;

    Light* _light = nullptr;
    SceneNode* _lightParent = nullptr;
    SceneNode* _lightNode = nullptr;

    Entity* _planeEntity;
    SceneNode* _planeNode = nullptr;

    SceneNode* _camNode = nullptr;
    OgreBites::CameraMan* _camMgr = nullptr;

    void createPlane(string mat, Vector3 pos, float width, float height);

    //Directional la comparten tanto la intro como el juego, asi que es general
    void createDirectionalLight();

};