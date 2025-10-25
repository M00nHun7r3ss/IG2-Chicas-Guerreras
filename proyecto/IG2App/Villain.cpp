#include "Villain.h"

Villain::Villain(Vector3 initPos, SceneNode* node, SceneManager* sceneMng) : Character(initPos, node, sceneMng) {
	//Timer para cambiar direccion giro partes moviles
	_timer = new Timer();
	_animDir = false; // false, por ejemplo
	_angle = 0.0; // inicialmente 0.

	createVillainParts();
}

void Villain::update(const Ogre::FrameEvent& evt){
	// cuando pasen dos segundos...
	if (_timer->getMilliseconds() > 2000){
		_timer->reset(); // resetea.
		_animDir = !_animDir; // invierte la direccion.
		_angle = 0; // restea el angulo 
	}
	armsRotation();

	move(evt.timeSinceLastFrame);
}

void Villain::armsRotation(){
	// TODO investigar si se puede reducir.
	_angle = _angle + 0.05;
	
	if (_animDir) {
		_bodyNodes[3]->rotate(Quaternion(Radian(Degree(_angle)), Vector3(1, 0, 0)));
		_bodyNodes[6]->rotate(Quaternion(Radian(Degree(-_angle)), Vector3(1, 0, 0)));
	}
	else {
		_bodyNodes[3]->rotate(Quaternion(Radian(Degree(-_angle)), Vector3(1, 0, 0)));
		_bodyNodes[6]->rotate(Quaternion(Radian(Degree(_angle)), Vector3(1, 0, 0)));
	}
}

void Villain::move(double t){
	setPosition(getPosition() + VILLAIN_SPEED * _direction * t);
}

void Villain::rotate()
{
}

void Villain::createVillainParts()
{
	/*
	 Esquema nodos:
	 Padre: Cuerpo [0]
			-> Cabeza [1]
			-> Pies [2]
			-> Brazo 1 R [3]
				-> Brazo 2 R [4]
					-> Brazo 3 R [5]
			-> Brazo 1 L [6]
				-> Brazo 2 L [7]
					-> Brazo 3 L [8]
	 */

# pragma region Elementos centrales
	

	//Nodo padre (cuerpo)
	_bodyNodes.push_back(mNode->createChildSceneNode());
	//Entidad cuerpo
	_bodyEntities.push_back(mSM->createEntity("sphere.mesh"));
	_bodyNodes[0]->attachObject(_bodyEntities[0]);
	_bodyNodes[0]->setScale(0.3, 0.3, 0.3); // si cambias este lo cambias todo.
	_bodyEntities[0]->setMaterialName("Villain/Sphere");

	//Nodo Head
	_bodyNodes.push_back(_bodyNodes[0]->createChildSceneNode());  //Vamos a rotar estos dos por lo que a lo mejor

	//Entidad head
	_bodyEntities.push_back(mSM->createEntity("ogrehead.mesh"));
	_bodyNodes[1]->attachObject(_bodyEntities[1]);
	_bodyNodes[1]->setScale(Vector3(1, 1, 1));
	_bodyNodes[1]->setPosition(Vector3(0, 25, 0));

	//Nodo Feet
	_bodyNodes.push_back(_bodyNodes[0]->createChildSceneNode());  //nos interesa guardarlo
	//Entidad Feet
	_bodyEntities.push_back(mSM->createEntity("cube.mesh"));
	_bodyNodes[2]->attachObject(_bodyEntities[2]);
	_bodyNodes[2]->setScale(Vector3(1, 1, 1));
	_bodyNodes[2]->setPosition(Vector3(_bodyNodes[0]->getPosition().x, _bodyNodes[0]->getPosition().y - 150, _bodyNodes[0]->getPosition().z));
	_bodyEntities[2]->setMaterialName("Villain/Body");
#pragma endregion

#pragma region Brazo derecho
	//Nodo Arm 1
	_bodyNodes.push_back(_bodyNodes[0]->createChildSceneNode());
	//Entidad Arm 1 RIGHT
	_bodyEntities.push_back(mSM->createEntity("cube.mesh"));
	_bodyNodes[3]->attachObject(_bodyEntities[3]);
	_bodyNodes[3]->setScale(Vector3(1, 0.25, 0.25));
	_bodyNodes[3]->setPosition(Vector3(_bodyNodes[0]->getPosition().x + 120, _bodyNodes[0]->getPosition().y, _bodyNodes[0]->getPosition().z));
	_bodyEntities[3]->setMaterialName("Villain/Body");

	//Nodo Arm 2
	_bodyNodes.push_back(_bodyNodes[3]->createChildSceneNode());
	//Entidad Arm 2 RIGHT
	_bodyEntities.push_back(mSM->createEntity("cube.mesh"));
	_bodyNodes[4]->attachObject(_bodyEntities[4]);
	_bodyNodes[4]->setScale(Vector3(1, 1, 1));
	_bodyNodes[4]->rotate(Quaternion(Radian(Degree(90)), Vector3(0, 0, 1)));
	_bodyNodes[4]->setPosition(Vector3(_bodyNodes[3]->getPosition().x - 80, _bodyNodes[3]->getPosition().y + 150, _bodyNodes[3]->getPosition().z));
	_bodyEntities[4]->setMaterialName("Villain/Body");

	//Nodo Arm 3
	_bodyNodes.push_back(_bodyNodes[4]->createChildSceneNode());
	//Entidad Arm 3 RIGHT
	_bodyEntities.push_back(mSM->createEntity("sphere.mesh"));
	_bodyNodes[5]->attachObject(_bodyEntities[5]);
	_bodyNodes[5]->setScale(Vector3(0.25, 1, 1));
	_bodyNodes[5]->setPosition(Vector3(_bodyNodes[4]->getPosition().x + 20, _bodyNodes[4]->getPosition().y - 150, _bodyNodes[4]->getPosition().z));
	_bodyEntities[5]->setMaterialName("Villain/Sphere");
#pragma endregion

#pragma region Brazo Izquierdo
	//Nodo Arm 1.
	_bodyNodes.push_back(_bodyNodes[0]->createChildSceneNode());
	//Entidad Arm 1 LEFT
	_bodyEntities.push_back(mSM->createEntity("cube.mesh"));
	_bodyNodes[6]->attachObject(_bodyEntities[6]);
	_bodyNodes[6]->setScale(Vector3(1, 0.25, 0.25));
	_bodyNodes[6]->setPosition(Vector3(_bodyNodes[0]->getPosition().x - 120, _bodyNodes[0]->getPosition().y, _bodyNodes[0]->getPosition().z));
	_bodyEntities[6]->setMaterialName("Villain/Body");

	//Nodo Arm 2
	_bodyNodes.push_back(_bodyNodes[6]->createChildSceneNode());
	//Entidad Arm 2 LEFT
	_bodyEntities.push_back(mSM->createEntity("cube.mesh"));
	_bodyNodes[7]->attachObject(_bodyEntities[7]);
	_bodyNodes[7]->setScale(Vector3(1, 1, 1));
	_bodyNodes[7]->rotate(Quaternion(Radian(Degree(-90)), Vector3(0, 0, 1)));
	_bodyNodes[7]->setPosition(Vector3(_bodyNodes[6]->getPosition().x + 80, _bodyNodes[6]->getPosition().y - 150, _bodyNodes[6]->getPosition().z));
	_bodyEntities[7]->setMaterialName("Villain/Body");

	//Nodo Arm 3
	_bodyNodes.push_back(_bodyNodes[7]->createChildSceneNode());
	//Entidad Arm 3 LEFT
	_bodyEntities.push_back(mSM->createEntity("sphere.mesh"));
	_bodyNodes[8]->attachObject(_bodyEntities[8]);
	_bodyNodes[8]->setScale(Vector3(0.25, 1, 1));
	_bodyNodes[8]->setPosition(Vector3(_bodyNodes[7]->getPosition().x + 80, _bodyNodes[7]->getPosition().y + 150, _bodyNodes[7]->getPosition().z));
	_bodyEntities[8]->setMaterialName("Villain/Sphere");
#pragma endregion
}
