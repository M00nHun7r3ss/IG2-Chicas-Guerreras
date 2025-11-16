#include "IntroScene.h"

IntroScene::IntroScene(SceneManager* sm, OgreBites::TrayManager* tm, Light* l, SceneNode* lp, SceneNode* ln, SceneNode* cn, OgreBites::CameraMan* cm)
	: Scene(sm, tm, l, lp, ln, cn, cm), _keyFramePos(Vector3(0, 0, 0)) {

	_timer = new Timer();

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

	//Creamos la animacion de sinbad
	Animation* sinbadAnim = _sceneMgr->createAnimation("sinbadIntro", DURATION);
	sinbadAnim->setInterpolationMode(Animation::IM_SPLINE);
	NodeAnimationTrack* track = sinbadAnim->createNodeTrack(0);
	track->setAssociatedNode(_sinbadNode);

	TransformKeyFrame* kf;

	// Keyframe 0 (Init state) //Baila
	kf = track->createNodeKeyFrame(DURATION_STEP);
	kf->setTranslate(_keyFramePos);

	// Keyframe 1: Look to the right
	kf = track->createNodeKeyFrame(DURATION_STEP * 2);
	//Mira a derecha
	kf->setRotation(Quaternion(Degree(90), Vector3(0, 1, 0)));

	// Keyframe 2: Go to the right
	kf = track->createNodeKeyFrame(DURATION_STEP * 3);
	_keyFramePos += Ogre::Vector3::NEGATIVE_UNIT_X * MOVEMENT_LENGTH;
	//Se mueve
	kf->setTranslate(_keyFramePos);
	//Sigue mirando a derecha
	kf->setRotation(Quaternion(Degree(90), Vector3(0, 1, 0)));

	// Keyframe 3: Look to the left
	kf = track->createNodeKeyFrame(DURATION_STEP * 4);
	//Mantiene la posicion
	kf->setTranslate(_keyFramePos);
	//Mira a izquierda
	kf->setRotation(Quaternion(Degree(-90), Vector3(0, 1, 0)));

	// Keyframe 4: Go to the origin
	kf = track->createNodeKeyFrame(DURATION_STEP * 5);
	_keyFramePos += Ogre::Vector3::UNIT_X * MOVEMENT_LENGTH;
	//Se mueve
	kf->setTranslate(_keyFramePos);
	//Sigue mirando a izquierda
	kf->setRotation(Quaternion(Degree(-90), Vector3(0, 1, 0)));

	// Keyframe 5: Go to the left
	kf = track->createNodeKeyFrame(DURATION_STEP * 6);
	_keyFramePos += Ogre::Vector3::UNIT_X * MOVEMENT_LENGTH;
	//Se mueve
	kf->setTranslate(_keyFramePos);
	//Sigue mirando a izquierda
	kf->setRotation(Quaternion(Degree(-90), Vector3(0, 1, 0)));

	// Keyframe 6: Look to the right
	kf = track->createNodeKeyFrame(DURATION_STEP * 7);
	//Mantiene la posicion
	kf->setTranslate(_keyFramePos);
	//Mira a derecha
	kf->setRotation(Quaternion(Degree(90), Vector3(0, 1, 0)));

	// Keyframe 7: Go to the origin
	kf = track->createNodeKeyFrame(DURATION_STEP * 8);
	_keyFramePos += Ogre::Vector3::NEGATIVE_UNIT_X * MOVEMENT_LENGTH;
	//Se mueve
	kf->setTranslate(_keyFramePos);
	//Sigue mirando a derecha
	kf->setRotation(Quaternion(Degree(90), Vector3(0, 1, 0)));

	// Keyframe 8: Look to the front
	kf = track->createNodeKeyFrame(DURATION_STEP * 9);
	//Mantiene la posicion
	kf->setTranslate(_keyFramePos);
	//Mira a centro
	kf->setRotation(Quaternion(Degree(0), Vector3(0, 1, 0)));

	// Our defined animation
	_animationState = _sceneMgr->createAnimationState("sinbadIntro");
	_animationState->setLoop(true);
	_animationState->setEnabled(true);

	_animStateDance->setEnabled(true);
	_animRunLegs->setEnabled(false);
	_animRunArms->setEnabled(false);

	//Empieza bailando
	_isDancing = true;
}

void IntroScene::update(const Ogre::FrameEvent& evt)
{
	//Si esta bailando y pasa el tiempo de bailar (Solo el primer frame)
	if (_timer->getMilliseconds() > DURATION_STEP * 1000 && _isDancing)
	{
		//Se pone a andar
		_animStateDance->setEnabled(false);
		_animRunLegs->setEnabled(true);
		_animRunArms->setEnabled(true);

		_isDancing = false;
		_isRunning = true;

	}

	//Si esta corriendo (Frames de 2 a 9)
	if (_timer->getMilliseconds() > 9 * DURATION_STEP * 1000 && _isRunning)
	{
		//Se para
		_animStateDance->setEnabled(true);
		_animRunLegs->setEnabled(false);
		_animRunArms->setEnabled(false);

		_isDancing = true;
		_isRunning = false;

		//Reseteamos el tiempo al acabar
		_timer->reset();
	}




	_animationState->addTime(evt.timeSinceLastFrame);
	_animStateDance->addTime(evt.timeSinceLastFrame);
	_animRunArms->addTime(evt.timeSinceLastFrame);
	_animRunLegs->addTime(evt.timeSinceLastFrame);
}

