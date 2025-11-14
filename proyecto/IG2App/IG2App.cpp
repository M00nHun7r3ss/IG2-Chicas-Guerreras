#include "IG2App.h"

#include "Bomb.h"

using namespace Ogre;
using namespace std;

bool IG2App::keyPressed(const OgreBites::KeyboardEvent& evt){
        
    // ESC key finished the rendering...
    if (evt.keysym.sym == SDLK_ESCAPE){
        getRoot()->queueEndRendering();
    }

    if (evt.keysym.sym == SDLK_p) {// p de pegar
        _hero->damagePlayer();
    }

    _hero->keyPressed(evt);

	return true;
}

void IG2App::shutdown(){
    
  mShaderGenerator->removeSceneManager(mSM);
  mSM->removeRenderQueueListener(mOverlaySystem);  
					
  mRoot->destroySceneManager(mSM);  

  delete mTrayMgr;  mTrayMgr = nullptr;
  delete mCamMgr; mCamMgr = nullptr;
  delete _lab; _lab = nullptr;
  //delete _hero; _hero = nullptr;
  /*for (Villain* v : _villains) {
      delete v;
      v = nullptr;
  }
  _villains.clear();*/
  
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

    //UI DERECHA
    mLabel = mTrayMgr->createLabel(OgreBites::TL_BOTTOMRIGHT, "Titulo", "Stage: 1");
    mTextBox = mTrayMgr->createTextBox(OgreBites::TL_BOTTOMRIGHT, "Caja", "Game Info Here!", 250, 100);

    addInputListener(mTrayMgr);
    
    // Adds the listener for this object
    addInputListener(this);
    setupScene();
}

void IG2App::createCamera(){
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
}

void IG2App::createPlane(){
   MeshManager::getSingleton().createPlane("mPlane1080x800",
        ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        Plane(Vector3::UNIT_Y, 0),
        _lab->getWidth(), _lab->getHeight(), 100, 80,
        true, 1, 1.0, 1.0, Vector3::UNIT_Z);
    Ogre::Entity* plane = mSM->createEntity("mPlane1080x800");
    Ogre::SceneNode* mSceneNewNode = mSM->getRootSceneNode()->createChildSceneNode("floor");
    mSceneNewNode->setPosition(_lab->getWidth() / 2 - 50, -_lab->getBoxSize().y / 2, _lab->getHeight() / 2 + 50);
    mSceneNewNode->attachObject(plane);
    plane->setMaterialName(_lab->getFloorMaterial());
}

void IG2App::createDirectionalLight() {
    mSM->setAmbientLight(ColourValue(0.7, 0.8, 0.9));
    light = mSM->createLight("Directional");
    light->setType(Ogre::Light::LT_DIRECTIONAL);
    light->setDiffuseColour(0.75, 0.75, 0.75);
    // Node with the light attached
    mLightNode = mCamNode->createChildSceneNode("nLuz");
    mLightNode->attachObject(light);
}

void IG2App::createSpotLight() {
    //Luz spotlight
    light = mSM->createLight("spotLight");
    light->setType(Light::LT_SPOTLIGHT);
    light->setSpotlightInnerAngle(Ogre::Degree(5.0f));
    light->setSpotlightOuterAngle(Ogre::Degree(60.0f));
    light->setSpotlightFalloff(3.0f);
    light->setDiffuseColour(1.0f, 1.0f, 1.0f);
    // Node with the light attached
    mLightNode = mSM->getRootSceneNode()->createChildSceneNode();
    mLightNode->setPosition(_hero->getPosition().x, 800, _hero->getPosition().z);
    mLightNode->setDirection(Ogre::Vector3(0, -1, 0));
    mLightNode->attachObject(light);
}

void IG2App::createPointLight() {
    //Luz Point
    light = mSM->createLight("pointLight");
    light->setType(Light::LT_POINT);
    light->setDiffuseColour(1.0f, 1.0f, 1.0f);
    light->setAttenuation(3200, 1.0, 0.0014, 0.00000007);
    // Node with the light attached
    mLightNode = mSM->getRootSceneNode()->createChildSceneNode();
    mLightNode->setPosition(_hero->getPosition());
    mLightNode->attachObject(light);
}

void IG2App::setupScene(void){
    // Creating the camera
    createCamera();

    // Hero creation
    _hero = new Hero(Vector3::ZERO, mSM->getRootSceneNode()->createChildSceneNode("nSinbad"), mSM);

    // Labyrinth and villains creation
    _lab = new Labyrinth("stage1wv.txt", mSM, _hero, _villains);
    
    //Floor
    createPlane();

    //BOOOOOMBAAAA
    bomba = new Bomb(Vector3::ZERO, mSM->getRootSceneNode()->createChildSceneNode(), mSM);
    bomba->setScale(Vector3(1, 1, 1));

    //Movemos la camara para que mire al laberinto
    mCamNode->setPosition(_lab->getPos().x, 3000, _lab->getPos().z  - 1250);
    mCamNode->lookAt(_lab->getPos(), Ogre::Node::TS_WORLD);

    //------------------------------------------------------------------------
	// Creating the light
    switch (_lab->getLightType()) {
	    case 0: createDirectionalLight(); break;
        case 1: createSpotLight(); break;
        case 2: createPointLight(); break;
        default: break;
    }
}

void IG2App::frameRendered(const Ogre::FrameEvent& evt)
{
    // updates
    checkCollisions();
    _hero->update(evt);

    //Mira el bloque de delante, ve si es traspasable, y lo setea en el hero
    Vector2 nextBlock = _lab->getCharacterForwardBlock(_hero);
    bool next = _lab->getBlockType(nextBlock);
    _hero->setCanGoForward(next);

    for (int i = 0; i < _villains.size(); ++i){
        //_villains[1]->setDirection(_lab->calculateRandomDir(_villains[1]));
        //_villains[1]->rotate();
        _villains[i]->update(evt);
    }

    //Bombas
    bomba->update(evt);

    //Actualizamos UI de vida y puntos
    mTextBox->setText("Lives: " + std::to_string(_hero->getLives()) + "\nPoints: " + std::to_string(_hero->getPoints()));

    //El spotlight se actualiza con la pos del player
    mLightNode->setPosition(_hero->getPosition().x, 800, _hero->getPosition().z);
}

void IG2App::checkCollisions()
{
    AxisAlignedBox heroAABox = _hero->getAABB();
    bool collides = false;

    int i = 0;
    while (i < _villains.size() && !collides) {
	    collides = heroAABox.intersects(_villains[i]->getAABB());
        i++;
    }

    //Si colisionan y aun quedan vidas...
    if (collides && _hero->getLives() > 0) { _hero->damagePlayer(); }

    if (_hero->getLives() == 0){
        getRoot()->queueEndRendering();
    }
}


