#include "Airplane.h"

Airplane::Airplane(Vector3 pos, SceneNode* node, SceneManager* sm) : IG2Object(pos, node, sm) {
	// --- cuerpo
	SceneNode* bodyNode = createChildSceneNode();
	Entity* bodyEnt = sm->createEntity("uv_sphere.mesh");
	bodyNode->attachObject(bodyEnt);
	Vector3 bodyScale = datasizesScale(bodyEnt, DataSizes::AIRPLANE_BODY_SIZE);
	bodyNode->setScale(bodyScale);
	bodyNode->pitch(Degree(90.0f));
	bodyEnt->setMaterialName("Body");

	// --- alas
	SceneNode* wingNode = createChildSceneNode();
	Entity* wingEnt = sm->createEntity("cube.mesh");
	wingNode->attachObject(wingEnt);
	Vector3 wingScale = datasizesScale(wingEnt, DataSizes::AIRPLANE_WING_SIZE);
	wingNode->setScale(wingScale);
	wingNode->setPosition(0.0f, 10.0f, 0.0f);
	wingEnt->setMaterialName("Wing");

	// --- timon
	SceneNode* rudderNode = createChildSceneNode();
	Entity* rudderEnt = sm->createEntity("cube.mesh");
	rudderNode->attachObject(rudderEnt);
	Vector3 rudderScale = datasizesScale(rudderEnt, DataSizes::AIRPLANE_RUDDER_SIZE);
	rudderNode->setScale(rudderScale);
	rudderNode->roll(Degree(90));
	rudderNode->yaw(Degree(30));
	rudderNode->setPosition(0.0f, DataSizes::AIRPLANE_BODY_SIZE.x / 2.0f, -DataSizes::AIRPLANE_BODY_SIZE.y / 2.0f);
	rudderEnt->setMaterialName("Wing");

	// --- motor izq
	SceneNode* engineLNode = createChildSceneNode();
	new Engine(Vector3(-150.0f, -20.0f, 0.0f), engineLNode, sm);
	
	// --- motor der
	SceneNode* engineRNode = createChildSceneNode();
	new Engine(Vector3(150.0f, -20.0f, 0.0f), engineRNode, sm);

	ParticleSystem* smoke = sm->createParticleSystem(to_string(rand()), "example/smokeParticle");
	ParticleEmitter* emitter = smoke->getEmitter(0);
	emitter->setColour(ColourValue::Red);
	rudderNode->attachObject(smoke);
}

void Airplane::update(float dt) {
	_angle += DataSizes::AIRPLANE_SPEED * dt;

	float rad = Degree(_angle).valueRadians();

	float x = _radius * sin(rad);
	float z = _radius * cos(rad);

	
	setPosition(Vector3(x, 100.0f, z));

	Ogre::Vector3 dir(
		std::cos(rad),
		0,
		-std::sin(rad)
	);

	mNode->setDirection(-dir);

	if (_rollSpeed != 0.0f) {
		mNode->roll(Ogre::Degree(_rollSpeed * dt));
	}
}

void Airplane::input(const OgreBites::KeyboardEvent& evt) {
	if (evt.keysym.sym == SDLK_a) _rollSpeed = DataSizes::AIRPLANE_ROTATION;
	else if (evt.keysym.sym == SDLK_d) _rollSpeed = -DataSizes::AIRPLANE_ROTATION;
	else if (evt.keysym.sym == SDLK_s) _rollSpeed = 0.0f;
}
