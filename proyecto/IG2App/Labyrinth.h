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
#include "Villain.h"

class Labyrinth : public OgreBites::IG2ApplicationContext, OgreBites::InputListener {
public:
    explicit Labyrinth(String file, SceneManager* sceneMng, Hero* h, std::vector<Villain*> v);

    inline Vector3 getPos() { return _pos; }
    inline float getHeight() { return _height; }
    inline float getWidth() { return _width; }
    inline Vector3 getBoxSize() { return _boxSize; }

    // le pasas una posicion del laberinto y te devuelve que bloque es.
    // ej.: de izq a der -> (0, 0), (1, 0), (2, 0) ...
    Vector2 getBlockPosition(Vector3 pos);

    // devuelve el tipo de bloque en la posicion dada (Wall - false, Empty - true)
    bool getBlockType(Vector2 blockPos);

    // define si el hero puede avanzar a la siguiente casilla o no
    // settea en el player si WALL -> false, EMPTY -> true
    void canHeroGoForward();

    void rotate();

private:
    // Personajes.
    Hero* _hero;
    std::vector<Villain*> _villains;

    //vector cajas
    std::vector <IG2Object*> _labyrinth; 

    //ancho y alto del laberinto, en plano xz
    float _width;
    float _height;

    //filas y columnas del txt
    int _nFils; 
    int _nCols;

    Vector3 _pos;

    // es la posicion del bloque actual, ej.: (1, 5), (6, 18)...
    // son como el v.size(), si se desea sacar la posicion actual reste 1.
    // int _nBlocksWidth = _width / _boxSize.x; 
    // int _nBlocksHeight = _height / _boxSize.z;
    // TODO hacer luego porque da problemas

    //tamanio bloque
    Vector3 _boxSize;
};

