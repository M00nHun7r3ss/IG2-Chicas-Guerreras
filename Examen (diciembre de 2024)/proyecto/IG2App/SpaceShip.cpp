#include "SpaceShip.h"

SpaceShip::SpaceShip(Vector3 pos, SceneNode* node, SceneManager* sceneMng) : IG2Object(pos, node, sceneMng) {
	_sphereNode = mNode->createChildSceneNode();

	_sphereEntity = mSM->createEntity("sphere.mesh");
	_sphereNode->attachObject(_sphereEntity);
	_sphereNode->setScale(DataSizes::SPACESHIP_BODY_SIZE / DataSizes::ADJUSTMENT);
}
