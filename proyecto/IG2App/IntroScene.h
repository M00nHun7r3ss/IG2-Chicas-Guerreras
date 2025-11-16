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

#include "Scene.h"

class IntroScene : public Scene {

public:
    explicit IntroScene(SceneManager* sm, OgreBites::TrayManager* tm,
        Light* l, SceneNode* lp, SceneNode* ln,
        SceneNode* cn, OgreBites::CameraMan* cm);

    //virtual ~IntroScene(); // TODO hacer desconstructora bien.

    void update(const Ogre::FrameEvent& evt);

private:
    // Objects
    Entity* _sinbadEnt;
    SceneNode* _sinbadNode;
    Entity* _swordLeftEnt;
    Entity* _swordRightEnt;

    // consts
    const int MOVEMENT_LENGTH = 50;
    const double DURATION = 21.0;
    const Vector3 KEY_FRAME_POS = Vector3(0, 0, 0);
    const double DURATION_STEP = DURATION / 3.0;

    void createCamera();

    // Animation state
    AnimationState* _animationState;

    // Animation states for Sinbad
    AnimationState* _animStateDance;
    AnimationState* _animRunLegs;
    AnimationState* _animRunArms;

    // Flags to control the animations
    bool isDancing = false;
    bool isRunning = false;
};