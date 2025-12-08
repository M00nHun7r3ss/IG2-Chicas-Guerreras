#pragma once

#include "IG2ApplicationContext.h"
//#include "OgreApplicationContext.h"
#include "IG2Object.h"
#include <OgreEntity.h>
#include <OgreInput.h>
#include <string>
#include <vector>
#include "Wall.h"
#include "Empty.h"
#include "Hero.h"
#include "Villain.h"

class Labyrinth : public OgreBites::IG2ApplicationContext, OgreBites::InputListener {
public:
    explicit Labyrinth(String file, SceneManager* sceneMng, Hero* h, std::vector<Villain*>& v);

    Vector2 getBlockPosition(Vector3 pos, Vector3 dir = Vector3(0.0f));

    inline Vector3 getPos() { return _pos; }
    inline float getHeight() { return _height; }
    inline float getWidth() { return _width; }
    inline Vector3 getBoxSize() { return _boxSize; }
    inline std::string getFloorMaterial() { return _floorMat; }
    inline int getLightType() { return _lightType; }

    // le pasas una posicion del laberinto y te devuelve que bloque es.
    // ej.: de izq a der -> (0, 0), (1, 0), (2, 0) ...
    Vector2 getBlockPosition(Vector3 pos);

    // devuelve el tipo de bloque en la posicion dada (Wall - false, Empty - true)
    bool getBlockType(Vector2 blockPos);

    // devuelve los bloques contiguos.
    Vector2 getCharacterForwardBlock(Character* c);
    Vector2 getCharacterLeftBlock(Character* c); //TODO ver si se puede comprimir el calculo en vez de ifs
    Vector2 getCharacterRightBlock(Character* c); //TODO ver si se puede comprimir el calculo en vez de ifs

    // saca posibles dirs segun entorno.
    std::vector<Vector3> _allDirs;
    std::vector<Vector3> choosePossibleDirs(Character* c);
    Vector3 calculateRandomDir(Character* c);

    void setVisible(bool visible);

private:
    // Personajes.
    Hero* _hero;
    std::vector<Villain*>& _villains;

    //vector cajas
    std::vector <IG2Object*> _labyrinth;
 
    //ancho y alto del laberinto (en distancia)
    float _width;
    float _height;

    //filas y columnas del txt
    int _nFils; 
    int _nCols;

    //Materials
    std::string _floorMat;

    //Lights
    int _lightType;

    //Posicion del laberinto
    Vector3 _pos;

    //tamanio bloque
    Vector3 _boxSize;

    void createLabyrinth(String f, SceneManager* sceneMng);
};

