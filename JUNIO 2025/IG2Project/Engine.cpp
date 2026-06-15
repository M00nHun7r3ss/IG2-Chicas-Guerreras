#include "Engine.h"

Engine::Engine(Vector3 pos, SceneNode* node, SceneManager* sm) : IG2Object(pos, node, sm) {
	// --- base
	SceneNode* baseNode = createChildSceneNode();
	Entity* baseEnt = sm->createEntity("Barrel.mesh");
	baseNode->attachObject(baseEnt);
	Vector3 engineScale = datasizesScale(baseEnt, DataSizes::ENGINE_BASE_SIZE);
	baseNode->setScale(engineScale);
	baseNode->pitch(Degree(90));

	// --- cohetes
	float radius = engineScale.x / 2.0f + 25.0f;

	for (int i = 0; i < DataSizes::AIRPLANE_NUM_ROCKETS; i++) {
		float angle = 2.0f * Ogre::Math::PI * i / DataSizes::AIRPLANE_NUM_ROCKETS;

		float x = radius * cos(angle);
		float y = radius * sin(angle);

		SceneNode* rocketNode = createChildSceneNode();
		Entity* rocketEnt = sm->createEntity("uv_sphere.mesh");
		rocketNode->attachObject(rocketEnt);

		rocketNode->setPosition(x, y, -50);
		Vector3 rocketScale = datasizesScale(rocketEnt, DataSizes::ROCKET_SIZE);
		rocketNode->setScale(rocketScale);
	}
}
