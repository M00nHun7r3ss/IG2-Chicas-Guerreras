#include "Hero.h"

#include "Labyrinth.h"

Hero::Hero(Vector3 initPos, SceneNode* node, SceneManager* sceneMng)
: Character(initPos, node, sceneMng, "Sinbad.mesh"), _lives(3), _points(0), _direction(Vector3::ZERO), _newDirection(Vector3::ZERO), _canGoForward(true) {
}

void Hero::keyPressed(const OgreBites::KeyboardEvent evt){
    if (evt.keysym.sym == SDLK_UP) {
        _newDirection = Vector3(0, 0, 1);
    }
    else if (evt.keysym.sym == SDLK_DOWN) {
        _newDirection = Vector3(0, 0, -1);
    }
    else if (evt.keysym.sym == SDLK_LEFT) {
        _newDirection = Vector3(1, 0, 0);
    }
    else if (evt.keysym.sym == SDLK_RIGHT) {
        _newDirection = Vector3(-1, 0, 0);
    }

    _direction = _newDirection;

    //Rota en la direccion que corresponde
    rotate();
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
		setPosition(getPosition() + HERO_SPEED * _direction * t);
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
    //Cogemos la rotacion que debe hacer entre la rotacion actual (orientation) y la nueva (_newDirection) 
    Quaternion q = getOrientation().getRotationTo(_newDirection);

    //Y rotamos en el eje y, solo la componente y de dicho quaternion
    yaw(q.getYaw());
}
