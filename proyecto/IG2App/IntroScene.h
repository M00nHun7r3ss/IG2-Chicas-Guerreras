#pragma once

#include <OgreTrays.h>
#include <OgreCameraMan.h>
#include <OgreEntity.h>
#include <OgreInput.h>

#include "OgreAnimation.h"
#include <OgreSkeletonInstance.h>
#include <OgreBone.h>
#include <OgreKeyFrame.h>

#include "OgreTimer.h"

#include "Scene.h"

class IntroScene : public Scene {

public:
    explicit IntroScene(SceneManager* sm, OgreBites::TrayManager* tm,
        Light* l, SceneNode* lp, SceneNode* ln,
        SceneNode* cn, OgreBites::CameraMan* cm, bool sceneType = false);

    //virtual ~IntroScene(); // TODO hacer desconstructora bien.

    void update(const Ogre::FrameEvent& evt);

    void setVisible(bool visible) override;

private:
    // TODO hacer que sean ig2objects y juntamos entidad y nodo.
    // Objects
    Entity* _sinbadEnt;
    SceneNode* _sinbadNode;
    Entity* _swordLeftEnt;
    Entity* _swordRightEnt;

    Entity* _ogreHeadEnt;
    SceneNode* _ogreHeadNode;

    Entity* _sphereEnt;
    SceneNode* _sphereNode;
    void createSphere();

    // consts
    const int MOVEMENT_LENGTH = 100;
    const double DURATION = 21.0;
    const double DURATION_STEP = DURATION / 9.0;

    Vector3 _sinbadKeyFramePos;
    Vector3 _ogreheadKeyFramePos;

    void createCamera();

    Timer* _timer = 0;

    // Animation state
    AnimationState* _sinbadAnimationState;
    AnimationState* _ogreheadAnimationState;

    // Animation states for Sinbad
    AnimationState* _animStateDance;
    AnimationState* _animRunLegs;
    AnimationState* _animRunArms;

    // Flags to control the animations
    bool _isDancing;
    bool _isRunning;
    bool _areSwordsAttached;

    void createSinbadAnim();
    void createOgreheadAnim();
};