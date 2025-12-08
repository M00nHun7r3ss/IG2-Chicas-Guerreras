#include "Engine.h"
#include <cmath>
#include <numbers>

Engine::Engine(Vector3 pos, SceneNode* node, SceneManager* sceneMng) : IG2Object(pos, node, sceneMng) {
	_baseNode = mNode->createChildSceneNode();

	_baseEntity = mSM->createEntity("Barrel.mesh");
	_baseNode->attachObject(_baseEntity);
	_baseNode->setScale(DataSizes::ENGINE_BASE_SIZE / 7.5);

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
		Radian q;
		//Si es par // Rotamos ROCKET_DEGREE
		if (i / 2 != 0)
		{
			q = Quaternion(Degree(-DataSizes::ROCKET_DEGREE), Vector3(0, 1, 0)).getYaw();
		}
		//Si es impar // Rotamos -ROCKET_DEGREE
		else
		{
			q = Quaternion(Degree(DataSizes::ROCKET_DEGREE), Vector3(0, 1, 0)).getYaw();
		}
		rocket->yaw(q);

		//Escalamos
		rocket->setScale(DataSizes::ROCKET_SIZE / 2500);

		//Lo aniadimos al vector general
		_rockets.push_back(rocket);
	}
}

/*
 * GLdouble alpha = 90.0;
    GLdouble incremento = 360.0 / num;
    for (GLuint i = 0; i < num + 2; i++) {
        GLdouble x = r * glm::cos(glm::radians(alpha));
        GLdouble y = r * glm::sin(glm::radians(alpha));
        alpha += incremento;

        // (x, y, z, 1 -> punto 0 -> vector) -> (Cx + R * cos(alpha), Cy + R * sin(alpha), 0, punto).
        mesh->vVertices.emplace_back(x, y, 0.0);
 *
 *
 *
 */