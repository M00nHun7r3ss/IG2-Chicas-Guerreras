#include "Scene.h"

Scene::Scene(SceneManager* sm, OgreBites::TrayManager* tm, Light* l, SceneNode* lp, SceneNode* ln, SceneNode* cn, OgreBites::CameraMan* cm)
	: _sceneMgr(sm), _trayMgr(tm), _light(l), _lightParent(lp), _lightNode(ln), _camNode(cn), _camMgr(cm) {
}

void Scene::createPlane(string mat, Vector3 pos, float width, float height) {
    MeshManager::getSingleton().createPlane("mPlane1080x800",
        ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        Plane(Vector3::UNIT_Y, 0),
        width, height, 100, 80,
        true, 1, 1.0, 1.0, Vector3::UNIT_Z);
    Ogre::Entity* plane = _sceneMgr->createEntity("mPlane1080x800");
    Ogre::SceneNode* mSceneNewNode = _sceneMgr->getRootSceneNode()->createChildSceneNode("floor");
    mSceneNewNode->setPosition(pos);
    mSceneNewNode->attachObject(plane);
    plane->setMaterialName(mat);
}

void Scene::createDirectionalLight() {
    _sceneMgr->setAmbientLight(ColourValue(0.7, 0.8, 0.9));
    _light = _sceneMgr->createLight("Directional");
    _light->setType(Ogre::Light::LT_DIRECTIONAL);
    _light->setDiffuseColour(0.75, 0.75, 0.75);
    // Node with the light attached
    _lightNode = _camNode->createChildSceneNode("nLuz");
    _lightNode->attachObject(_light);
}

void Scene::createSpotLight() {
}

void Scene::createPointLight() {
}
