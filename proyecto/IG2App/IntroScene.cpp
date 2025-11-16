#include "IntroScene.h"

IntroScene::IntroScene(SceneManager* sm, OgreBites::TrayManager* tm, Light* l, SceneNode* lp, SceneNode* ln,SceneNode* cn, OgreBites::CameraMan* cm)
	: Scene(sm, tm, l, lp, ln, cn, cm){
	// luces, plano.
	createDirectionalLight();
	Vector3 planePos = Vector3(0, -300, 0);
	createPlane("Intro/Floor", planePos, 1080, 800);

	// Movemos la camara para que mire a la animacion
	_camNode->setPosition(0, -100, -500);
	_camNode->lookAt(Vector3(planePos.x, planePos.y + 50, planePos.z), Ogre::Node::TS_WORLD);

	// Creating Sinbad
	_sinbadEnt = _sceneMgr->createEntity("Sinbad.mesh");
	_sinbadNode = _sceneMgr->getRootSceneNode()->createChildSceneNode();
	_sinbadNode->attachObject(_sinbadEnt);
	_sinbadNode->scale(20, 20, 20);
	_sinbadNode->setPosition(0, -200, 0);
	_sinbadNode->yaw(Ogre::Degree(180));
	_sinbadNode->setInitialState();

	// Creating two swords
	_swordLeftEnt = _sceneMgr->createEntity("Sword.mesh");
	_swordRightEnt = _sceneMgr->createEntity("Sword.mesh");

	_animStateDance = _sinbadEnt->getAnimationState("Dance");
	_animRunLegs = _sinbadEnt->getAnimationState("RunBase");
	_animRunArms = _sinbadEnt->getAnimationState("RunTop");

	Animation* danceAnim = _sceneMgr->createAnimation("sinbadDancing", DURATION);
	danceAnim->setInterpolationMode(Animation::IM_SPLINE);
	NodeAnimationTrack* danceTrack = danceAnim->createNodeTrack(0);
	danceTrack->setAssociatedNode(_sinbadNode);

	TransformKeyFrame* kf;

	// Keyframe 0 (Init state) //Baila
	kf = danceTrack->createNodeKeyFrame(DURATION_STEP * 0);
	kf->setTranslate(KEY_FRAME_POS);

	//// Keyframe 1: Go to the right
	//kf = track->createNodeKeyFrame(durStep * 1);
	//keyframePos += Ogre::Vector3::UNIT_X * movementLength;
	//kf->setTranslate(keyframePos);
	//// Keyframe 3: Go to the origin
	//kf = track->createNodeKeyFrame(durStep * 2);
	//keyframePos += Ogre::Vector3::NEGATIVE_UNIT_X * movementLength;
	//kf->setTranslate(keyframePos);
	//// Keyframe 4: Go to the left
	//kf = track->createNodeKeyFrame(durStep * 3);
	//keyframePos += Ogre::Vector3::NEGATIVE_UNIT_X * movementLength;
	//kf->setTranslate(keyframePos);
	//// Keyframe 5: Go to the origin
	//kf = track->createNodeKeyFrame(durStep * 3);
	//keyframePos += Ogre::Vector3::UNIT_X * movementLength;
	//kf->setTranslate(keyframePos);
	//// Keyframe 6 (Init state) //Baila
	//kf = track->createNodeKeyFrame(durStep * 0);
	//kf->setTranslate(keyframePos);

	// Our defined animation
	_animationState = _sceneMgr->createAnimationState("sinbadDancing");
	_animationState->setLoop(true);
	_animationState->setEnabled(true);

	_animStateDance->setEnabled(true);
	_animRunLegs->setEnabled(false);
	_animRunArms->setEnabled(false);
}

void IntroScene::update(const Ogre::FrameEvent& evt)
{
	_animationState->addTime(evt.timeSinceLastFrame);
	_animStateDance->addTime(evt.timeSinceLastFrame);
	_animRunArms->addTime(evt.timeSinceLastFrame);
	_animRunLegs->addTime(evt.timeSinceLastFrame);
}

