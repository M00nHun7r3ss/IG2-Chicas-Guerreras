#include "Scene.h"

Scene::Scene(SceneManager* sm, OgreBites::TrayManager* tm, Light* l, SceneNode* lp, SceneNode* ln, SceneNode* cn, OgreBites::CameraMan* cm, bool sceneType)
	: _sceneMgr(sm), _trayMgr(tm), _light(l), _lightParent(lp), _lightNode(ln), _camNode(cn), _camMgr(cm), _sceneType(sceneType) {
}


void Scene::createPlane(string mat, Vector3 pos, float width, float height) {
    MeshManager::getSingleton().createPlane("mPlane1080x800" + _sceneType,
        ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        Plane(Vector3::UNIT_Y, 0),
        width, height, 100, 80,
        true, 1, 1.0, 1.0, Vector3::UNIT_Z);
    _planeEntity = _sceneMgr->createEntity("mPlane1080x800" + _sceneType);
    _planeNode = _sceneMgr->getRootSceneNode()->createChildSceneNode("floor" + _sceneType);
    _planeNode->setPosition(pos);
    _planeNode->attachObject(_planeEntity);
    _planeEntity->setMaterialName(mat);
}

void Scene::createDirectionalLight() {
    _sceneMgr->setAmbientLight(ColourValue(0.7, 0.8, 0.9));
    _light = _sceneMgr->createLight("Directional" + _sceneType);
    _light->setType(Ogre::Light::LT_DIRECTIONAL);
    _light->setDiffuseColour(0.75, 0.75, 0.75);
    // Node with the light attached
    _lightNode = _camNode->createChildSceneNode("nLuz" + _sceneType);
    _lightNode->attachObject(_light);
}
