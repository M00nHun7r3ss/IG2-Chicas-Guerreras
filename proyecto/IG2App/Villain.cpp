#include "Villain.h"

Villain::Villain(Vector3 initPos, SceneNode* node, SceneManager* sceneMng) : Character(initPos, node, sceneMng){
	// TODO gestionar como el traspasable afecta al villain ya que en si no tiene malla este objeto, sino que son tres externas.

	//Timer para cambiar direccion giro partes moviles
	_timer = new Timer();
	_animDir = false; // false, por ejemplo
	_angle = 0.0; // inicialmente 0.

	/*
	 Esquema nodos:
	 Padre: Cuerpo [0]
			-> Cabeza [1]
			-> Pies
			-> Brazo 1
				-> Brazo 2
					-> Brazo 3 
	 */

# pragma region Elementos centrales
	//Nodo padre
	_nCuerpo = mNode->createChildSceneNode();
	//Entidad cuerpo
	_vBody = mSM->createEntity("sphere.mesh");
	_nCuerpo->attachObject(_vBody);
	_nCuerpo->setScale(0.3, 0.3, 0.3); // si cambias este lo cambias todo.
	//mNodecuerpo->setPosition(0, 0, -50);
	//mNodecuerpo->yaw(Ogre::Degree(180));

	//Ncuerpo->showBoundingBox(true);

	////Nodo Head
	//SceneNode* mNodeHead = mNodecuerpo->createChildSceneNode();  //Vamos a rotar estos dos por lo que a lo mejor

	////Entidad head
	//Entity* Head = mSM->createEntity("ogrehead.mesh");
	//mNodeHead->attachObject(Head);
	//mNodeHead->setScale(Vector3(1, 1, 1));
	//mNodeHead->setPosition(Vector3(0, 25, 0));

	//Nodo Feet
	_nFeet = _nCuerpo->createChildSceneNode();  //nos interesa guardarlo
	//Entidad Feet
	_vFeet = mSM->createEntity("cube.mesh");
	_nFeet->attachObject(_vFeet);
	_nFeet->setScale(Vector3(1, 1, 1));
	_nFeet->setPosition(Vector3(_nCuerpo->getPosition().x, _nCuerpo->getPosition().y - 150, _nCuerpo->getPosition().z));
#pragma endregion

#pragma region Brazo derecho
	//Nodo Arm 1
	_nArm1R = _nCuerpo->createChildSceneNode();
	//Entidad Arm 1 RIGHT
	_vArm1R = mSM->createEntity("cube.mesh");
	_nArm1R->attachObject(_vArm1R);
	_nArm1R->setScale(Vector3(1, 0.25, 0.25));
	_nArm1R->setPosition(Vector3(_nCuerpo->getPosition().x + 120, _nCuerpo->getPosition().y, _nCuerpo->getPosition().z));

	//Nodo Arm 2
	_nArm2R = _nArm1R->createChildSceneNode();
	//Entidad Arm 2 RIGHT
	_vArm2R = mSM->createEntity("cube.mesh");
	_nArm2R->attachObject(_vArm2R);
	_nArm2R->setScale(Vector3(1, 1, 1));
	_nArm2R->rotate(Quaternion(Radian(Degree(90)), Vector3(0, 0, 1)));
	_nArm2R->setPosition(Vector3(_nArm1R->getPosition().x - 80, _nArm1R->getPosition().y + 150, _nArm1R->getPosition().z));

	//Nodo Arm 3
	_nArm3R = _nArm2R->createChildSceneNode();
	//Entidad Arm 3 RIGHT
	_vArm3R = mSM->createEntity("sphere.mesh");
	_nArm3R->attachObject(_vArm3R);
	_nArm3R->setScale(Vector3(0.25, 1, 1));
	_nArm3R->setPosition(Vector3(_nArm2R->getPosition().x + 20, _nArm2R->getPosition().y - 150, _nArm2R->getPosition().z));
#pragma endregion

#pragma region Brazo Izquierdo
	//Nodo Arm 1.
	_nArm1L = _nCuerpo->createChildSceneNode();
	//Entidad Arm 1 LEFT
	_vArm1L = mSM->createEntity("cube.mesh");
	_nArm1L->attachObject(_vArm1L);
	_nArm1L->setScale(Vector3(1, 0.25, 0.25));
	_nArm1L->setPosition(Vector3(_nCuerpo->getPosition().x - 120, _nCuerpo->getPosition().y, _nCuerpo->getPosition().z));

	//Nodo Arm 2
	_nArm2L = _nArm1L->createChildSceneNode();
	//Entidad Arm 2 LEFT
	_vArm2L = mSM->createEntity("cube.mesh");
	_nArm2L->attachObject(_vArm2L);
	_nArm2L->setScale(Vector3(1, 1, 1));
	_nArm2L->rotate(Quaternion(Radian(Degree(-90)), Vector3(0, 0, 1)));
	_nArm2L->setPosition(Vector3(_nArm1L->getPosition().x + 80, _nArm1L->getPosition().y - 150, _nArm1L->getPosition().z));

	//Nodo Arm 3
	_nArm3L = _nArm2L->createChildSceneNode();
	//Entidad Arm 3 LEFT
	_vArm3L = mSM->createEntity("sphere.mesh");
	_nArm3L->attachObject(_vArm3L);
	_nArm3L->setScale(Vector3(0.25, 1, 1));
	_nArm3L->setPosition(Vector3(_nArm2L->getPosition().x + 80, _nArm2L->getPosition().y + 150, _nArm2L->getPosition().z));
#pragma endregion

}

void Villain::frameRendered(const Ogre::FrameEvent& evt){
	// cuando pasen dos segundos...
	if (_timer->getMilliseconds() > 2000){
		_timer->reset(); // resetea.
		_animDir = !_animDir; // invierte la direccion.
		_angle = 0; // restea el angulo 
	}
	std::cout << _angle << std::endl;
	armsRotation();
}

void Villain::armsRotation(){
	_angle = _angle + 0.05;
	
	if (_animDir) {
		_nArm1R->rotate(Quaternion(Radian(Degree(_angle)), Vector3(1, 0, 0)));
		_nArm1L->rotate(Quaternion(Radian(Degree(-_angle)), Vector3(1, 0, 0)));
	}
	else {
		_nArm1R->rotate(Quaternion(Radian(Degree(-_angle)), Vector3(1, 0, 0)));
		_nArm1L->rotate(Quaternion(Radian(Degree(_angle)), Vector3(1, 0, 0)));
	}
}

SceneNode* Villain::createChildEntity(SceneNode* parentNode, std::string mesh, Vector3 pos, Vector3 scale, Degree angle, Vector3 rotateOn){
	SceneNode* child = parentNode->createChildSceneNode();

	Entity* ent = mSM->createEntity(mesh);
	child->attachObject(ent);
	child->setScale(scale);
	child->rotate(Quaternion(Radian(Degree(angle)), rotateOn));
	child->setPosition(pos);

	return child;
}

void Villain::move(double t)
{
}

void Villain::rotate()
{
}
