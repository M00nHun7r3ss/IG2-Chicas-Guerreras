#pragma once

#include "IG2ApplicationContext.h"
#include <OgreInput.h>
#include <OgreMeshManager.h>
#include <iostream>
#include "Character.h"

class Hero : public Character
{
public: 
	explicit Hero(Vector3 initPos, SceneNode* node, SceneManager* sceneMng);

	void keyPressed(const OgreBites::KeyboardEvent evt); // input
	void update(const Ogre::FrameEvent& evt); // update

	inline int getLives() { return _lives; }
	inline int getPoints() { return _points; }
	inline bool getCanGoForward() { return _canGoForward; }

	inline void increasePoints(int newPoints) { _points += newPoints; }

	void setCanGoForward(bool _canGo) { _canGoForward = _canGo; }
	void setFirstPos(Vector3 initPos) { _initialPos = initPos; }

	void damagePlayer();


private:
	int _lives;
	int _points;

	Vector3 _initialPos;
	Vector3 _newDirection;
	const double HERO_SPEED = 70.0;

	bool _canGoForward;

	void move(double t) override;
	void rotate() override;

	inline void releaseLives() { _lives--; }
};

