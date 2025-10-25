#include "Hero.h"

Hero::Hero(Vector3 initPos, SceneNode* node, SceneManager* sceneMng)
: Character(initPos, node, sceneMng, "Sinbad.mesh"), _lives(3), _points(0), _newDirection(Vector3::ZERO), _canGoForward(true) {
    _direction = Vector3::ZERO;
}

void Hero::keyPressed(const OgreBites::KeyboardEvent evt){
    if (evt.keysym.sym == SDLK_UP || evt.keysym.sym == SDLK_w) {
        _newDirection = Vector3::UNIT_Z;
    }
    else if (evt.keysym.sym == SDLK_DOWN || evt.keysym.sym == SDLK_s) {
        _newDirection = Vector3::NEGATIVE_UNIT_Z;
    }
    else if (evt.keysym.sym == SDLK_LEFT || evt.keysym.sym == SDLK_a) {
        _newDirection = Vector3::UNIT_X;
    }
    else if (evt.keysym.sym == SDLK_RIGHT || evt.keysym.sym == SDLK_d) {
        _newDirection = Vector3::NEGATIVE_UNIT_X;
    }

    _direction = _newDirection;

    //Rota en la direccion que corresponde
    rotate();
}

void Hero::update(const Ogre::FrameEvent& evt)
{
    //evita que se mueva al arrancar
    if (_newDirection != Vector3::ZERO) { move(evt.timeSinceLastFrame); }
}

void Hero::damagePlayer(){
    // ponemos la dir a zero
    _direction = Vector3::ZERO;
    //Lo movemos a la posicion inicial
    setPosition(_initialPos);
    //Quitamos una vida
    releaseLives();
}

void Hero::move(double t)
{
    //Si el siguiente bloque es traspasable, avanza
    if (_canGoForward) { setPosition(getPosition() + HERO_SPEED * _direction * t); }
    //Si no, se para
    else { _direction = Vector3::ZERO; }
}

void Hero::rotate()
{
    //Cogemos la rotacion que debe hacer entre la rotacion actual (orientation) y la nueva (_newDirection) 
    Quaternion q = getOrientation().getRotationTo(_newDirection);

    //Y rotamos en el eje y, solo la componente y de dicho quaternion
    yaw(q.getYaw());
}
