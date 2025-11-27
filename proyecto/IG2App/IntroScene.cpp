#include "IntroScene.h"

IntroScene::IntroScene(SceneManager* sm, OgreBites::TrayManager* tm, Light* l, SceneNode* lp, SceneNode* ln, SceneNode* cn, OgreBites::CameraMan* cm, bool sceneType)
	: Scene(sm, tm, l, lp, ln, cn, cm, sceneType), _sinbadKeyFramePos(Vector3(0, 0, 0)), _ogreheadKeyFramePos(Vector3(0, 0, 0)), _isRunning(false), _isDancing(false), _areSwordsAttached(false) {
	_timer = new Timer();

	// luces, plano.
	createDirectionalLight();
	Vector3 planePos = Vector3(0, -300, 0);
	createPlane("Intro/Water", planePos, 1080, 800);

	createSinbadAnim();
	createOgreheadAnim();
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

	// Saca espadas.
	if (_timer->getMilliseconds() > 4 * DURATION_STEP * 1000 && !_areSwordsAttached){
		_sinbadEnt->attachObjectToBone("Handle.L", _swordLeftEnt);
		_sinbadEnt->attachObjectToBone("Handle.R", _swordRightEnt);
		_areSwordsAttached = true;
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

		// Quita espadas.
		if (_areSwordsAttached) {
			_sinbadEnt->detachObjectFromBone(_swordLeftEnt);
			_sinbadEnt->detachObjectFromBone(_swordRightEnt);
			_areSwordsAttached = false;
		}
		

		//Reseteamos el tiempo al acabar
		_timer->reset();
	}

	_sinbadAnimationState->addTime(evt.timeSinceLastFrame);
	_animStateDance->addTime(evt.timeSinceLastFrame);
	_animRunArms->addTime(evt.timeSinceLastFrame);
	_animRunLegs->addTime(evt.timeSinceLastFrame);

	_ogreheadAnimationState->addTime(evt.timeSinceLastFrame);
}

void IntroScene::setVisible(bool visible)
{
	_sinbadEnt->setVisible(visible);
	_sinbadNode->setVisible(visible);
	_sinbadNode->setVisible(visible);
	_swordLeftEnt->setVisible(visible);
	_swordRightEnt->setVisible(visible);

	_ogreHeadEnt->setVisible(visible);
	_ogreHeadNode->setVisible(visible);

	_planeEntity->setVisible(visible);
	_planeNode->setVisible(visible);

	_sceneType = visible;

	Vector3 planePos = Vector3(0, -300, 0);
	if (visible)
	{
		// Movemos la camara para que mire a la animacion
		_camNode->setPosition(0, -100, -500);
		_camNode->lookAt(Vector3(planePos.x, planePos.y + 50, planePos.z), Ogre::Node::TS_WORLD);
	}

}

void IntroScene::createSinbadAnim() {
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

	// Crea animationstates
	_animStateDance = _sinbadEnt->getAnimationState("Dance");
	_animRunLegs = _sinbadEnt->getAnimationState("RunBase");
	_animRunArms = _sinbadEnt->getAnimationState("RunTop");

	//Creamos la animacion de sinbad
	Animation* sinbadAnim = _sceneMgr->createAnimation("sinbadIntro", DURATION);
	sinbadAnim->setInterpolationMode(Animation::IM_SPLINE);
	NodeAnimationTrack* track = sinbadAnim->createNodeTrack(0);
	track->setAssociatedNode(_sinbadNode);

	TransformKeyFrame* kf;

	// Keyframe 0 (Init state) //Baile
	//addKeyFrame(DURATION_STEP, setrotation, settranslate)
	kf = track->createNodeKeyFrame(DURATION_STEP);
	kf->setTranslate(_sinbadKeyFramePos);

	// Keyframe 1: Look to the right
	kf = track->createNodeKeyFrame(DURATION_STEP * 2);
	//Mira a derecha
	kf->setRotation(Quaternion(Degree(90), Vector3(0, 1, 0)));

	// Keyframe 2: Go to the right
	kf = track->createNodeKeyFrame(DURATION_STEP * 3);
	_sinbadKeyFramePos += Ogre::Vector3::NEGATIVE_UNIT_X * MOVEMENT_LENGTH;
	//Se mueve
	kf->setTranslate(_sinbadKeyFramePos);
	//Sigue mirando a derecha
	kf->setRotation(Quaternion(Degree(90), Vector3(0, 1, 0)));

	// Keyframe 3: Look to the left
	kf = track->createNodeKeyFrame(DURATION_STEP * 4);
	//Mantiene la posicion
	kf->setTranslate(_sinbadKeyFramePos);
	//Mira a izquierda
	kf->setRotation(Quaternion(Degree(-90), Vector3(0, 1, 0)));

	// Keyframe 4: Go to the origin
	kf = track->createNodeKeyFrame(DURATION_STEP * 5);
	_sinbadKeyFramePos += Ogre::Vector3::UNIT_X * MOVEMENT_LENGTH;
	//Se mueve
	kf->setTranslate(_sinbadKeyFramePos);
	//Sigue mirando a izquierda
	kf->setRotation(Quaternion(Degree(-90), Vector3(0, 1, 0)));

	// Keyframe 5: Go to the left
	kf = track->createNodeKeyFrame(DURATION_STEP * 6);
	_sinbadKeyFramePos += Ogre::Vector3::UNIT_X * MOVEMENT_LENGTH;
	//Se mueve
	kf->setTranslate(_sinbadKeyFramePos);
	//Sigue mirando a izquierda
	kf->setRotation(Quaternion(Degree(-90), Vector3(0, 1, 0)));

	// Keyframe 6: Look to the right
	kf = track->createNodeKeyFrame(DURATION_STEP * 7);
	//Mantiene la posicion
	kf->setTranslate(_sinbadKeyFramePos);
	//Mira a derecha
	kf->setRotation(Quaternion(Degree(90), Vector3(0, 1, 0)));

	// Keyframe 7: Go to the origin
	kf = track->createNodeKeyFrame(DURATION_STEP * 8);
	_sinbadKeyFramePos += Ogre::Vector3::NEGATIVE_UNIT_X * MOVEMENT_LENGTH;
	//Se mueve
	kf->setTranslate(_sinbadKeyFramePos);
	//Sigue mirando a derecha
	kf->setRotation(Quaternion(Degree(90), Vector3(0, 1, 0)));

	// Keyframe 8: Look to the front
	kf = track->createNodeKeyFrame(DURATION_STEP * 9);
	//Mantiene la posicion
	kf->setTranslate(_sinbadKeyFramePos);
	//Mira a centro
	kf->setRotation(Quaternion(Degree(0), Vector3(0, 1, 0)));

	// Our defined animation
	_sinbadAnimationState = _sceneMgr->createAnimationState("sinbadIntro");
	_sinbadAnimationState->setLoop(true);
	_sinbadAnimationState->setEnabled(true);

	// inicialmente baila pero no corre.
	_animStateDance->setEnabled(true);
	_animRunLegs->setEnabled(false);
	_animRunArms->setEnabled(false);
	_isDancing = true;
}

void IntroScene::createOgreheadAnim()
{
	// Creating Head
	_ogreHeadEnt = _sceneMgr->createEntity("ogrehead.mesh");
	_ogreHeadNode = _sceneMgr->getRootSceneNode()->createChildSceneNode();
	_ogreHeadNode->scale(3, 3, 3);
	_ogreHeadNode->setPosition(200, -220, 0);
	_ogreHeadNode->yaw(Ogre::Degree(-90));
	_ogreHeadNode->attachObject(_ogreHeadEnt);
	_ogreHeadNode->setInitialState();

	//Creamos la animacion de ogrehead
	Animation* ogreHeadAnim = _sceneMgr->createAnimation("ogreIntro", DURATION);
	ogreHeadAnim->setInterpolationMode(Animation::IM_SPLINE);
	NodeAnimationTrack* track = ogreHeadAnim->createNodeTrack(0);
	track->setAssociatedNode(_ogreHeadNode);

	// -----------------------------------------

	TransformKeyFrame* kf;

	// Keyframe 0: static
	kf = track->createNodeKeyFrame(DURATION_STEP);
	//Se mueve
	kf->setTranslate(_ogreheadKeyFramePos);
	//Sigue mirando a derecha
	kf->setRotation(Quaternion(Degree(0), Vector3(0, 1, 0)));

	// Keyframe 1: Go to the right
	kf = track->createNodeKeyFrame(DURATION_STEP * 2);
	_ogreheadKeyFramePos += Ogre::Vector3::NEGATIVE_UNIT_X * MOVEMENT_LENGTH * 2;
	//Se mueve
	kf->setTranslate(_ogreheadKeyFramePos);
	//Sigue mirando a derecha
	kf->setRotation(Quaternion(Degree(0), Vector3(0, 1, 0)));

	// Keyframe 2: Look to the left
	kf = track->createNodeKeyFrame(DURATION_STEP * 3);
	//Mantiene la posicion
	kf->setTranslate(_ogreheadKeyFramePos);
	//Mira a izquierda
	kf->setRotation(Quaternion(Degree(180), Vector3(0, 1, 0)));

	// Keyframe 3: Go to the left
	kf = track->createNodeKeyFrame(DURATION_STEP * 4);
	_ogreheadKeyFramePos += Ogre::Vector3::UNIT_X * MOVEMENT_LENGTH * 2;
	//Se mueve
	kf->setTranslate(_ogreheadKeyFramePos);
	//Sigue mirando a izquierda
	kf->setRotation(Quaternion(Degree(180), Vector3(0, 1, 0)));

	// Keyframe 4: Look to the right
	kf = track->createNodeKeyFrame(DURATION_STEP * 5);
	//Mantiene la posicion
	kf->setTranslate(_ogreheadKeyFramePos);
	//Mira a derecha
	kf->setRotation(Quaternion(Degree(0), Vector3(0, 1, 0)));

	// Keyframe 5: Go to the right
	kf = track->createNodeKeyFrame(DURATION_STEP * 6);
	_ogreheadKeyFramePos += Ogre::Vector3::NEGATIVE_UNIT_X * MOVEMENT_LENGTH * 2;
	//Se mueve
	kf->setTranslate(_ogreheadKeyFramePos);
	//Sigue mirando a derecha
	kf->setRotation(Quaternion(Degree(0), Vector3(0, 1, 0)));
	//Se va haciendo pequenio
	kf->setScale(kf->getScale() * 0.01);

	// Keyframe 6: Go to the left
	kf = track->createNodeKeyFrame(DURATION_STEP * 7);
	_ogreheadKeyFramePos = Ogre::Vector3::UNIT_X * MOVEMENT_LENGTH * 2;
	//Se mueve
	kf->setTranslate(_ogreheadKeyFramePos);
	//Sigue mirando a derecha
	kf->setRotation(Quaternion(Degree(0), Vector3(0, 1, 0)));

	// Keyframe 7: Rescale
	kf = track->createNodeKeyFrame(DURATION_STEP * 8);
	//Mantiene la posicion
	kf->setTranslate(_ogreheadKeyFramePos);
	//Sigue mirando a derecha
	kf->setRotation(Quaternion(Degree(0), Vector3(0, 1, 0)));
	//Se va haciendo pequenio
	kf->setScale(kf->getScale() * 1);


	// Our defined animation
	_ogreheadAnimationState = _sceneMgr->createAnimationState("ogreIntro");
	_ogreheadAnimationState->setLoop(true);
	_ogreheadAnimationState->setEnabled(true);
}

