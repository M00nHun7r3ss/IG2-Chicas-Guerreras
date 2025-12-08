#include "Bomb.h"

Bomb::Bomb(Vector3 pos, SceneNode* node, SceneManager* sceneMng, int index) : IG2Object(pos, node, sceneMng), _index(index) {
	//Timer para cambiar direccion giro partes moviles
	_timer = new Timer();
	//Timer para iniciar explosion
	_untilExplosionTimer = new Timer();
	//Timer para quitar explosion
	_explosionDurationTimer = new Timer();

	_animDir = false; // false, por ejemplo
	_scale = 0.0; // inicialmente 0.

	createBombParts();

}

void Bomb::update(const Ogre::FrameEvent& evt)
{
	// cuando pasen dos segundos...
	if (_timer->getMilliseconds() > 1000) {
		_timer->reset(); // resetea.
		_animDir = !_animDir; // invierte la direccion.
	}

	// explota.
	if (_untilExplosionTimer->getMilliseconds() >= EXPLOSION_TIME){
		_untilExplosionTimer->reset();
		createExplosion();
	}
	else{
		_smokeParticles->translate(Vector3(0, -1, 0));
		scaleBomb();
	}
}

void Bomb::createBombParts()
{
	//Nodo padre (cuerpo)
	_ball = mNode->createChildSceneNode();
	//Entidad cuerpo
	_ballEntity = mSM->createEntity("sphere.mesh");
	_ball->attachObject(_ballEntity);
	_ball->setScale(0.3, 0.3, 0.3); // si cambias este lo cambias todo.
	_ballEntity->setMaterialName("Bomb/Body"); // TODO cambiar

	//Nodo cuerda
	_rope = _ball->createChildSceneNode();  //Vamos a rotar estos dos por lo que a lo mejor
	//Entidad cuerda
	_ropeEntity = mSM->createEntity("column.mesh");
	_rope->attachObject(_ropeEntity);
	_rope->setScale(Vector3(0.5, 0.3, 0.5));
	_rope->setPosition(Vector3(0, 125, 0));
	_ropeEntity->setMaterialName("Bomb/Rope"); // TODO cambiar

	// Nodo mecha.
	_smokeParticles = _rope->createChildSceneNode();
	_rope->setScale(Vector3(0.5, 0.3, 0.5));
	_rope->setPosition(Vector3(0, 125, 0));

	ParticleSystem* pSys = mSM->createParticleSystem("mechaSmoke" + _index, "ParticleSystem/smokeParticle");
	pSys->setEmitting(true);
	_smokeParticles->attachObject(pSys);
}

void Bomb::scaleBomb()
{

	if (_animDir) {
		_scale = _scale + 0.005;
	}
	else {
		_scale = _scale - 0.005;
	}

	if (_scale <= 0.2) _scale = 0.2;

	_ball->setScale(Vector3(_scale, _scale, _scale));
	_rope->setScale(Vector3(_scale, _scale, _scale));
}

void Bomb::createExplosion() {
	// va escondiendo.
	_smokeParticles->setVisible(false);
	_ropeEntity->setVisible(false);
	_rope->setVisible(false);
	_ballEntity->setVisible(false);
	_ball->setVisible(false);

	//Centro
	_explosionParticles = _ball->createChildSceneNode();
	ParticleSystem* pSys = mSM->createParticleSystem("explosionSmoke" + _index, "ParticleSystem/explosionParticle");
	pSys->setEmitting(false);
	_explosionParticles->attachObject(pSys);



}
