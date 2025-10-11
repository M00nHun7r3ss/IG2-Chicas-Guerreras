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
    const Vector3 boxSize = aux->calculateBoxSize();

    // creamos vector cajas.
    std::vector <IG2Object*> labyrinth(numFilas * numColumnas);

    // leemos cada fila
    for (int i = 0; i < numFilas; i++) {
        for (int j = 0; j < numColumnas; j++) {
            file >> lee;
            //std::cout << lee;

            if (lee == 'x') {
                // crea elemento muro
                labyrinth.push_back(new Wall(Vector3(boxSize.x * j, 0, boxSize.z * i), sceneMng->getRootSceneNode()->createChildSceneNode(), sceneMng));
            }
            else if (lee == 'o') {
                // crea elemento vacio
                labyrinth.push_back(new Empty(Vector3(boxSize.x * j, 0, boxSize.z * i), sceneMng->getRootSceneNode()->createChildSceneNode(), sceneMng));
            }
            else if (lee == 'h') {
                // crea elemento vacio
                labyrinth.push_back(new Empty(Vector3(boxSize.x * j, 0, boxSize.z * i), sceneMng->getRootSceneNode()->createChildSceneNode(), sceneMng));
                // crea hero
                _hero->setPosition(Vector3(boxSize.x * j, 10, boxSize.z * i));
            	_hero->setScale(Vector3(boxSize.x / _hero->calculateBoxSize().x, boxSize.y / _hero->calculateBoxSize().y + 5, boxSize.z / _hero->calculateBoxSize().z));
                labyrinth.push_back(_hero);
                addInputListener(_hero);
            }
        }
    }

    _width = numColumnas * boxSize.x;
    _height = numFilas * boxSize.y;
    _pos = Vector3(_width / 2, 0.0f, _height / 2);

}
