#include "Villain.h"

Villain::Villain(Vector3 initPos, SceneNode* node, SceneManager* sceneMng) : Character(initPos, node, sceneMng){
	// TODO gestionar como el traspasable afecta al villain ya que en si no tiene malla este objeto, sino que son tres externas.

	_vBody = new VillainBody(Vector3(0, 0, 0), node, sceneMng);
	_vHead = new VillainHead(Vector3(0, _vBody->calculateBoxSize().y/2, 0), node, sceneMng);
	_vHelix = new VillainHelix(Vector3(0, -_vBody->calculateBoxSize().y / 2, 0), node, sceneMng);
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
