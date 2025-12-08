#include "Engine.h"

Engine::Engine(Vector3 pos, SceneNode* node, SceneManager* sceneMng) : IG2Object(pos, node, sceneMng) {
	_baseNode = mNode->createChildSceneNode();

	_baseEntity = mSM->createEntity("Barrel.mesh");
	_baseNode->attachObject(_baseEntity);
	_baseNode->setScale(DataSizes::ENGINE_BASE_SIZE);
}
