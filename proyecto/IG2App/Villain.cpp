#include "Villain.h"

Villain::Villain(Vector3 initPos, SceneNode* node, SceneManager* sceneMng) : Character(initPos, node, sceneMng){
	// TODO gestionar como el traspasable afecta al villain ya que en si no tiene malla este objeto, sino que son tres externas.

	//Timer para cambiar direccion giro partes moviles
	_timer = new Timer();

	/*
	 Esquema nodos:
	 Padre: Cuerpo
			-> Cabeza
			-> Pies
			-> Brazo 1
				-> Brazo 2
					-> Brazo 3 
	 */

	//Nodo padre
	SceneNode* mNodecuerpo = mNode->createChildSceneNode();

	//Entidad cuerpo
	_vBody = mSM->createEntity("sphere.mesh");
	mNodecuerpo->attachObject(_vBody);
	mNodecuerpo->setScale(0.3, 0.3, 0.3); // si cambias este lo cambias todo.
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
	SceneNode* mNodeFeet = mNodecuerpo->createChildSceneNode();  //nos interesa guardarlo

	//Entidad Feet
	_vFeet = mSM->createEntity("cube.mesh");
	mNodeFeet->attachObject(_vFeet);
	mNodeFeet->setScale(Vector3(1, 1, 1));
	mNodeFeet->setPosition(Vector3(mNodecuerpo->getPosition().x, mNodecuerpo->getPosition().y - 150, mNodecuerpo->getPosition().z));

	//Brazo derecho

	//Nodo Arm 1
	SceneNode* mNodeArm1R = mNodecuerpo->createChildSceneNode();

	//Entidad Arm 1 RIGHT
	_vArm1R = mSM->createEntity("cube.mesh");
	mNodeArm1R->attachObject(_vArm1R);
	mNodeArm1R->setScale(Vector3(1, 0.25, 0.25));
	mNodeArm1R->setPosition(Vector3(mNodecuerpo->getPosition().x + 120, mNodecuerpo->getPosition().y, mNodecuerpo->getPosition().z));

	//Nodo Arm 2
	SceneNode* mNodeArm2R = mNodeArm1R->createChildSceneNode();

	//Entidad Arm 2 RIGHT
	_vArm2R = mSM->createEntity("cube.mesh");
	mNodeArm2R->attachObject(_vArm2R);
	mNodeArm2R->setScale(Vector3(1, 1, 1));
	mNodeArm2R->rotate(Quaternion(Radian(Degree(90)), Vector3(0, 0, 1)));
	mNodeArm2R->setPosition(Vector3(mNodeArm1R->getPosition().x - 80, mNodeArm1R->getPosition().y + 150, mNodeArm1R->getPosition().z));

	//Nodo Arm 3
	SceneNode* mNodeArm3R = mNodeArm2R->createChildSceneNode();

	//Entidad Arm 3 RIGHT
	_vArm3R = mSM->createEntity("sphere.mesh");
	mNodeArm3R->attachObject(_vArm3R);
	mNodeArm3R->setScale(Vector3(0.25, 1, 1));
	mNodeArm3R->setPosition(Vector3(mNodeArm2R->getPosition().x + 20, mNodeArm2R->getPosition().y - 150, mNodeArm2R->getPosition().z));

	//Brazo izquierdo

	//Nodo Arm 1.
	SceneNode* mNodeArm1L = mNodecuerpo->createChildSceneNode();

	//Entidad Arm 1 LEFT
	_vArm1L = mSM->createEntity("cube.mesh");
	mNodeArm1L->attachObject(_vArm1L);
	mNodeArm1L->setScale(Vector3(1, 0.25, 0.25));
	mNodeArm1L->setPosition(Vector3(mNodecuerpo->getPosition().x - 120, mNodecuerpo->getPosition().y, mNodecuerpo->getPosition().z));

	//Nodo Arm 2
	SceneNode* mNodeArm2L = mNodeArm1L->createChildSceneNode();

	//Entidad Arm 2 RIGHT
	_vArm2L = mSM->createEntity("cube.mesh");
	mNodeArm2L->attachObject(_vArm2L);
	mNodeArm2L->setScale(Vector3(1, 1, 1));
	mNodeArm2L->rotate(Quaternion(Radian(Degree(-90)), Vector3(0, 0, 1)));
	mNodeArm2L->setPosition(Vector3(mNodeArm1L->getPosition().x + 80, mNodeArm1L->getPosition().y - 150, mNodeArm1L->getPosition().z));

	//Nodo Arm 3
	SceneNode* mNodeArm3L = mNodeArm2L->createChildSceneNode();

	//Entidad Arm 3 RIGHT
	_vArm3L = mSM->createEntity("sphere.mesh");
	mNodeArm3L->attachObject(_vArm3L);
	mNodeArm3L->setScale(Vector3(0.25, 1, 1));
	mNodeArm3L->setPosition(Vector3(mNodeArm2L->getPosition().x + 80, mNodeArm2L->getPosition().y + 150, mNodeArm2L->getPosition().z));

}

void Villain::frameRendered(const Ogre::FrameEvent& evt)
{
	//if (_timer->getMilliseconds() > evt.timeSinceLastFrame);

}

void Villain::move(double t)
{
}

void Villain::rotate()
{
}
