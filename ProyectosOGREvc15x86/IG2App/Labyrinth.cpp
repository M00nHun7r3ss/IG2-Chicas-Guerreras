#include "Labyrinth.h"

Labyrinth::Labyrinth(String f, SceneManager* sceneMng)
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

    // creamos vector cajas. TODO: sera una clase luego 1. LABERINTO 2.MURO 3. VACIO
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
        }
    }

}
