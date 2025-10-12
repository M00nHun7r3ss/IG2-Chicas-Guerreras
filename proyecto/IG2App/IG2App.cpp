#include "IG2App.h"

using namespace Ogre;
using namespace std;

bool IG2App::keyPressed(const OgreBites::KeyboardEvent& evt){
        
    // ESC key finished the rendering...
    if (evt.keysym.sym == SDLK_ESCAPE){
        getRoot()->queueEndRendering();
    }

    _hero->keyPressed(evt);
    std::cout << _lab->getBlockPosition(_hero->getPosition()) << std::endl;

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
    luz->setDiffuseColour(0.75, 0.75, 0.75);*/

    mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
    //mLightNode = mCamNode->createChildSceneNode("nLuz");
    //mLightNode->attachObject(luz);
    //mLightNode->setDirection(Ogre::Vector3(0, 0, -1)); //Luz de frente
    //mLightNode->setDirection(Ogre::Vector3(0, 1, 0)); //Luz de abajo
    //mLightNode->setDirection(Ogre::Vector3(-1, -0.25, 0.25)); //Luz de lado

    //------------------------------------------------------------------------
    //Hero creation
    _hero = new Hero(Vector3::ZERO, mSM->getRootSceneNode()->createChildSceneNode("nSinbad"), mSM);

    //------------------------------------------------------------------------
    //Labyrinth creation
    _lab = new Labyrinth("stage1.txt", mSM, _hero);

    //Movemos la camara para que mire al laberinto
    // TODO luego cambiar para que parezca un libro.
    mCamNode->setPosition(_lab->getPos().x, 3000, _lab->getPos().z);
    mCamNode->lookAt(_lab->getPos(), Ogre::Node::TS_WORLD);
 
}

void IG2App::frameRendered(const Ogre::FrameEvent& evt)
{
    _lab->canHeroGoForward();
    //Update del Hero
    _hero->frameRendered(evt);

    std::cout << _lab->getBlockPosition(_hero->getPosition()) << std::endl;
    std::cout << _hero->getDirection() << std::endl;
}


