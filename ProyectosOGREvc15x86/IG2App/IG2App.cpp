#include "IG2App.h"


using namespace Ogre;
using namespace std;

bool IG2App::keyPressed(const OgreBites::KeyboardEvent& evt){
        
    // ESC key finished the rendering...
    if (evt.keysym.sym == SDLK_ESCAPE){
        getRoot()->queueEndRendering();
    }
    
  return true;
}

void IG2App::shutdown(){
    
  mShaderGenerator->removeSceneManager(mSM);
  mSM->removeRenderQueueListener(mOverlaySystem);  
					
  mRoot->destroySceneManager(mSM);  

  delete mTrayMgr;  mTrayMgr = nullptr;
  delete mCamMgr; mCamMgr = nullptr;
  
  // do not forget to call the base 
  IG2ApplicationContext::shutdown(); 
}

void IG2App::setup(void){
    
    // do not forget to call the base first
    IG2ApplicationContext::setup();

    // Create the scene manager
    mSM = mRoot->createSceneManager();

    // Register our scene with the RTSS
    mShaderGenerator->addSceneManager(mSM);

    mSM->addRenderQueueListener(mOverlaySystem);
    mTrayMgr = new OgreBites::TrayManager("TrayGUISystem", mWindow.render);
    mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
    addInputListener(mTrayMgr);
    
    // Adds the listener for this object
    addInputListener(this);
    setupScene();
}

void IG2App::setupScene(void){
    
    //------------------------------------------------------------------------
    // Creating the camera
    
    Camera* cam = mSM->createCamera("Cam");
    cam->setNearClipDistance(1);
    cam->setFarClipDistance(10000);
    cam->setAutoAspectRatio(true);
    //cam->setPolygonMode(Ogre::PM_WIREFRAME);
            
    mCamNode = mSM->getRootSceneNode()->createChildSceneNode("nCam");
    mCamNode->attachObject(cam);

    mCamNode->setPosition(0, 0, 1000);
    mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);
    
    // and tell it to render into the main window
    Viewport* vp = getRenderWindow()->addViewport(cam);
    
    mCamMgr = new OgreBites::CameraMan(mCamNode);
    addInputListener(mCamMgr);
    mCamMgr->setStyle(OgreBites::CS_ORBIT);
    
    
    //------------------------------------------------------------------------
    // Creating the light
    
    mSM->setAmbientLight(ColourValue(0.7, 0.8, 0.9));
    /*Light* luz = mSM->createLight("Luz");
    luz->setType(Ogre::Light::LT_DIRECTIONAL);
    luz->setDiffuseColour(0.75, 0.75, 0.75);*/

    mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
    //mLightNode = mCamNode->createChildSceneNode("nLuz");
    //mLightNode->attachObject(luz);
    //mLightNode->setDirection(Ogre::Vector3(0, 0, -1)); //Luz de frente
    //mLightNode->setDirection(Ogre::Vector3(0, 1, 0)); //Luz de abajo
    //mLightNode->setDirection(Ogre::Vector3(-1, -0.25, 0.25)); //Luz de lado
    

    
    //------------------------------------------------------------------------
    // Creating Sinbad

    //Ogre::Entity* ent = mSM->createEntity("Sinbad.mesh");
    //mSinbadNode = mSM->getRootSceneNode()->createChildSceneNode("nSinbad");
    //mSinbadNode->attachObject(ent);

    //// Show bounding box
    //mSinbadNode->showBoundingBox(false);
    //
    //// Set position of Sinbad
    ////mSinbadNode->setPosition(x, y, z);
    //
    //// Set scale of Sinbad
    //mSinbadNode->setScale(20, 20, 20);
    //
    ////mSinbadNode->yaw(Ogre::Degree(-45));
    //mSinbadNode->setVisible(false);    

    //------------------------------------------------------------------------
    // CUBOS PARA P1

    IG2Object* cube = nullptr;

    //nuevo objeto 
    cube = new IG2Object(
        Vector3::ZERO,                                   // pos inicial
        mSM->getRootSceneNode()->createChildSceneNode(), // creamos un nodo nuevo para el hijo
        mSM,                                             // en en SceneManager
        "cube.mesh"                                      // con la malla de cubo
    );

    const Vector3 boxSize = cube->calculateBoxSize();
    cube->setVisible(false);


    //Lectura archivo laberinto
    std::ifstream file("stage1.txt");
    if (!file.is_open())
    {
        cout << "Error al abrir el stageX.txt\n";
        exit(EXIT_FAILURE);
    }

    int numFilas;
    file >> numFilas;
    
    int numColumnas;
    file >> numColumnas;

    char lee; 

    // creamos vector cajas. TODO: sera una clase luego 1. LABERINTO 2.MURO 3. VACIO
    std::vector <IG2Object*> labyrinth(numFilas * numColumnas);

    // leemos cada fila
    for (int i = 0; i < numFilas; i++) {
        for (int j = 0; j < numColumnas; j++) {
            file >> lee;
            std::cout << lee;

            if (lee == 'x') {
                // crea elemento muro
                labyrinth.push_back(new IG2Object(
                    Vector3(boxSize.x * j, 0, boxSize.z * i),                                    // pos inicial
                    mSM->getRootSceneNode()->createChildSceneNode(), // creamos un nodo nuevo para el hijo
                    mSM,                                             // en en SceneManager
                    "cube.mesh"                                      // con la malla de cubo
                ));
            }
            else if (lee == 'o') {
                // crea elemento vacio
                labyrinth.push_back(new IG2Object(
                    Vector3(boxSize.x * j, 0, boxSize.z * i),                                    // pos inicial
                    mSM->getRootSceneNode()->createChildSceneNode(), // creamos un nodo nuevo para el hijo
                    mSM                                              // en en SceneManager
                )); // sin malla
            }
        }
    }


    /*
    //Se pueden poner COUTS
    cout << "Size:" << cube->calculateBoxSize() << endl;

    //Se pueden resizear
    cube->setScale(IG2App::BLOCK_SIZE /  cube->calculateBoxSize() );
    cout << "New size:" << cube->calculateBoxSize() << endl;
    */

    //------------------------------------------------------------------------
    // LABERINTO

    /*
    //Se recomienda usar un solo vector de IG2Object para almacenar, en vez de la matriz, pero intentar trabajar en modo cuadricula
    //Tener en cuenta el tamaño de los bloques etcetc...

    Crear nodo para el laberinto, y luego los cubos son hijos

    //Los vacios son objeto sin malla







    */
}


