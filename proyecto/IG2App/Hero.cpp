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
        this->mNode->setDirection(_newDirection);
    }
    else if (evt.keysym.sym == SDLK_DOWN) {
        _newDirection = Vector3(0, 0, -1);
        std::cout << "DOWN" << std::endl;
        this->mNode->setDirection(_newDirection);
    }
    else if (evt.keysym.sym == SDLK_LEFT) {
        _newDirection = Vector3(1, 0, 0);
        std::cout << "LEFT" << std::endl;
        this->mNode->setDirection(_newDirection);
    }
    else if (evt.keysym.sym == SDLK_RIGHT) {
        _newDirection = Vector3(-1, 0, 0);
        std::cout << "RIGHT" << std::endl;
        this->mNode->setDirection(_newDirection);
    }

    _direction = _newDirection;

    //this->yaw(Degree(90.0f));
    //std::cout << this->getOrientation() << std::endl;


}

void Hero::frameRendered(const Ogre::FrameEvent& evt){
    //evt.timeSinceLastFrame //TODO: PA K CONIO ES ESTO?
    //evita que se mueva al arrancar
    if (_newDirection != Vector3::ZERO) {
        move(evt.timeSinceLastFrame);
    }

}

void Hero::move(double t){
    this->setPosition(this->getPosition() + HERO_SPEED * _direction * t);
}

void Hero::rotate()
{
    Quaternion q = this->getOrientation().getRotationTo(_newDirection);
}
