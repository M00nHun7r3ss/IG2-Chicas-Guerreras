#include "Labyrinth.h"

Labyrinth::Labyrinth(String f, SceneManager* sceneMng, Hero* h, std::vector<Villain*>& v) : _hero(h), _villains(v) {
    createLabyrinth(f, sceneMng);

    // tamanio del laberinto (en distancia).
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

Vector2 Labyrinth::getBlockPosition(Vector3 pos, Vector3 dir){
    // esto sirve para centrar al personaje segun el bloque dependiendo de la direccion (prueba y error), viendo el margen.
    float marginCols = 0;
    float marginFils = 0;

    // hoy hemos aprendido que no se puede hacer switch de vector3
    if (dir == _allDirs[0]) { // left
        marginCols = _boxSize.x * 0.05f;
    }
    else if (dir == _allDirs[1]) { // right
        marginCols = _boxSize.x * 0.95f;
    }
    else if (dir == _allDirs[2]) { // up 
        marginFils = _boxSize.z * 0.05f;
    }
    else if (dir == _allDirs[3]) { // down
        marginFils = _boxSize.z * 0.95f;
    }

    // posicion en casillas, teselas, celdas... (como si fuera matriz).
    int col = _nCols - 1 - int((pos.x+ marginCols)  / _boxSize.x); // 0 = izquierda
    int row = _nFils - int(((pos.z+ marginFils) / _boxSize.z));  // 0 = arriba

    return Vector2(col, row); // x = columna, y = fila
}

bool Labyrinth::getBlockType(Vector2 blockPos){

    // sacamos el bloque concreto que le hemos pasado
    IG2Object* block = _labyrinth[blockPos.y * _nCols + blockPos.x];

    return block->isTraspasable();
}

Vector2 Labyrinth::getCharacterForwardBlock(Character* c)
{
    // Cogemos la direccion del personaje
    Vector3 dir = c->getOrientation();

    // Miramos su posicion actual en la cuadricula
    Vector2 blockPos = getBlockPosition(c->getPosition(), dir);

    // Convertimos direccion a desplazamiento en celdas
    // En la cuadricula:
    //  - derecha = -1 columna
    //  - izquierda = +1 columna
    //  - arriba = -1 fila
    //  - abajo = +1 fila
    Vector2 forwardBlock(blockPos.x - dir.x, blockPos.y - dir.z);

    return forwardBlock;
}

Vector2 Labyrinth::getCharacterLeftBlock(Character* c)
{
    // Cogemos la direccion del personaje
    Vector3 dir = c->getOrientation();

    // Miramos su posicion actual en la cuadricula
    Vector2 blockPos = getBlockPosition(c->getPosition(), dir);

    // Convertimos direccion a desplazamiento en celdas
	// En la cuadricula, las izquierdas de las direcciones son:
	//  - izquierda -> abajo (0, 0, 1)
	//  - derecha -> arriba (0, 0, -1)
	//  - arriba -> izquierda (-1, 0, 0)
	//  - abajo -> derecha (1, 0, 0)
    int dCol = 0;
    int dFil = 0;

    if (dir == _allDirs[0]) { // left
        dFil = 1;
    }
    else if (dir == _allDirs[1]) { // right
        dFil = -1;
    }
    else if (dir == _allDirs[2]) { // up 
        dCol = -1;
    }
    else if (dir == _allDirs[3]) { // down
        dCol = 1;
    }

    Vector2 leftBlock(blockPos.x + dCol, blockPos.y + dFil);

    return leftBlock;
}

Vector2 Labyrinth::getCharacterRightBlock(Character* c)
{
    // Cogemos la direccion del personaje
    Vector3 dir = c->getOrientation();

    // Miramos su posicion actual en la cuadricula
    Vector2 blockPos = getBlockPosition(c->getPosition(), dir);

    // Convertimos direccion a desplazamiento en celdas
    // En la cuadricula, las derechas de las direcciones son:
    //  - izquierda -> arriba (0, 0, -1)
    //  - derecha -> abajo (0, 0, 1)
    //  - arriba -> derecha (1, 0, 0)
    //  - abajo -> izquierda (-1, 0, 0)
    int dCol = 0;
    int dFil = 0;

    if (dir == _allDirs[0]) { // left
        dFil = -1;
    }
    else if (dir == _allDirs[1]) { // right
        dFil = 1;
    }
    else if (dir == _allDirs[2]) { // up 
        dCol = 1;
    }
    else if (dir == _allDirs[3]) { // down
        dCol = -1;
    }

    Vector2 rightBlock(blockPos.x + dCol, blockPos.y + dFil);

    return rightBlock;
}

std::vector<Vector3> Labyrinth::choosePossibleDirs(Character* c)
{
    std::vector<Vector3> possibleDirs; // aux

    //Izquierda, derecha y atras calculados con la regla de la mano derecha y crossProduct
    //El laberinto esta al reves, y por tanto hay que darle la vuelta a left y a right
    Vector3 left = c->getOrientation().crossProduct(Vector3::UNIT_Y);
    Vector3 right = c->getOrientation().crossProduct(Vector3::NEGATIVE_UNIT_Y);
    Vector3 back = left.crossProduct(Vector3::UNIT_Y);


	if (!getBlockType(getCharacterForwardBlock(c))) {
    	possibleDirs.push_back(c->getOrientation()); // forward (la direccion actual)
    }
    if (!getBlockType(getCharacterLeftBlock(c))) {
    	possibleDirs.push_back(left); // izq
    }

	if (!getBlockType(getCharacterRightBlock(c))) {
        possibleDirs.push_back(right); // der
    }

    //Esta siempre estara disponible
	possibleDirs.push_back(back); // atras (contrario de la direccion actual)

    // devuelve las posibles direcciones a las que puedes ir en este instante.
    return possibleDirs;
}

Vector3 Labyrinth::calculateRandomDir(Character* c)
{
    // caso cruce varias opciones: nueva dir aleatoria menos giro 180º
    // caso muro enfrente: si puede evitar 180º, lo evita, si no, lo hace

    // direcciones posibles en este instante
    std::vector<Vector3> vDirs = choosePossibleDirs(c);

    Vector3 vReturn;

    //La direccion atras siempre esta disponible
    //Si hay mas direcciones que para atras
    if (vDirs.size() > 1)
    {
        // random dir between 0 and v.size() - 2 para evitar la direccion de atras
        vReturn = vDirs[std::rand() % (vDirs.size() - 1)];
    }
    //Si la unica direccion que hay es atras
    else
    {
	    //elige atras (la ultima)
        vReturn = vDirs.back();
    }

    //Cogemos la rotacion que debe hacer entre la rotacion actual (orientation) y la nueva (_newDirection) 
    Quaternion q = c->getOrientation().getRotationTo(vReturn);

    //Y rotamos en el eje y, solo la componente y de dicho quaternion
    c->yaw(q.getYaw());

    return vReturn;
}

void Labyrinth::setVisible(bool visible)
{
    for (int i = 0; i < _labyrinth.size(); i++)
    {
        _labyrinth[i]->setVisible(visible);
    }
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
                _hero->setFirstPos(actualPos);
                _hero->setScale(Vector3(_boxSize.x / _hero->calculateBoxSize().x, _boxSize.y / _hero->calculateBoxSize().y + 5, _boxSize.z / _hero->calculateBoxSize().z) / 2);
                _hero->createAnimation();
            }
            else if (lee == 'v' && _villains.size() < 10) {
                // crea elemento vacio
                _labyrinth.push_back(new Empty(actualPos, sceneMng->getRootSceneNode()->createChildSceneNode(), sceneMng));
                // crea villain.
                Villain* v = new Villain(actualPos, sceneMng->getRootSceneNode()->createChildSceneNode(), sceneMng);
                v->setScale(Vector3(0.75));
                _villains.push_back(v);
            }
        }
    }
}