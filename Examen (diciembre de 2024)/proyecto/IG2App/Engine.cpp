#include "Engine.h"
#include <cmath>
#include <numbers>

Engine::Engine(Vector3 pos, SceneNode* node, SceneManager* sceneMng) : IG2Object(pos, node, sceneMng) {
	_baseNode = mNode->createChildSceneNode();

	_baseEntity = mSM->createEntity("Barrel.mesh");
	_baseNode->attachObject(_baseEntity);
	_baseNode->setScale(DataSizes::ENGINE_BASE_SIZE / 7.5);

	_baseEntity->setMaterialName("Examen/BaseMotor");

	int incremento = 360 / DataSizes::NUM_ROCKETS;
	int angulo = 0;
	int radius = 35;
	double x, z;
	for (int i = 0; i < DataSizes::NUM_ROCKETS; i++)
	{
		//Posicion
		x = radius * cos(angulo * M_PI / 180);
		z = radius * sin(angulo * M_PI / 180);
		angulo += incremento;
		//Creamos el cohete en esa direccion
		Rocket* rocket = new Rocket(Vector3(x, -75, z), mNode->createChildSceneNode(), mSM);

		//Rotamos los cohetes segun si son pares o no

		int rot = DataSizes::ROCKET_DEGREE; // par

		//Si es impar // Rotamos -ROCKET_DEGREE
		if ((i % 2) != 0) {
			rot = - DataSizes::ROCKET_DEGREE;
		}

		rocket->yaw(Quaternion(Degree(rot), Vector3(0, 1, 0)).getYaw());

		//Escalamos
		rocket->setScale(DataSizes::ROCKET_SIZE / 3000);

		//Sistema de particulas
		_whiteSmokeParticles = rocket->createChildSceneNode();

		ParticleSystem* pSys = mSM->createParticleSystem(i, "ParticleSystem/WhiteSmoke");
		pSys->setEmitting(true);
		_whiteSmokeParticles->attachObject(pSys);

		//Lo aniadimos al vector general
		_rockets.push_back(rocket);
	}
}