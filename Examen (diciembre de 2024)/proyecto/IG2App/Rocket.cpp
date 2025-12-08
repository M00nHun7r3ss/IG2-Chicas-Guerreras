#include "Rocket.h"

Rocket::Rocket(Vector3 pos, SceneNode* node, SceneManager* sceneMng) : IG2Object(pos, node, sceneMng) {

	//Nodo padre (cuerpo)
	_cubeNode = mNode->createChildSceneNode();
	//Entidad cuerpo
	_cubeEntity = mSM->createEntity("cube.mesh");
	_cubeNode->attachObject(_cubeEntity);
	_cubeNode->setScale(DataSizes::ROCKET_CUBE_SIZE);

	//Nodo bola
	_sphereNode = _cubeNode->createChildSceneNode();  //Vamos a rotar estos dos por lo que a lo mejor
	//Entidad bola
	_sphereEntity = mSM->createEntity("sphere.mesh");
	_sphereNode->attachObject(_sphereEntity);
	_sphereNode->setPosition(Vector3(0, -50, 0));
	_sphereNode->setScale(Vector3(1, 0.25, 1)); //??ALBENUNEEEE

}
