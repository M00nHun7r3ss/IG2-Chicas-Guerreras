#include "Labyrinth.h"

Labyrinth::Labyrinth(String f, SceneManager* sceneMng, Hero* h) : _hero(h)
{
    //Lectura archivo laberinto
    std::ifstream file(f);
    if (!file.is_open())
    {
        cout << "Error al abrir " << f << endl;
        exit(EXIT_FAILURE);
    }
	
    file >> _nFils >> _nCols;

    char lee;

    // tamanio entre cada espacio
    Wall* aux = new Wall(Vector3::ZERO, sceneMng->getRootSceneNode()->createChildSceneNode(), sceneMng);
    aux->setVisible(false);
	_boxSize = aux->calculateBoxSize();

    // tamanio vector cajas.
    _labyrinth.reserve(_nFils * _nCols);

    // leemos cada fila
    for (int i = 0; i < _nFils; i++) {
        for (int j = 0; j < _nCols; j++) {
            file >> lee;

            if (lee == 'x') {
                // crea elemento muro
                _labyrinth.push_back(new Wall(Vector3(_boxSize.x * j, 0, _boxSize.z * i), sceneMng->getRootSceneNode()->createChildSceneNode(), sceneMng));
            }
            else if (lee == 'o') {
                // crea elemento vacio
                _labyrinth.push_back(new Empty(Vector3(_boxSize.x * j, 0, _boxSize.z * i), sceneMng->getRootSceneNode()->createChildSceneNode(), sceneMng));
            }
            else if (lee == 'h') {
                // crea elemento vacio
                _labyrinth.push_back(new Empty(Vector3(_boxSize.x * j, 0, _boxSize.z * i), sceneMng->getRootSceneNode()->createChildSceneNode(), sceneMng));
                // crea hero
                _hero->setPosition(Vector3(_boxSize.x * j, 10, _boxSize.z * i));
            	_hero->setScale(Vector3(_boxSize.x / _hero->calculateBoxSize().x, _boxSize.y / _hero->calculateBoxSize().y + 5, _boxSize.z / _hero->calculateBoxSize().z)/2);
                _labyrinth.push_back(_hero);
                addInputListener(_hero);
            }
        }
    }

    _width = _nCols * _boxSize.x;
    _height = _nFils * _boxSize.y;

    _pos = Vector3(_width / 2, 0.0f, _height / 2);
}

Vector2 Labyrinth::getBlockPosition(Vector3 pos){
    int nBlocksWidth = _width / _boxSize.x;
    int nBlocksHeight = _height / _boxSize.z;
    return Vector2((nBlocksWidth - 1) - int(pos.x / _boxSize.x), (nBlocksHeight - 1) - int(pos.z / _boxSize.z));
}

bool Labyrinth::getBlockType(Vector2 blockPos){

    //n fila + n columna + (n fila * n columnas del laberinto)
    IG2Object* block = _labyrinth[(blockPos.y) * _nCols + blockPos.x];
    //std::cout << "El bloque que esta delante del Hero es: " << getBlockPosition(block->getPosition()) << std::endl;
    //std::cout << "¿El bloque es traspasble? " << block->isTraspasable() << std::endl;
    return block->isTraspasable();
}

void Labyrinth::canHeroGoForward() {
    // 1. Calculamos la pos en bloques del hero.
    Vector2 heroBlockPos = getBlockPosition(_hero->getPosition());

    std::cout << "El Hero esta en: " << heroBlockPos << std::endl;
    
    // 1. Calculamos el siguiente bloque en cuestion a la posicion y direccion de hero
    Vector2 forwardBlock = Vector2(heroBlockPos.x - _hero->getOrientation().z, heroBlockPos.y - _hero->getOrientation().x);

    //std::cout << "Orientacion del heroe: " << _hero->getOrientation() << std::endl;

    //std::cout << "El bloque delante del Hero es: " << forwardBlock << std::endl;

    // 2. Miramos si es traspasable y lo seteamos.
    //_hero->setCanGoForward(getBlockType(forwardBlock));
}
