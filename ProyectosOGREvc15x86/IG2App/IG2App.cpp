#include "IG2App.h"

using namespace Ogre;
using namespace std;

bool IG2App::keyPressed(const OgreBites::KeyboardEvent& evt){
        
    // ESC key finished the rendering...
    if (evt.keysym.sym == SDLK_ESCAPE){
        getRoot()->queueEndRendering();
    }
    
  return true;
}

void IG2App::shutdown(){
    
  mShaderGenerator->removeSceneManager(mSM);
  mSM->removeRenderQueueListener(mOverlaySystem);  
					
  mRoot->destroySceneManager(mSM);  

  delete mTrayMgr;  mTrayMgr = nullptr;
  delete mCamMgr; mCamMgr = nullptr;
  
  // do not forget to call the base 
  IG2ApplicationContext::shutdown(); 
}

void IG2App::setup(void){
    
    // Caja de dialogo inicial
    //mRoot->showConfigDialog(OgreBites::getNativeConfigDialog());

    // do not forget to call the base first
    IG2ApplicationContext::setup();

    // Create the scene manager
    mSM = mRoot->createSceneManager();

    // Register our scene with the RTSS
    mShaderGenerator->addSceneManager(mSM);

    mSM->addRenderQueueListener(mOverlaySystem);
    mTrayMgr = new OgreBites::TrayManager("TrayGUISystem", mWindow.render);
    mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
    addInputListener(mTrayMgr);
    
    // Adds the listener for this object
    addInputListener(this);
    setupScene();
}

void IG2App::setupScene(void){
    
    //------------------------------------------------------------------------
    // Creating the camera
    
    Camera* cam = mSM->createCamera("Cam");
    cam->setNearClipDistance(1);
    cam->setFarClipDistance(10000);
    cam->setAutoAspectRatio(true);
    //cam->setPolygonMode(Ogre::PM_WIREFRAME);
            
    mCamNode = mSM->getRootSceneNode()->createChildSceneNode("nCam");
    mCamNode->attachObject(cam);

    mCamNode->setPosition(0, 0, 1000);
    mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);
    
    // and tell it to render into the main window
    Viewport* vp = getRenderWindow()->addViewport(cam);

    mCamMgr = new OgreBites::CameraMan(mCamNode);
    addInputListener(mCamMgr);
    mCamMgr->setStyle(OgreBites::CS_ORBIT);
    
    
    //------------------------------------------------------------------------
    // Creating the light
    
    mSM->setAmbientLight(ColourValue(0.7, 0.8, 0.9));
    /*Light* luz = mSM->createLight("Luz");
    luz->setType(Ogre::Light::LT_DIRECTIONAL);
    luz->setDiffuseColour(0.7, 0.8, 0.9);*/

    mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
    //mLightNode = mCamNode->createChildSceneNode("nLuz");
    //mLightNode->attachObject(luz);
    //mLightNode->setDirection(Ogre::Vector3(0, 0, -1)); //Luz de frente
    //mLightNode->setDirection(Ogre::Vector3(0, 1, 0)); //Luz de abajo
    //mLightNode->setDirection(Ogre::Vector3(-1, -0.25, 0.25)); //Luz de lado

    //------------------------------------------------------------------------
    // Creating Sinbad

    Ogre::Entity* ent0 = mSM->createEntity("Sinbad.mesh");
    mSinbadNode = mSM->getRootSceneNode()->createChildSceneNode("nSinbad");
    mSinbadNode->attachObject(ent0);

    // Show bounding box
    mSinbadNode->showBoundingBox(false);
    
    // Set position of Sinbad
    //mSinbadNode->setPosition(x, y, z);
    
    // Set scale of Sinbad
    mSinbadNode->setScale(20, 20, 20);
    
    //mSinbadNode->yaw(Ogre::Degree(45));
    mSinbadNode->setVisible(true);    

    //------------------------------------------------------------------------
    // Creating Sword

    Ogre::Entity* ent1 = mSM->createEntity("Sword.mesh");
    mSwordNode = mSM->getRootSceneNode()->createChildSceneNode("nSword"); // IMPORTANTE CAMBIAR NOMBRE
    mSwordNode->attachObject(ent1);

    // Show bounding box
    mSwordNode->showBoundingBox(false);

    // Set position of Sinbad
    //mSinbadNode->setPosition(x, y, z);

    // Set scale of Sinbad
    mSwordNode->setScale(20, 20, 20);

    mSwordNode->yaw(Ogre::Degree(45));
    mSwordNode->setVisible(false);

    //------------------------------------------------------------------------
    // Creating Damaged Helmet

    Ogre::Entity* ent2 = mSM->createEntity("DamagedHelmet.mesh");
    mHelmetNode = mSM->getRootSceneNode()->createChildSceneNode("nHelmet");
    mHelmetNode->attachObject(ent2);

    // Show bounding box
    mHelmetNode->showBoundingBox(false);

    // Set position of Sinbad
    //mHelmetNode->setPosition(x, y, z);

    // Set scale of Sinbad
    mHelmetNode->setScale(20, 20, 20);

    mHelmetNode->yaw(Ogre::Degree(180));
    mHelmetNode->setVisible(false);

    //------------------------------------------------------------------------
    // Creating Ogre Head

    Ogre::Entity* ent3 = mSM->createEntity("ogrehead.mesh");
    mOgreHead = mSM->getRootSceneNode()->createChildSceneNode("nOgrehead");
    mOgreHead->attachObject(ent3);

    // Show bounding box
    mOgreHead->showBoundingBox(false);

    // Set position of Sinbad
    //mOgreHead->setPosition(x, y, z);

    // Set scale of Sinbad
    mOgreHead->setScale(10, 10, 10);

    mOgreHead->yaw(Ogre::Degree(0));
    mOgreHead->setVisible(false);

    //------------------------------------------------------------------------
    // Creating Facial

    Ogre::Entity* ent4 = mSM->createEntity("facial.mesh");
    mFacial = mSM->getRootSceneNode()->createChildSceneNode("nFacial");
    mFacial->attachObject(ent4);

    // Show bounding box
    mFacial->showBoundingBox(false);

    // Set position of Sinbad
    mFacial->setPosition(0, -50, 0);

    // Set scale of Sinbad
    mFacial->setScale(5, 5, 5);

    //mFacial->yaw(Ogre::Degree(0));
    mFacial->setVisible(false);

    //------------------------------------------------------------------------
    // Creating Bath

    Ogre::Entity* ent5 = mSM->createEntity("RomanBathLower.mesh");
    mBathLower = mSM->getRootSceneNode()->createChildSceneNode("mBathLower");
    mBathLower->attachObject(ent5);

    // Show bounding box
    mBathLower->showBoundingBox(true);

    // Set position of Sinbad
    mBathLower->setPosition(0, -20, 0);

    // Set scale of Sinbad
    mBathLower->setScale(1, 1, 1);

    //mBathLower->yaw(Ogre::Degree(0));
    mBathLower->setVisible(true);

    Ogre::Entity* ent6 = mSM->createEntity("RomanBathUpper.mesh");
    mBathUpper = mSM->getRootSceneNode()->createChildSceneNode("mBathUpper");
    mBathUpper->attachObject(ent6);

    // Show bounding box
    mBathUpper->showBoundingBox(true);

    // Set position of Sinbad
    mBathUpper->setPosition(0, -20, 0);

    // Set scale of Sinbad
    mBathUpper->setScale(1, 1, 1);

    //mBathUpper->yaw(Ogre::Degree(0));
    mBathUpper->setVisible(true);

    Ogre::Entity* ent7 = mSM->createEntity("Columns.mesh");
    mColumns = mSM->getRootSceneNode()->createChildSceneNode("mColumns");
    mColumns->attachObject(ent7);

    // Show bounding box
    mColumns->showBoundingBox(true);

    // Set position of Sinbad
    mColumns->setPosition(0, -20, 0);

    // Set scale of Sinbad
    mColumns->setScale(1, 1, 1);

    //mColumns->yaw(Ogre::Degree(0));
    mColumns->setVisible(true);
}


