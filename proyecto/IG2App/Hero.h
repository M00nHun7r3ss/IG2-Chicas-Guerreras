#pragma once

#include "IG2ApplicationContext.h"
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreTrays.h>
#include <OgreCameraMan.h>
#include <OgreEntity.h>
#include <OgreInput.h>
#include <SDL_keycode.h>
#include <OgreMeshManager.h>
#include <sstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <vector>
#include "Character.h"

class Hero : public Character
{
public: 
	explicit Hero(Vector3 initPos, SceneNode* node, SceneManager* sceneMng);

	void keyPressed(const OgreBites::KeyboardEvent evt); // input
	void update(const Ogre::FrameEvent& evt); // update

	inline Vector3 getDirection() { return _direction; }
	inline int getLives() { return _lives; }
	inline int getPoints() { return _points; }
	inline bool getCanGoForward() { return _canGoForward; }

	inline void releaseLives() { if (_lives > 0) _lives--; else _lives = 0; }
	inline void increasePoints(int newPoints) { _points += newPoints; }

	void setCanGoForward(bool _canGo) { _canGoForward = _canGo; }


private:
	int _lives;
	int _points;
	Vector3 _direction;
	Vector3 _newDirection;
	const double HERO_SPEED = 70.0;

	bool _canGoForward;

	void move(double t) override;
	void rotate() override;
};

