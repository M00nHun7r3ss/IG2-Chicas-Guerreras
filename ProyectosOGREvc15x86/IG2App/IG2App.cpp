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
    // CUBOS PARA P1

    /*
    IG2Ojbect* cube = nullpts;

    //nuevo objeto, con pos inicial, creamos un nodo nuevo para el hijo, en en SceneManager, con la malla de cubo
    cube = new IG2Object(Vector3::ZERO, mSM->getRootSceneNode()->createChildrenNode(), mSM, "cube.mesh");
    
    //Se pueden poner COUTS
    cout << "Size:" << cube->calculateBoxSize() << endl;

    //Se pueden resizear
    cube->setScale(IG2App::BLOCK_SIZE /  cube->calculateBoxSize() );
    cout << "New size:" << cube->calculateBoxSize() << endl;
    */

    //------------------------------------------------------------------------
    // LABERINTO

    /*
    //Se recomienda usar un solo vector de IG2Object para almacenar, en vez de la matriz, pero intentar trabajar en modo cuadricula
    //Tener en cuenta el tamaño de los bloques etcetc...

    Crear nodo para el laberinto, y luego los cubos son hijos

    //Los vacios son objeto sin malla



    
    
    
    
    */



}


