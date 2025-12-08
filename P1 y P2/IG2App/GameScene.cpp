#include "GameScene.h"

GameScene::GameScene(SceneManager* sm, OgreBites::TrayManager* tm, Light* l, SceneNode* lp, SceneNode* ln, SceneNode* cn, OgreBites::CameraMan* cm, bool sceneType)
	: Scene(sm, tm, l, lp, ln, cn, cm, sceneType) {

    // Creating the sky
    createSkybox();

    //UI DERECHA
   mLabel = _trayMgr->createLabel(OgreBites::TL_BOTTOMRIGHT, "Titulo", "Stage: 1");
   mTextBox = _trayMgr->createTextBox(OgreBites::TL_BOTTOMRIGHT, "Caja", "Game Info Here!", 250, 100);

    // Hero creation
    _hero = new Hero(Vector3::ZERO, _sceneMgr->getRootSceneNode()->createChildSceneNode("nSinbad"), _sceneMgr);

    // Labyrinth and villains creation
    _lab = new Labyrinth("stage1wv.txt", _sceneMgr, _hero, _villains);

    // Floor creation
    createPlane(_lab->getFloorMaterial(), _lab->getPos(), _lab->getWidth(), _lab->getHeight());

    //------------------------------------------------------------------------
	// Creating the light
    switch (_lab->getLightType()) {
    case 0: createDirectionalLight(); break;
    case 1: createSpotLight(); break;
    case 2: createPointLight(); break;
    default: break;
    }

    
}

bool GameScene::keyPressed(const OgreBites::KeyboardEvent& evt)
{
    //Mira el input del player
    _hero->keyPressed(evt);
    return true;
}

void GameScene::setVisible(bool visible)
{
    _hero->setVisible(visible);
    _lab->setVisible(visible);
    for (Villain* v : _villains) {
        v->setVisible(visible);
	}

    _planeEntity->setVisible(visible);
    _planeNode->setVisible(visible);

    _sceneMgr->setSkyPlaneEnabled(visible);
	_sceneType = visible;

    if (visible)
    {
        //Movemos la camara para que mire al laberinto
        _camNode->setPosition(_lab->getPos().x, 3000, _lab->getPos().z - 1250);
        _camNode->lookAt(_lab->getPos(), Ogre::Node::TS_WORLD);
    }


}

void GameScene::update(const Ogre::FrameEvent& evt)
{
    // updates
    checkCollisions();
    _hero->update(evt);

    ////Mira el bloque de delante, ve si es traspasable, y lo setea en el hero
    //Vector2 nextBlock = _lab->getCharacterForwardBlock(_hero);
    //bool next = _lab->getBlockType(nextBlock);
    //_hero->setCanGoForward(next);

    for (int i = 0; i < _villains.size(); ++i) {
        //_villains[1]->setDirection(_lab->calculateRandomDir(_villains[1]));
        //_villains[1]->rotate();
        _villains[i]->update(evt);
    }

    //Bombas
    for (int i = 0; i < _hero->activeBombs.size(); i++)
    {
        _hero->activeBombs[i]->update(evt);
    }

    //Actualizamos UI de vida y puntos
    mTextBox->setText("Lives: " + std::to_string(_hero->getLives()) + "\nPoints: " + std::to_string(_hero->getPoints()));

    //El spotlight se actualiza con la pos del player
    _lightNode->setPosition(_hero->getPosition().x, 800, _hero->getPosition().z);
}

void GameScene::checkCollisions()
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

    //Si no quedan vidas
    if (_hero->getLives() == 0) {
        _endGame = true;
    }
}

void GameScene::createSkybox()
{
    Plane plane;
    plane.d = 1000;
    plane.normal = Vector3::UNIT_Y;
    _sceneMgr->setSkyPlane(true, plane, "Labyrinth/Skybox", 1500, 25, true, 1.5, 50, 50);
    //TODO SE MUEVE
}

void GameScene::createSpotLight()
{
    //Luz spotlight
    _light = _sceneMgr->createLight("spotLight");
    _light->setType(Light::LT_SPOTLIGHT);
    _light->setSpotlightInnerAngle(Ogre::Degree(5.0f));
    _light->setSpotlightOuterAngle(Ogre::Degree(60.0f));
    _light->setSpotlightFalloff(3.0f);
    _light->setDiffuseColour(1.0f, 1.0f, 1.0f);
    // Node with the light attached
    _lightNode = _sceneMgr->getRootSceneNode()->createChildSceneNode();
    _lightNode->setPosition(_hero->getPosition().x, 800, _hero->getPosition().z);
    _lightNode->setDirection(Ogre::Vector3(0, -1, 0));
    _lightNode->attachObject(_light);
}

void GameScene::createPointLight()
{
    //Luz Point
    _light = _sceneMgr->createLight("pointLight");
    _light->setType(Light::LT_POINT);
    _light->setDiffuseColour(1.0f, 1.0f, 1.0f);
    _light->setAttenuation(3200, 1.0, 0.0014, 0.00000007);
    // Node with the light attached
    _lightNode = _sceneMgr->getRootSceneNode()->createChildSceneNode();
    _lightNode->setPosition(_hero->getPosition());
    _lightNode->attachObject(_light);
}
