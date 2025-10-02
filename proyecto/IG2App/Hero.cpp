#include "Hero.h"

Hero::Hero(Vector3 initPos, SceneNode* node, SceneManager* sceneMng)
: Character(initPos, node, sceneMng, "Sinbad.mesh") {
}

void Hero::heroInput(const OgreBites::KeyboardEvent evt)
{
	/*earth->setPosition(EarthDistance*Ogre::Math::Cos(Ogre::Degree(alpha)), 0, EarthDistance*Ogre::Math::Sin(Ogre::Degree(alpha)));
    earth->translate(-EarthDistance, 0, 0, SceneNode::TS_LOCAL);
    earth->yaw(Ogre::Degree(alpha));
    earth->translate(EarthDistance, 0, 0, SceneNode::TS_LOCAL);*/

	if (evt.keysym.sym == SDLK_UP){

    }
    else if (evt.keysym.sym == SDLK_DOWN){
	    
    }
    else if (evt.keysym.sym == SDLK_LEFT){

    }
    else if (evt.keysym.sym == SDLK_RIGHT){

    }
}

void Hero::move()
{
}
