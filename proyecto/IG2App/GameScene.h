#pragma once
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

#include "OgreAnimation.h"
#include <OgreSkeletonInstance.h>
#include <OgreBone.h>
#include <OgreKeyFrame.h>

#include "Bomb.h"

#include "Scene.h"

class GameScene : public Scene {

public:
    explicit GameScene(SceneManager* sm, OgreBites::TrayManager* tm,
        Light* l, SceneNode* lp, SceneNode* ln,
        SceneNode* cn, OgreBites::CameraMan* cm, bool sceneType = true);

    //virtual ~GameScene(); // TODO hacer desconstructora bien.

    virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);  // InputListener

    void setVisible(bool visible) override;

    void update(const Ogre::FrameEvent& evt);

    bool getEndGame() { return _endGame; };
    void setEndGame(bool endGame) { _endGame = endGame; }

private:

    //Define si se acaba el juego o no;
    bool _endGame = false;

    // Objects
    Hero* _hero = nullptr;
    Labyrinth* _lab = nullptr;
    std::vector<Villain*> _villains;

    //Para la ui de la vida y los puntos
    OgreBites::TextBox* mTextBox = nullptr;
    OgreBites::Label* mLabel = nullptr;

    void checkCollisions(); // TODO arreglar
    void createSkybox();

    //Estas luces solo pueden estar aqui
    void createSpotLight();
    void createPointLight();
};
