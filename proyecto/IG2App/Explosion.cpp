#include "Explosion.h"

Explosion::Explosion(Vector3 pos, SceneNode* node, SceneManager* sceneMng, int index)
{
	_explosionParticles = node->createChildSceneNode();
	ParticleSystem* pSys = mSM->createParticleSystem("explosionSmoke" + index, "ParticleSystem/explosionParticle");
	pSys->setEmitting(true);
	_explosionParticles->attachObject(pSys);
}
