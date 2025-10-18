#include "Villain.h"

Villain::Villain(Vector3 initPos, SceneNode* node, SceneManager* sceneMng) : Character(initPos, node, sceneMng){
	// TODO gestionar como el traspasable afecta al villain ya que en si no tiene malla este objeto, sino que son tres externas.

	//Nodo padre
	SceneNode* mNodecuerpo = mNode->createChildSceneNode();

	//Entidad cuerpo
	_vBody = mSM->createEntity("sphere.mesh");
	mNodecuerpo->attachObject(_vBody);
	mNodecuerpo->setScale(0.25, 0.25, 0.25); // si cambias este lo cambias todo.
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
	mNodeFeet->setScale(Vector3(1.5, 1.5, 1.5));
	//mNodeFeet->rotate(Quaternion(Radian(15), Vector3(1, 0, 1)));  //Lo giramos para que no esten exactamente iguales
	mNodeFeet->setPosition(Vector3(mNodecuerpo->getPosition().x, mNodecuerpo->getPosition().y -  50, mNodecuerpo->getPosition().z));

	// nodo brazo 1.
	SceneNode* mNodeArm1 = mNodecuerpo->createChildSceneNode();

	// entidad brazo 1.
	Entity* b1 = mSM->createEntity("cube.mesh");
	mNodeArm1->attachObject(b1);
	mNodeArm1->setScale(Vector3(1.5, 1.5, 1.5));
	//mNodeFeet->rotate(Quaternion(Radian(15), Vector3(1, 0, 1)));  //Lo giramos para que no esten exactamente iguales
	mNodeArm1->setPosition(Vector3(mNodecuerpo->getPosition().x, mNodecuerpo->getPosition().y - 50, mNodecuerpo->getPosition().z));

	// nodo brazo 2.
	SceneNode* mNodeArm2 = mNodecuerpo->createChildSceneNode();

	//// entidad brazo 2.
	//Entity* b2 = mSM->createEntity("cube.mesh");
	//mNodeArm2->attachObject(b2);
	//mNodeArm2->setScale(Vector3(1.5, 1.5, 1.5));
	////mNodeFeet->rotate(Quaternion(Radian(15), Vector3(1, 0, 1)));  //Lo giramos para que no esten exactamente iguales
	//mNodeArm2->setPosition(Vector3(mNodecuerpo->getPosition().x, mNodecuerpo->getPosition().y - 50, mNodecuerpo->getPosition().z));

	// TODO  a donde se attachan las demas partes, a los arms, al body, etc?? -> mirar folio
}

void Villain::frameRendered(const Ogre::FrameEvent& evt)
{
}

void Villain::move(double t)
{
}

void Villain::rotate()
{
}
