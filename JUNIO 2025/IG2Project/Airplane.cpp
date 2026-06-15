#include "Airplane.h"

Airplane::Airplane(Vector3 pos, SceneNode* node, SceneManager* sm) : IG2Object(pos, node, sm) {
	// --- cuerpo
	SceneNode* bodyNode = createChildSceneNode();
	Entity* bodyEnt = sm->createEntity("uv_sphere.mesh");
	bodyNode->attachObject(bodyEnt);
	Vector3 bodyScale = datasizesScale(bodyEnt, DataSizes::AIRPLANE_BODY_SIZE);
	bodyNode->setScale(bodyScale);
	bodyNode->pitch(Degree(90.0f));

	// --- alas
	SceneNode* wingNode = createChildSceneNode();
	Entity* wingEnt = sm->createEntity("cube.mesh");
	wingNode->attachObject(wingEnt);
	Vector3 wingScale = datasizesScale(wingEnt, DataSizes::AIRPLANE_WING_SIZE);
	wingNode->setScale(wingScale);
	wingNode->setPosition(0.0f, 10.0f, 0.0f);

	// --- timon
	SceneNode* rudderNode = createChildSceneNode();
	Entity* rudderEnt = sm->createEntity("cube.mesh");
	rudderNode->attachObject(rudderEnt);
	Vector3 rudderScale = datasizesScale(rudderEnt, DataSizes::AIRPLANE_RUDDER_SIZE);
	rudderNode->setScale(rudderScale);
	rudderNode->roll(Degree(90));
	rudderNode->yaw(Degree(30));
	rudderNode->setPosition(0.0f, DataSizes::AIRPLANE_BODY_SIZE.x / 2.0f, -DataSizes::AIRPLANE_BODY_SIZE.y / 2.0f);

	// --- motor izq
	SceneNode* engineLNode = createChildSceneNode();
	new Engine(Vector3(-150.0f, -20.0f, 0.0f), engineLNode, sm);
	
	// --- motor der
	SceneNode* engineRNode = createChildSceneNode();
	new Engine(Vector3(150.0f, -20.0f, 0.0f), engineRNode, sm);

}
