#include "Hero.h"

Hero::Hero(Vector3 initPos, SceneNode* node, SceneManager* sceneMng)
: Character(initPos, node, sceneMng, "Sinbad.mesh"), _lives(3), _points(0), _direction(Vector3::ZERO), _newDirection(Vector3::ZERO) {
}

void Hero::keyPressed(const OgreBites::KeyboardEvent evt)
{
    /*earth->setPosition(EarthDistance*Ogre::Math::Cos(Ogre::Degree(alpha)), 0, EarthDistance*Ogre::Math::Sin(Ogre::Degree(alpha)));
    earth->translate(-EarthDistance, 0, 0, SceneNode::TS_LOCAL);
    earth->yaw(Ogre::Degree(alpha));
    earth->translate(EarthDistance, 0, 0, SceneNode::TS_LOCAL);*/

    if (evt.keysym.sym == SDLK_UP) {
        _newDirection = Vector3(0, 0, 1);
        std::cout << "UP" << std::endl;
    }
    else if (evt.keysym.sym == SDLK_DOWN) {
        _newDirection = Vector3(0, 0, -1);
        std::cout << "DOWN" << std::endl;
    }
    else if (evt.keysym.sym == SDLK_LEFT) {
        _newDirection = Vector3(1, 0, 0);
        std::cout << "LEFT" << std::endl;
    }
    else if (evt.keysym.sym == SDLK_RIGHT) {
        _newDirection = Vector3(-1, 0, 0);
        std::cout << "RIGHT" << std::endl;
    }

    _direction = _newDirection;

    

}

void Hero::frameRendered(const Ogre::FrameEvent& evt){
    //evita que se mueva al arrancar
    if (_newDirection != Vector3::ZERO) {
        move(evt.timeSinceLastFrame);
    }
        std::cout << "Hello im moving" << std::endl;
}


void Hero::move(double t){
    this->setPosition(this->getPosition() + HERO_SPEED * _direction);
}
