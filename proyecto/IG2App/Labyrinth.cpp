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

    int numFilas;
    file >> numFilas;

    int numColumnas;
    file >> numColumnas;

    char lee;

    // tamanio entre cada espacio
    Wall* aux = new Wall(Vector3::ZERO, sceneMng->getRootSceneNode()->createChildSceneNode(), sceneMng);
    aux->setVisible(false);
	_boxSize = aux->calculateBoxSize();

    // tamanio vector cajas.
    _labyrinth.reserve(numFilas * numColumnas);

    // leemos cada fila
    for (int i = 0; i < numFilas; i++) {
        for (int j = 0; j < numColumnas; j++) {
            file >> lee;
            //std::cout << lee;

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
            	_hero->setScale(Vector3(_boxSize.x / _hero->calculateBoxSize().x, _boxSize.y / _hero->calculateBoxSize().y + 5, _boxSize.z / _hero->calculateBoxSize().z));
                _labyrinth.push_back(_hero);
                addInputListener(_hero);
            }
        }
    }

    _width = numColumnas * _boxSize.x;
    _height = numFilas * _boxSize.y;

    _pos = Vector3(_width / 2, 0.0f, _height / 2);
}

Vector2 Labyrinth::getBlockPosition(Vector3 pos){
    int nBlocksWidth = _width / _boxSize.x;
    int nBlocksHeight = _height / _boxSize.z;
    return Vector2((nBlocksWidth - 1) - int(pos.x / _boxSize.x), (nBlocksHeight - 1) - int(pos.z / _boxSize.z));
}

bool Labyrinth::getBlockType(Vector2 blockPos)
{
    int i = 0;
    //Buscamos el bloque que coincida con la pos dada
    while (i < _labyrinth.size())
    {
        Vector2 auxPos = getBlockPosition(_labyrinth[i]->getPosition());
        if (auxPos == blockPos)
        {
            std::cout << _labyrinth[i]->isTraspasable() << std::endl;
            return (_labyrinth[i]->isTraspasable());
        }
        i++;
    }

    std::cout << _labyrinth[i]->isTraspasable() << std::endl;

    //Si no lo encuentra (condicion de seguridad)
    return (_labyrinth[i]->isTraspasable());
}

void Labyrinth::canHeroGoForward()
{
    //Calculamos el siguiente bloque en cuestion a la posicion y direccion de hero
    Vector3 forwardPos = _hero->getPosition() + _hero->getDirection();

    //Sacamos la pos en la matriz del laberinto
    Vector2 blockPos = getBlockPosition(forwardPos);

    //Sacamos si la siguiente pos es traspasable o no
    //y lo seteamos en el player
    _hero->setCanGoForward(getBlockType(blockPos));
}

