#include "Bomb.h"

Bomb::Bomb(Vector3 pos, SceneNode* node, SceneManager* sceneMng) : IG2Object(pos, node, sceneMng) {
	createBombParts();
}

void Bomb::createBombParts()
{
	//Nodo padre (cuerpo)
	SceneNode* ball = mNode->createChildSceneNode();
	//Entidad cuerpo
	Entity* ballEntity = mSM->createEntity("sphere.mesh");
	ball->attachObject(ballEntity);
	ball->setScale(0.3, 0.3, 0.3); // si cambias este lo cambias todo.
	ballEntity->setMaterialName("Villain/Sphere"); // TODO cambiar

	//Nodo cuerda
	SceneNode* rope = ball->createChildSceneNode();  //Vamos a rotar estos dos por lo que a lo mejor

	//Entidad cuerda
	Entity* ropeEntity = mSM->createEntity("cube.mesh");
	rope->attachObject(ropeEntity);
	rope->setScale(Vector3(2, 2, 2));
	rope->setPosition(Vector3(0, 125, 0));
}
