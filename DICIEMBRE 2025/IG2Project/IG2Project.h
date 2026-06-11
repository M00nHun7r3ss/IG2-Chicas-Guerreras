#ifndef __IG2PROJECT_H__
#define __IG2PROJECT_H__

#include <OgreApplicationContext.h>
#include <OgreSceneManager.h>
#include <OgreRTShaderSystem.h>       
#include <OgreSceneNode.h>
#include <OgreTrays.h>
#include <OgreCameraMan.h>
#include <OgreEntity.h>
#include <OgreInput.h>
#include <OgreMeshManager.h>
#include <sstream>
#include <iostream>
#include <string>
#include "Ogre.h"
#include <OgreWindowEventUtilities.h>
#include <SDL_keycode.h>
#include "DataSizes.h"


class IG2Project: public OgreBites::ApplicationContext, OgreBites::InputListener {

public:
    explicit IG2Project() : OgreBites::ApplicationContext("SinbadExample") {};
    virtual ~IG2Project() {};

protected:
    virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
    virtual void setup();
    virtual void shutdown();
    virtual void setupScene();
    void frameRendered(const Ogre::FrameEvent& evt) override;


    Ogre::SceneNode* mSinbadNode = nullptr;

    Ogre::SceneManager* mSM = nullptr;
    OgreBites::TrayManager* mTrayMgr = nullptr;

    Ogre::Light* light = nullptr;
    Ogre::SceneNode* mLightParent = nullptr;
    Ogre::SceneNode* mLightNode = nullptr;

    Ogre::SceneNode* mCamNode = nullptr;
    OgreBites::CameraMan* mCamMgr = nullptr;

private:
    void createCamera();
    void createLights();
    void createSinbad();
    void createFloor();

    // --- examen apartado 1
    void createInnerRings();
    void createOuterRings();
    SceneNode* _innerRingsNode;
    SceneNode* _outerRingsNode;
    std::vector<SceneNode*> _sphereNodes;
    bool _rotateSpheres = false;
    bool _rotateOuter = false;
    float _innerDir = 1.0f;

    // --- examen apartado 2
    void createSkybox();

    // --- examen apartado 3
    bool _particlesEnabled = false;
    std::vector<Ogre::ParticleSystem*> _particleSystems;

    // --- examen apartado 4
    Ogre::AnimationState* _sinbadAnimState = nullptr;
    void createSinbadAnimation();
};

#endif
