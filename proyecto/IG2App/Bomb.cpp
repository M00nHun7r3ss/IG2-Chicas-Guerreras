#include "Bomb.h"

Bomb::Bomb(Vector3 pos, SceneNode* node, SceneManager* sceneMng) : IG2Object(pos, node, sceneMng) {
	//Timer para cambiar direccion giro partes moviles
	_timer = new Timer();
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
		//_scale = 0; // restea la escala
	}
	scaleBomb();
}

void Bomb::createBombParts()
{
	//Nodo padre (cuerpo)
	ball = mNode->createChildSceneNode();
	//Entidad cuerpo
	ballEntity = mSM->createEntity("sphere.mesh");
	ball->attachObject(ballEntity);
	ball->setScale(0.3, 0.3, 0.3); // si cambias este lo cambias todo.
	ballEntity->setMaterialName("Bomb/Body"); // TODO cambiar

	//Nodo cuerda
	rope = ball->createChildSceneNode();  //Vamos a rotar estos dos por lo que a lo mejor

	//Entidad cuerda
	ropeEntity = mSM->createEntity("column.mesh");
	rope->attachObject(ropeEntity);
	rope->setScale(Vector3(0.5, 0.3, 0.5));
	rope->setPosition(Vector3(0, 125, 0));
	ropeEntity->setMaterialName("Bomb/Rope"); // TODO cambiar
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

	ball->setScale(Vector3(_scale, _scale, _scale));
	rope->setScale(Vector3(_scale, _scale, _scale));
}
