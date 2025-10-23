#include "Labyrinth.h"

Labyrinth::Labyrinth(String f, SceneManager* sceneMng, Hero* h, std::vector<Villain*> v) : _hero(h), _villains(v)
{
    createLabyrinth(f, sceneMng);

    _width = _nCols * _boxSize.x;
    _height = _nFils * _boxSize.y;

    _pos = Vector3(_width / 2, 0.0f, _height / 2);

    _allDirs = {
        Vector3::UNIT_X,		  // left [0]
        Vector3::NEGATIVE_UNIT_X, // right [1]
        Vector3::UNIT_Z,		  // up [2]
        Vector3::NEGATIVE_UNIT_Z  // down [3]
    };
}

Vector2 Labyrinth::getBlockPosition(Vector3 pos){
    /*int nBlocksWidth = _width / _boxSize.x;
    int nBlocksHeight = _height / _boxSize.z;
    return Vector2((nBlocksWidth -1) - int(pos.x / _boxSize.x), (nBlocksHeight -1) - int(pos.z / _boxSize.z));*/

    //DENISA AQUI
    // Usamos el centro del bloque como referencia
    float halfX = _boxSize.x * 0.5f;
    float halfZ = _boxSize.z * 0.5f;

    // Posición relativa y redondeamos a la celda más cercana
	//Explicación: ponemos pos.x + halfX para que si el héroe está a mitad entre dos bordes, vaya a la celda más intuitiva(redondeo al centro)
    // columna: x crece hacia la derecha -> col 0 = izquierda
    int col = _nCols - 1 - int(std::floor((pos.x + halfX) / _boxSize.x)); // 0 = izquierda

    // fila: queremos row 0 = fila superior del fichero.
    // La lectura del fichero usó i desde _nFils..1 y puso z = boxSize.z * i,
    // así que las filas superiores tienen z más grande.
    // Primero calculamos la fila "desde abajo" y luego invertimos:
    int row = _nFils - int(std::floor((pos.z + halfZ) / _boxSize.z));  // 0 = arriba

    // Clamp para que no salte fuera de rango
    if (col < 0) col = 0;
    if (col >= _nCols) col = _nCols - 1;
    if (row < 0) row = 0;
    if (row >= _nFils) row = _nFils - 1;

    return Vector2(col, row); // x = columna, y = fila
}

bool Labyrinth::getBlockType(Vector2 blockPos){

    ////n fila + n columna + (n fila * n columnas del laberinto)
    //IG2Object* block = _labyrinth[(blockPos.y) * _nCols + blockPos.x];
    //std::cout << "El bloque que esta delante del Hero es: " << getBlockPosition(block->getPosition()) << std::endl;
    //std::cout << "El bloque es traspasble? " << block->isTraspasable() << std::endl;
    //return block->isTraspasable();

    //Forzamos int
    int col = (int)blockPos.x;
    int row = (int)blockPos.y;

    //Miramos fuera de rango
    if (col < 0 || col >= _nCols || row < 0 || row >= _nFils) {
        std::cout << "getBlockType: indices fuera de rango (" << col << "," << row << ")\n";
        return false; // fuera del laberinto se considera NO traspasable
    }

    //Sacamos el bloque concreto 
    IG2Object* block = _labyrinth[row * _nCols + col];
    //std::cout << "El bloque en (" << col << "," << row << ") es traspasable? " << block->isTraspasable() << std::endl;
    return block->isTraspasable();
}

Vector2 Labyrinth::getCharacterForwardBlock(Character* c)
{
    // 1. Posicion actual del hero en la cuadricula
    Vector2 blockPos = getBlockPosition(c->getPosition());

    // 2. Direccion de movimiento actual del hero (en mundo)
    Vector3 dir = c->getOrientation();

    // 3. Convertimos direccion mundo a desplazamiento en celdas (top-left origin)
    // En la cuadricula:
    //  - derecha = +1 columna
    //  - izquierda = -1 columna
    //  - arriba (hacia el norte, z mayor) = -1 fila
    //  - abajo (hacia el sur, z menor) = +1 fila
    int dCol = 0;
    int dRow = 0;

    if (dir.x > 0.5f) dCol = -1;         // derecha
    else if (dir.x < -0.5f) dCol = +1;   // izquierda
    else if (dir.z > 0.5f) dRow = -1;    // arriba
    else if (dir.z < -0.5f) dRow = +1;   // abajo

    Vector2 forwardBlock(blockPos.x + dCol, blockPos.y + dRow);

    std::cout << "Hero esta en celda: " << blockPos << " y su celda delante: " << forwardBlock << std::endl;

    //Forzamos la posicion de hero en el centro de la casilla
    //_hero->setPosition(Vector3(forwardBlock.x * _boxSize.x/2, _hero->getPosition().y, forwardBlock.y * _boxSize.z / 2));

    return forwardBlock;
}

Vector2 Labyrinth::getCharacterLeftBlock(Character* c)
{
    //// 1. Calculamos la pos en bloques del hero.
    //Vector2 heroBlockPos = getBlockPosition(_hero->getPosition());
    //std::cout << "El Hero esta en: " << heroBlockPos << std::endl;

    ////std::cout << "El Hero esta en [coords reales]: " << _hero->getPosition() << std::endl;

    //// 1. Calculamos el siguiente bloque en cuestion a la posicion y direccion de hero
    //Vector2 LeftBlock = Vector2(heroBlockPos.x, heroBlockPos.y + _hero->getOrientation().x);
    //std::cout << "Bloque de delante del Hero: " << LeftBlock << std::endl;
    ////std::cout << "Orientacion del heroe: " << _hero->getOrientation() << std::endl;

    //getBlockType(LeftBlock);

    //return LeftBlock;

    Vector2 heroBlockPos = getBlockPosition(_hero->getPosition());
    Vector3 dir = _hero->getDirection();

    int dCol = 0;
    int dRow = 0;

    // Giramos 90° a la izquierda (desde la dirección actual)
    if (dir.x > 0.5f) { dRow = -1; } // derecha - arriba
    else if (dir.x < -0.5f) { dRow = +1; } // izquierda - abajo
    else if (dir.z > 0.5f) { dCol = -1; } // arriba - izquierda
    else if (dir.z < -0.5f) { dCol = +1; } // abajo - derecha

    Vector2 leftBlock(heroBlockPos.x + dCol, heroBlockPos.y + dRow);

    std::cout << "Hero celda izquierda: " << leftBlock << std::endl;
    return leftBlock;
}

Vector2 Labyrinth::getCharacterRightBlock(Character* c)
{
    Vector2 heroBlockPos = getBlockPosition(_hero->getPosition());
    Vector3 dir = _hero->getDirection();

    int dCol = 0;
    int dRow = 0;

    // Giramos 90° a la derecha (desde la dirección actual)
    if (dir.x > 0.5f) { dRow = +1; } // derecha - abajo
    else if (dir.x < -0.5f) { dRow = -1; } // izquierda - arriba
    else if (dir.z > 0.5f) { dCol = +1; } // arriba - derecha
    else if (dir.z < -0.5f) { dCol = -1; } // abajo - izquierda

    Vector2 rightBlock(heroBlockPos.x + dCol, heroBlockPos.y + dRow);

    std::cout << "Hero celda derecha: " << rightBlock << std::endl;
    return rightBlock;
}

std::vector<Vector3> Labyrinth::choosePossibleDirs(Character* c)
{
    std::vector<Vector3> possibleDirs; // aux

    if (!getBlockType(getCharacterLeftBlock(c))) possibleDirs.push_back(_allDirs[0]); // izq
    else if (!getBlockType(getCharacterRightBlock(c))) possibleDirs.push_back(_allDirs[1]); // der
    else if (!getBlockType(getCharacterForwardBlock(c))) possibleDirs.push_back(_allDirs[2]); // forward
    else possibleDirs.push_back(_allDirs[3]); // atras

    // devuelve las posibles direcciones a las que puedes ir en este instante.
    return possibleDirs;
}

Vector3 Labyrinth::calculateRandomDir(Character* c)
{
    // caso cruce varias opciones: nueva dir aleatoria menos giro 180º
    // caso muro enfrente: si puede evitar 180º, lo evita, si no, lo hace

    // direcciones posibles en este instante
    std::vector<Vector3> vDirs = choosePossibleDirs(c);

    // random dir between 0 and v.size()-1
	return vDirs[std::rand() % vDirs.size()];
}

void Labyrinth::createLabyrinth(String f, SceneManager* sceneMng)
{
    //Lectura archivo laberinto
    std::ifstream file(f);
    if (!file.is_open())
    {
        cout << "Error al abrir " << f << endl;
        exit(EXIT_FAILURE);
    }
    std::string wallMat;
    std::string light;

    file >> _nFils >> _nCols >> wallMat >> _floorMat >> light;

    if (light == "directional") { _lightType = 0; }
    else if (light == "spot") { _lightType = 1; }
    else if (light == "point") { _lightType = 2; }

    char lee;

    // tamanio entre cada espacio
    Wall* aux = new Wall(Vector3::ZERO, sceneMng->getRootSceneNode()->createChildSceneNode(), sceneMng);
    aux->setVisible(false);
    _boxSize = aux->calculateBoxSize();

    // tamanio vector cajas.
    _labyrinth.reserve(_nFils * _nCols);

    // leemos cada fila (nota: le hemos dado la vuelta al laberinto para que el 0 este en la esquina superior izquierda.
    for (int i = _nFils; i > 0; i--) {
        for (int j = 0; j < _nCols; j++) {
            file >> lee;

            Vector3 actualPos = Vector3(_boxSize.x * j, 0, _boxSize.z * i);

            if (lee == 'x') {
                // crea elemento muro y le asigna el nombre del material
                Wall* x = new Wall(actualPos, sceneMng->getRootSceneNode()->createChildSceneNode(), sceneMng);
                x->setMaterialName(wallMat);
                _labyrinth.push_back(x);
            }
            else if (lee == 'o') {
                // crea elemento vacio
                _labyrinth.push_back(new Empty(actualPos, sceneMng->getRootSceneNode()->createChildSceneNode(), sceneMng));
            }
            else if (lee == 'h') {
                // crea elemento vacio
                _labyrinth.push_back(new Empty(actualPos, sceneMng->getRootSceneNode()->createChildSceneNode(), sceneMng));
                // crea hero
                _hero->setPosition(actualPos);
                _hero->setScale(Vector3(_boxSize.x / _hero->calculateBoxSize().x, _boxSize.y / _hero->calculateBoxSize().y + 5, _boxSize.z / _hero->calculateBoxSize().z) / 2);
            }
            else if (lee == 'v' && _villains.size() < 10) {
                // crea elemento vacio
                _labyrinth.push_back(new Empty(actualPos, sceneMng->getRootSceneNode()->createChildSceneNode(), sceneMng));
                // crea villain.
                Villain* v = new Villain(actualPos, sceneMng->getRootSceneNode()->createChildSceneNode(), sceneMng);
                v->setScale(Vector3(0.75));
                //v->setDirection(calculateRandomDir(v));
                _villains.push_back(v);
            }
        }
    }
}

void Labyrinth::createFloor(SceneManager* sm, std::string mat){
   MeshManager::getSingleton().createPlane("mPlane1080x800",
        ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        Plane(Vector3::UNIT_Y, 0),
        getWidth(), getHeight(), 100, 80,
        true, 1, 1.0, 1.0, Vector3::UNIT_Z);
    Ogre::Entity* plane = sm->createEntity("mPlane1080x800");
    Ogre::SceneNode* mSceneNewNode = sm->getRootSceneNode()->createChildSceneNode("floor");
    mSceneNewNode->setPosition(getWidth() / 2, getBoxSize().y / 2, getHeight() / 2);
    mSceneNewNode->attachObject(plane);
    //plane->setMaterialName(mat);
}

