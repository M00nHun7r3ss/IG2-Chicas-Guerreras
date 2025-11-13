#pragma once
#include <OgreTrays.h>
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
	SceneNode* ball;
	SceneNode* rope;
	//Entidades
	Entity* ballEntity;
	Entity* ropeEntity;

	Timer* _timer;
	bool _animDir;
	double _scale;
	void scaleBomb();
};