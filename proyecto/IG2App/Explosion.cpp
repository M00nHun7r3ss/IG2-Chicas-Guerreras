#include "Explosion.h"

Explosion::Explosion(Vector3 pos, SceneNode* node, SceneManager* sceneMng)
{
	_explosionParticles = node->createChildSceneNode();
	ParticleSystem* pSys = mSM->createParticleSystem("explosionSmoke", "ParticleSystem/explosionParticle");
	pSys->setEmitting(true);
	_explosionParticles->attachObject(pSys);
}
