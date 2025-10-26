#pragma once
#include <OgreTrays.h>
#include "Character.h"

class Villain : public Character{
public:
	explicit Villain(Vector3 initPos, SceneNode* node, SceneManager* sceneMng);

	void update(const Ogre::FrameEvent& evt); // update
private:
	std::vector<Entity*> _bodyEntities;
	std::vector<SceneNode*> _bodyNodes;

	Timer* _timer;
	bool _animDir;
	double _angle;
	void armsRotation();

	Vector3 _newDirection;
	const double VILLAIN_SPEED = 50.0;

	void move(double t) override;
	void rotate() override;

	void createVillainParts();
};