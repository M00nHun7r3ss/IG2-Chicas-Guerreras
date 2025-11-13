#ifndef __IG2App_H__
#define __IG2App_H__

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

#include "Bomb.h"

class IG2App : public  OgreBites::IG2ApplicationContext, OgreBites::InputListener{

public:
    explicit IG2App() : IG2ApplicationContext("IG2App") { };  // new -> setup()
    virtual ~IG2App() { };                                    // delete -> shutdown()
 
protected:
    virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);  // InputListener
    virtual void setup();
    virtual void shutdown();
  
    virtual void setupScene();
    virtual void frameRendered(const Ogre::FrameEvent& evt);
      
    Ogre::SceneManager* mSM = nullptr;
    OgreBites::TrayManager* mTrayMgr = nullptr;
    
    Ogre::Light* light = nullptr;
    Ogre::SceneNode* mLightParent = nullptr;
    Ogre::SceneNode* mLightNode = nullptr;
    
    Ogre::SceneNode* mCamNode = nullptr;
    OgreBites::CameraMan* mCamMgr = nullptr;

private:
    // Objects
    Hero* _hero = nullptr;
    Labyrinth* _lab = nullptr;
    std::vector<Villain*> _villains;
    Bomb* bomba;

    Ogre::SceneNode* mPSNode;

    //Para la ui de la vida y los puntos
    OgreBites::TextBox* mTextBox = nullptr;
    OgreBites::Label* mLabel = nullptr;

    void checkCollisions(); // TODO arreglar
    void createCamera();
    void createPlane();
    void createDirectionalLight();
    void createSpotLight();
    void createPointLight();
};

#endif
