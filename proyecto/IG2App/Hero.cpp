#include "Hero.h"

#include "Labyrinth.h"

Hero::Hero(Vector3 initPos, SceneNode* node, SceneManager* sceneMng)
: Character(initPos, node, sceneMng, "Sinbad.mesh"), _lives(3), _points(0), _direction(Vector3::ZERO), _newDirection(Vector3::ZERO), _canGoForward(true) {
}

void Hero::keyPressed(const OgreBites::KeyboardEvent evt){
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

void Hero::move(double t)
{
    //std::cout << _canGoForward << std::endl;
    //Si el siguiente bloque es traspasable, avanza
	if (_canGoForward)
	{
		this->setPosition(this->getPosition() + HERO_SPEED * _direction * t);
	}
    //Si no, se para
    else
    {
        _newDirection = Vector3::ZERO;
    	_direction = _newDirection;
    }
}

void Hero::rotate()
{
    Quaternion q = this->getOrientation().getRotationTo(_newDirection);
}
