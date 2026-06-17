#include "Engine.h"

Engine::Engine(Vector3 pos, SceneNode* node, SceneManager* sm) : IG2Object(pos, node, sm) {
	// --- base
	SceneNode* baseNode = createChildSceneNode();
	Entity* baseEnt = sm->createEntity("Barrel.mesh");
	baseNode->attachObject(baseEnt);
	Vector3 engineScale = datasizesScale(baseEnt, DataSizes::ENGINE_BASE_SIZE);
	baseNode->setScale(engineScale);
	baseNode->pitch(Degree(90));
	baseEnt->setMaterialName("Engine");

	// --- cohetes
	float radius = engineScale.x / 2.0f + 25.0f;

	for (int i = 0; i < DataSizes::AIRPLANE_NUM_ROCKETS; i++) {
		float angle = 2.0f * Ogre::Math::PI * i / DataSizes::AIRPLANE_NUM_ROCKETS;

		float x = radius * cos(angle);
		float y = radius * sin(angle);

		SceneNode* rocketNode = createChildSceneNode();
		Entity* rocketEnt = sm->createEntity("uv_sphere.mesh");
		rocketNode->attachObject(rocketEnt);

		ParticleSystem* smoke = sm->createParticleSystem(to_string(rand()), "example/smokeParticle");
		ParticleEmitter* emitter = smoke->getEmitter(0);
		if (i % 2 == 0) emitter->setColour(ColourValue::White);
		else emitter->setColour(ColourValue(0.2f, 0.2f, 0.2f));
		rocketNode->attachObject(smoke);

		rocketNode->setPosition(x, y, -50);
		Vector3 rocketScale = datasizesScale(rocketEnt, DataSizes::ROCKET_SIZE);
		rocketNode->setScale(rocketScale);
		rocketEnt->setMaterialName("Rocket");
	}
}
