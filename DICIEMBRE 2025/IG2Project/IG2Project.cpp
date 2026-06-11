#include "IG2Project.h"

using namespace std;
using namespace Ogre;


bool IG2Project::keyPressed(const OgreBites::KeyboardEvent& evt) {

    // ESC key finished the rendering...
    if (evt.keysym.sym == SDLK_ESCAPE) {
        getRoot()->queueEndRendering();
    }

    // multiplicamos por -1 para invertir la direccion de rotacion
    if (evt.keysym.sym == SDLK_s) { _innerDir *= -1.0f; }

    if (evt.keysym.sym == SDLK_f) { _rotateSpheres = !_rotateSpheres; }

    if (evt.keysym.sym == SDLK_d) { _rotateOuter = !_rotateOuter; }

    if (evt.keysym.sym == SDLK_a) {
        _particlesEnabled = !_particlesEnabled;

        for (ParticleSystem* ps : _particleSystems) {
            ps->setEmitting(_particlesEnabled);
        }
    }

    return true;
}


void IG2Project::shutdown() {

    mShaderGenerator->removeSceneManager(mSM);
    mSM->removeRenderQueueListener(mOverlaySystem);

    mRoot->destroySceneManager(mSM);

    delete mTrayMgr;  mTrayMgr = nullptr;
    delete mCamMgr; mCamMgr = nullptr;

    // do not forget to call the base 
    OgreBites::ApplicationContext::shutdown();
}

void IG2Project::setup(void) {

    // do not forget to call the base first
    OgreBites::ApplicationContext::setup();

    // Create the scene manager
    mSM = mRoot->createSceneManager();

    // Register our scene with the RTSS
    mShaderGenerator->addSceneManager(mSM);
        
    mSM->addRenderQueueListener(mOverlaySystem);
    //mTrayMgr = new OgreBites::TrayManager("TrayGUISystem", mWindow.render);
    mTrayMgr = new OgreBites::TrayManager("TrayGUISystem", getRenderWindow());
    mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
    addInputListener(mTrayMgr);

    // Adds the listener for this object
    addInputListener(this);
    setupScene();
}

void IG2Project::setupScene(void) {

    // Creating the camera
    createCamera();
    
    // Creating the light
    createLights();

    // Creating Sinbad and its animation
    createSinbad();
    createSinbadAnimation();
    
    // Creating the floor
    createFloor();  

    // create rings
    createInnerRings();
    createOuterRings();

    // ajustamos posicion
    _outerRingsNode->setPosition(Vector3(0.0f, DataSizes::OUTER_RING_RADIUS, 0.0f));
    _innerRingsNode->setPosition(Vector3(0.0f, DataSizes::OUTER_RING_RADIUS, 0.0f));

    // create skybox
    createSkybox();
}

// equivalente a update
void IG2Project::frameRendered(const Ogre::FrameEvent& evt) {
    float deltaTime = evt.timeSinceLastFrame;

    // anillo interior
    _innerRingsNode->yaw(Ogre::Degree(DataSizes::RING_SPEED * _innerDir * deltaTime));

    // anillo exterior
    if (_rotateOuter) {
        _outerRingsNode->pitch(Ogre::Degree(DataSizes::RING_SPEED * deltaTime));
    }

    // bolillas
    if (_rotateSpheres) {
        for (SceneNode* s : _sphereNodes) {
            s->yaw(Ogre::Degree(DataSizes::SPHERE_SPEED * deltaTime));
        }
    }

    if (_sinbadAnimState) _sinbadAnimState->addTime(deltaTime);
    _runbase->addTime(deltaTime);
    _runtop->addTime(deltaTime);
}

void IG2Project::createCamera() {
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
}

void IG2Project::createLights() {
    //mSM->setAmbientLight(ColourValue(0.5, 0.5, 0.5));

    Light* luz = mSM->createLight("Luz");
    luz->setType(Ogre::Light::LT_DIRECTIONAL);
    luz->setDiffuseColour(0.75, 0.75, 0.75);

    mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
    mLightNode->attachObject(luz);
    mLightNode->setDirection(Ogre::Vector3(-1, -1, -1));
}

void IG2Project::createSinbad() {
    Ogre::Entity* ent = mSM->createEntity("Sinbad.mesh");
    mSinbadNode = mSM->getRootSceneNode()->createChildSceneNode();
    mSinbadNode->attachObject(ent);

    /*
    //// Show bounding box
    //mSinbadNode->showBoundingBox(true);

    //mSinbadNode->yaw(Ogre::Degree(-45));
    //mSinbadNode->setVisible(false);
    */

    mSinbadNode->setScale(5, 5, 5);
    mSinbadNode->setPosition(DataSizes::SINBAD_INITIAL_POSITION);

    // para la animacion
    _runbase = ent->getAnimationState("RunBase");
    _runbase->setEnabled(true);
    _runbase->setLoop(true);
    _runtop = ent->getAnimationState("RunTop");
    _runtop->setEnabled(true);
    _runtop->setLoop(true);
    mSinbadNode->setInitialState(); 
}

void IG2Project::createFloor() {
    MeshManager::getSingleton().createPlane("floor", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        Plane(Vector3::UNIT_Y, 0),
        1500, 1500, 50, 50, true, 1, 5, 5,
        Vector3::UNIT_Z);

    Entity* entFloor = mSM->createEntity("exampleFloor", "floor");
    entFloor->setMaterialName("Floor");
    SceneNode* floorNode = mSM->getRootSceneNode()->createChildSceneNode();
    floorNode->attachObject(entFloor);
}

void IG2Project::createInnerRings() {
    _innerRingsNode = mSM->getRootSceneNode()->createChildSceneNode();

    // anillo interior
    for (int i = 0; i < DataSizes::NUM_SPHERES_PER_RING; ++i) {
        float angle = 2.0f * Ogre::Math::PI * i / DataSizes::NUM_SPHERES_PER_RING;

        float x = DataSizes::INNER_RING_RADIUS * cos(angle);
        float y = DataSizes::INNER_RING_RADIUS * sin(angle);

        Entity* sphere = mSM->createEntity("sphere.mesh");
        SceneNode* node = _innerRingsNode->createChildSceneNode();

        node->attachObject(sphere);
        node->showBoundingBox(true);
        _sphereNodes.push_back(node); // guardamos cada esfera

        // saca el centro de la esfera y la direccion del chorro
        Vector3 centerSphere(x, y, 0);
        Vector3 dir = (centerSphere - _innerRingsNode->getPosition()).normalisedCopy();

        // mete cada particula con su direccion y sus cosas
        ParticleSystem* ps = mSM->createParticleSystem(to_string(i), "example/smokeParticle");
        ps->setEmitting(false);
        SceneNode* particleNode = _innerRingsNode->createChildSceneNode();

        particleNode->setPosition(centerSphere + dir * DataSizes::SPHERE_SIZE.x);
        particleNode->attachObject(ps);
        _particleSystems.push_back(ps);

        ParticleEmitter* emitter = ps->getEmitter(0);

        if (i % 2 == 0) { // pares
            sphere->setMaterialName("RustedMetal"); 
            emitter->setColour(ColourValue(1.0f, 1.0f, 1.0f, 1.0f));
        }
        else { // impares
            sphere->setMaterialName("RustySteel"); 
            emitter->setColour(ColourValue(0.0f, 0.0f, 0.0f, 1.0f));
        }

        emitter->setDirection(dir);
        

        node->setPosition(centerSphere);
        node->setScale(Vector3(DataSizes::SPHERE_SIZE));
    }
}

void IG2Project::createOuterRings() {
    _outerRingsNode = mSM->getRootSceneNode()->createChildSceneNode();

    // anillo exterior
    for (int i = 0; i < DataSizes::NUM_SPHERES_PER_RING; ++i) {
        float angle = 2.0f * Ogre::Math::PI * i / DataSizes::NUM_SPHERES_PER_RING;

        float x = DataSizes::OUTER_RING_RADIUS * cos(angle);
        float z = DataSizes::OUTER_RING_RADIUS * sin(angle);

        Entity* sphere = mSM->createEntity("sphere.mesh");
        SceneNode* node = _outerRingsNode->createChildSceneNode();

        if (i % 2 == 0) sphere->setMaterialName("RustedMetal"); // pares
        else sphere->setMaterialName("RustySteel"); // impares

        node->attachObject(sphere);

        node->setPosition(x, 0, z);
        node->setScale(Vector3(DataSizes::SPHERE_SIZE));
    }
}

void IG2Project::createSkybox() {
    Plane skyPlane(Vector3::UNIT_Z, -5000);

    mSM->_setSkyPlane(
        true,
        skyPlane,
        "Sky",
        1000, // scale: la escala aplicada al plano del cielo.
        5,     // tiling: numero de veces que se coloca la textura en el cielo.
        true,
        0,
        1,
        1,
        ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME
    );
}

void IG2Project::createSinbadAnimation() {
    // lado y altura del triangulo
    float l = DataSizes::SINBAD_WALK_LENGTH;
    float h = sqrt(3.0f) * l / 2.0f; // enunciado

    // vertices del triangulo
    Vector3 p0 = DataSizes::SINBAD_INITIAL_POSITION;
    Vector3 p1 = p0 + Vector3(l, 0, 0);
    Vector3 p2 = p0 + Vector3(l / 2.0f, 0, -h);

    // tiempo total
    float duration = 
        3.0f * DataSizes::SINBAD_TIME_WALKING + // veces que camina
        3.0f * DataSizes::SINBAD_TIME_ROTATING; // veces que rota

    // crea el anim y el track
    Animation* anim = mSM->createAnimation("SinbadAnimation", duration);
    NodeAnimationTrack* track = anim->createNodeTrack(0, mSinbadNode);

    // direcciones de la trayectoria (p0->p1, p1->p2, p2->p0)
    Vector3 p0p1 = (p1 - p0).normalisedCopy();
    Vector3 p1p2 = (p2 - p1).normalisedCopy();
    Vector3 p2p0 = (p0 - p2).normalisedCopy();

    // orientaciones de la trayectoria
    Quaternion r01 = Vector3::UNIT_Z.getRotationTo(p0p1);
    Quaternion r12 = Vector3::UNIT_Z.getRotationTo(p1p2);
    Quaternion r20 = Vector3::UNIT_Z.getRotationTo(p2p0);

    // keyframes
    TransformKeyFrame* kf;

    float t = 0.0f;
    kf = track->createNodeKeyFrame(t);
    kf->setTranslate(p0);
    kf->setRotation(r01);

    t += DataSizes::SINBAD_TIME_WALKING;
    kf = track->createNodeKeyFrame(t);
    kf->setTranslate(p1);
    kf->setRotation(r01);

    t += DataSizes::SINBAD_TIME_ROTATING;
    kf = track->createNodeKeyFrame(t);
    kf->setTranslate(p1);
    kf->setRotation(r12);

    t += DataSizes::SINBAD_TIME_WALKING;
    kf = track->createNodeKeyFrame(t);
    kf->setTranslate(p2);
    kf->setRotation(r12);

    t += DataSizes::SINBAD_TIME_ROTATING;
    kf = track->createNodeKeyFrame(t);
    kf->setTranslate(p2);
    kf->setRotation(r20);

    t += DataSizes::SINBAD_TIME_WALKING;
    kf = track->createNodeKeyFrame(t);
    kf->setTranslate(p0);
    kf->setRotation(r20);

    t += DataSizes::SINBAD_TIME_ROTATING;
    kf = track->createNodeKeyFrame(t);
    kf->setTranslate(p0);
    kf->setRotation(r01);

    _sinbadAnimState = mSM->createAnimationState("SinbadAnimation");
    _sinbadAnimState->setEnabled(true);
    _sinbadAnimState->setLoop(true);
}


