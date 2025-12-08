#ifndef __IG2App_H__
#define __IG2App_H__

#include "IG2ApplicationContext.h"
//#include "OgreApplicationContext.h" //TODO
#include <OgreSceneManager.h>
#include <OgreRTShaderSystem.h>  
#include <OgreSceneNode.h>
#include <OgreTrays.h>
#include <OgreCameraMan.h>
#include <OgreInput.h>

#include "IntroScene.h"
#include "GameScene.h"

class IG2App : public  OgreBites::IG2ApplicationContext, OgreBites::InputListener{
	//class IG2App : public  OgreBites::OgreApplicationContext, OgreBites::InputListener {
public:
    explicit IG2App() : IG2ApplicationContext("IG2App") { };  // new -> setup()
    //explicit IG2App() : OgreApplicationContext("IG2App") {};  // new -> setup()
    virtual ~IG2App() { };                                    // delete -> shutdown()
 
protected:
    virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);  // InputListener
    virtual void setup();
    virtual void shutdown();
  
    virtual void setupScene();
    virtual void frameRendered(const Ogre::FrameEvent& evt);

private:

    Ogre::SceneManager* mSM = nullptr;
    OgreBites::TrayManager* mTrayMgr = nullptr;

    Ogre::Light* light = nullptr;
    Ogre::SceneNode* mLightParent = nullptr;
    Ogre::SceneNode* mLightNode = nullptr;

    Ogre::SceneNode* mCamNode = nullptr;
    OgreBites::CameraMan* mCamMgr = nullptr;

    //Escenas TODO: Gestion paso de escenas con la s
    IntroScene* _introScene;
    GameScene* _gameScene;

    void createCamera();
};

#endif
