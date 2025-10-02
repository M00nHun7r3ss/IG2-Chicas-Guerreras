#include "Hero.h"

Hero::Hero(Vector3 initPos, SceneNode* node, SceneManager* sceneMng)
: Character(initPos, node, sceneMng, "Sinbad.mesh"), _lives(3), _points(0), _direction(Vector3(1.0, 0, 0)), _newDirection(Vector3::ZERO) {
}

void Hero::keyPressed(const OgreBites::KeyboardEvent evt)
{
    /*earth->setPosition(EarthDistance*Ogre::Math::Cos(Ogre::Degree(alpha)), 0, EarthDistance*Ogre::Math::Sin(Ogre::Degree(alpha)));
    earth->translate(-EarthDistance, 0, 0, SceneNode::TS_LOCAL);
    earth->yaw(Ogre::Degree(alpha));
    earth->translate(EarthDistance, 0, 0, SceneNode::TS_LOCAL);*/

    if (evt.keysym.sym == SDLK_UP) {
        _newDirection = Vector3(0, 0, -1);
    }
    else if (evt.keysym.sym == SDLK_DOWN) {
        _newDirection = Vector3(0, 0, 1);
    }
    else if (evt.keysym.sym == SDLK_LEFT) {
        _newDirection = Vector3(-1, 0, 0);
    }
    else if (evt.keysym.sym == SDLK_RIGHT) {
        _newDirection = Vector3(1, 0, 0);
    }

    //evita que se mueva al principio
    if (_newDirection != Vector3::ZERO)
    {
        move();
    }
}

void Hero::move()
{
    this->setPosition(this->getPosition() + HERO_SPEED * _direction * 0.001);
}
