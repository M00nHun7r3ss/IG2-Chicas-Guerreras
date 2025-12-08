#pragma once

#include "IG2ApplicationContext.h"
//#include "OgreApplicationContext.h"
#include "IG2Object.h"

class Empty : public  IG2Object {
public:
	explicit Empty(Vector3 initPos, SceneNode* node, SceneManager* sceneMng) : IG2Object(initPos, node, sceneMng){
		_traspasable = true;
	}
};

