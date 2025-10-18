#include "Villain.h"

Villain::Villain(Vector3 initPos, SceneNode* node, SceneManager* sceneMng) : Character(initPos, node, sceneMng){
	// TODO gestionar como el traspasable afecta al villain ya que en si no tiene malla este objeto, sino que son tres externas.

	//Nodo padre
	auto mNodecuerpo = mNode->createChildSceneNode();

	//Entidad cuerpo
	Entity* Cuerpo = mSM->createEntity("sphere.mesh");
	mNodecuerpo->attachObject(Cuerpo);
	//mNodecuerpo->setScale(3, 6, 0.7);
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
	Entity* Feet = mSM->createEntity("cube.mesh");
	mNodeFeet->attachObject(Feet);
	mNodeFeet->setScale(Vector3(1, 1, 1));
	//mNodeFeet->rotate(Quaternion(Radian(15), Vector3(1, 0, 1)));  //Lo giramos para que no esten exactamente iguales
	mNodeFeet->setPosition(Vector3(0, -25, 0));



	//_vBody = new VillainBody(Vector3(0, 0, 0), node, sceneMng);
	//_vHead = new VillainHead(Vector3(0, _vBody->calculateBoxSize().y/2, 0), node, sceneMng);
	//_vHelix = new VillainHelix(Vector3(0, -_vBody->calculateBoxSize().y / 2, 0), node, sceneMng);
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
