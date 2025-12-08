#pragma once

#include "IG2ApplicationContext.h"
//#include "OgreApplicationContext.h"
#include <OgreInput.h>
#include <OgreMeshManager.h>
#include <iostream>
#include "Character.h"
#include "Bomb.h"
#include "OgreAnimation.h"
#include <OgreSkeletonInstance.h>
#include <OgreBone.h>
#include <OgreKeyFrame.h>

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

	void setBomb();

	void createAnimation();

	std::vector<Bomb*> activeBombs;

private:
	int _lives;
	int _points;
	const int MAX_BOMBS = 5;
	int _bombs;

	Vector3 _initialPos;
	Vector3 _newDirection;
	const double HERO_SPEED = 70.0;

	bool _canGoForward;

	void move(double t) override;
	void rotate() override;

	inline void releaseLives() { _lives--; }


	// Animation state
	Ogre::AnimationState* _animationState;

	// Animation states for Sinbad
	Ogre::AnimationState* _animationStateRunBase;
	Ogre::AnimationState* _animationStateRunTop;
};

