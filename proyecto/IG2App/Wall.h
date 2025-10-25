#pragma once

#include "IG2ApplicationContext.h"
#include "IG2Object.h"
#include <OgreTrays.h>
#include <string>

class Wall : public  IG2Object {
public:
    explicit Wall(Vector3 initPos, SceneNode* node, SceneManager* sceneMng) : IG2Object(initPos, node, sceneMng, "cube.mesh"){
        _traspasable = false;
    }
};
