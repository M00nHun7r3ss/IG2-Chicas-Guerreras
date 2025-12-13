#include "SpaceShip.h"
SpaceShip::SpaceShip(Vector3 pos, SceneNode* node, SceneManager* sceneMng) : IG2Object(pos, node, sceneMng), _timer(new Timer()){
	_sphereNode = mNode->createChildSceneNode();

	_sphereEntity = mSM->createEntity("sphere.mesh");
	_sphereNode->attachObject(_sphereEntity);
	_sphereNode->setScale(DataSizes::SPACESHIP_BODY_SIZE / DataSizes::ADJUSTMENT);

	_sphereEntity->setMaterialName("Examen/CuerpoNave");

	//Motor
	_engine = new Engine(Vector3(0, -75, 0), _sphereNode->createChildSceneNode(), mSM);
	_engine->setScale(Vector3(2.5, .4, 2.5));
}

void SpaceShip::update()
{
	//Rotacion cohetes y fuego
	_engine->update();

	//Movimiento de cohete
	//Sube pasado un tiempo
	//if (_timer->getMilliseconds() >=  DataSizes::TIME_ENGINE_START * 1000)
	//{
	//	//Sube
	//	_sphereNode->translate(Vector3(0, 2, 0));
	//}

	//Movimiento de avion
}
