#pragma once
#include "IG2Object.h"
#include "DataSizes.h"
#include "Rocket.h"
#include "OgreParticleSystem.h"
#include <OgreTrays.h>
#include "OgreBillboardSet.h"
#include "OgreParticleSystem.h"
#include <cmath>
#include <numbers>
using namespace std;

class Engine : public IG2Object {
public:
	explicit Engine(Vector3 pos, SceneNode* node, SceneManager* sceneMng);

private:
	SceneNode* _baseNode;
	Entity* _baseEntity;

	std::vector<Rocket*> _rockets;

	//Sistemas de particulas
	SceneNode* _whiteSmokeParticles;
	/*SceneNode* _greySmokeParticles;
	SceneNode* _colorSmokeParticles;*/
};

