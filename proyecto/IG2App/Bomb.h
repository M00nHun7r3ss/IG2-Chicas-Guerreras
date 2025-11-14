#pragma once
#include <OgreTrays.h>
#include "OgreBillboardSet.h"
#include "OgreParticleSystem.h"
#include "Character.h"

class Bomb : public IG2Object {
public:
	explicit Bomb(Vector3 pos, SceneNode* node, SceneManager* sceneMng);

	void update(const Ogre::FrameEvent& evt); // update
private:
	int const EXPLOSION_RADIUS = 3; // radio de la explosion
	int const EXPLOSION_TIME = 5000; // tiempo que tarda en explotar la bomba

	void createBombParts();
	//Nodos
	SceneNode* _ball;
	SceneNode* _rope;
	SceneNode* _smokeParticles;
	SceneNode* _explosionParticles;

	//Entidades
	Entity* _ballEntity;
	Entity* _ropeEntity;

	Timer* _timer;
	Timer* _explosionTimer;
	bool _animDir;
	double _scale;
	void scaleBomb();
	void createExplosion();
};