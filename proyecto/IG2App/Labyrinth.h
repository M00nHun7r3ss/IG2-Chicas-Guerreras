#pragma once

#include "IG2ApplicationContext.h"
#include "IG2Object.h"
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
#include "Wall.h"
#include "Empty.h"
#include "Hero.h"

class Labyrinth : public OgreBites::IG2ApplicationContext, OgreBites::InputListener {
public:
    explicit Labyrinth(String file, SceneManager* sceneMng, Hero* h);

    inline Vector3 getPos() { return _pos; }
    inline float getHeight() { return _height; }
    inline float getWidth() { return _width; }

    // le pasas una posicion del laberinto y te devuelve que bloque es.
    // ej.: de izq a der -> (0, 0), (1, 0), (2, 0) ...
    Vector2 getBlockPosition(Vector3 pos);

private:
    Hero* _hero;

    float _width;
    float _height;

    Vector3 _pos;

    // es la posicion del bloque actual, ej.: (1, 5), (6, 18)...
    // son como el v.size(), si se desea sacar la posicion actual reste 1.
    // int _nBlocksWidth = _width / _boxSize.x; 
    // int _nBlocksHeight = _height / _boxSize.z;
    // TODO hacer luego porque da problemas

    Vector3 _boxSize;
};

