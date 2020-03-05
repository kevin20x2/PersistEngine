#include <cstdio>
#include <iostream>
#include <Persist.hpp>
#include <FrameWork/Math/Vectors.hpp>
#include <FrameWork/Scene/World.hpp>
#include <windows.h>
#include <FrameWork/Common/Array.hpp>
#include <FrameWork/Components/Components.hpp>
#include <FrameWork/Geometry/Mesh.hpp>
#include <FrameWork/Unit/SceneUnit.hpp>
using namespace Persist;

int main()
//int WINAPI WinMain(HINSTANCE hInstance , HINSTANCE hPrevInstance ,
//    LPTSTR lpCmdLine , int nCmdShow
//)
{

    std::cout << "hello engine";
    Persist::IApplication * application = 
    Persist::IApplication::currentApplication();


    std::cout <<"sizeof Persit:: Matrix4x4f" << sizeof(Persist::Matrix4x4f) << std::endl  ;

    //clock wise front
    Array <Vector3f> * vertice = new Array <Vector3f>({
        Vector3f(0.5 ,-0.5,-0.5 ) , // 1 right - front  - bottom
        Vector3f(-0.5f ,-0.5f,-0.5) , // 0 left - front - bottom
        Vector3f(-0.5 ,-0.5,0.5),  //  2 left - front - top

        Vector3f(0.5, -0.5,0.5) , 
        Vector3f(0.5, -0.5,-0.5),
        Vector3f(-0.5,-0.5,0.5),

       //bottom
        Vector3f(-0.5 ,- 0.5, -0.5), 
        Vector3f(-0.5, 0.5 , -0.5 ),
        Vector3f(0.5, 0.5, -0.5),

        Vector3f( -0.5 ,-0.5,-0.5) ,
        Vector3f(0.5,0.5,-0.5),
        Vector3f( 0.5 , -0.5 ,-0.5 ) ,
        //left

        Vector3f(-0.5 , -0.5 ,-0.5) ,
        Vector3f(-0.5 , 0.5 , -0.5),
        Vector3f(-0.5, -0.5 , 0.5 )










//        Vector3f(0.5,0.5, 0.5) , //  3 right - front - top
        //Vector3f(-0.5,0.5,-0.5) , //  4 left - back - bottom
        //Vector3f(0.5,0.5,-0.5 ) , //  5 right - back  - bottom
        //Vector3f(-0.5,0.5,0.5),  //   6 left - back - top
        //Vector3f(0.5,0.5, 0.5) , //   7 right - back - top
    });
    Array <Vector4f> * color = new Array <Vector4f> ({
        Vector4f(1.0,0.0,0.0,1.0) , 
        Vector4f(1.0,0.0,0.0,1.0) , 
        Vector4f(1.0,0.0,0.0,1.0) , 

        Vector4f(1.0,0.0,0.0,1.0) , 
        Vector4f(1.0,0.0,0.0,1.0) , 
        Vector4f(1.0,0.0,0.0,1.0) , 
        // bottom

        Vector4f(0.0,1.0,0.0,1.0) , 
        Vector4f(0.0,1.0,0.0,1.0) , 
        Vector4f(0.0,1.0,0.0,1.0) , 

        Vector4f(0.0,1.0,0.0,1.0) , 
        Vector4f(0.0,1.0,0.0,1.0) , 
        Vector4f(0.0,1.0,0.0,1.0) , 

//left
        Vector4f(0.0,0.0,1.0,1.0) , 
        Vector4f(0.0,0.0,1.0,1.0) , 
        Vector4f(0.0,0.0,1.0,1.0) , 

/*
        Vector4f(0.0,1.0,0.0,1.0) , 
        Vector4f(0.0,1.0,0.0,1.0) , 
        Vector4f(0.0,1.0,0.0,1.0) , 
        */

        //Vector4f(1.0,1.0,1.0,1.0) , 
        //Vector4f(1.0,1.0,1.0,1.0) , 
        //Vector4f(1.0,1.0,1.0,1.0) , 
        //Vector4f(1.0,1.0,1.0,1.0) , 
        //Vector4f(1.0,1.0,1.0,1.0) 
    });
    /*
    Vector3f t(-1,-1.0,-1);
    Vector3f v2(1,-1,-1);
    Vector4f t4(1.0,1.0,1.0,1.0);
    float t2[14] = {-1 , -1, -1 ,1.0,1.0,1.0,1.0, 
                      1,-1,-1, 1.0,1.0,1.0,1.0};
    uint8_t buffer[4*14];
    memcpy(buffer , &t , sizeof(Vector3f));
    memcpy(buffer+ sizeof(Vector3f), & t4 , sizeof(Vector4f));
    memcpy(buffer+28 , &v2 , 12  );
    memcpy(buffer+28+12 , &t4 , 16 );

    int ans =memcmp(buffer ,t2 , sizeof(float) * 14 );
    */

    Array<int> *triangles = new Array<int>({
        1, 0, 2,
        2, 1, 3, // front
        //0, 2, 4,
        //4, 2, 6, // left
        //3, 1, 5,
        //3, 5, 7, // right
        //4, 5, 6,
        //5, 6, 7, // back
        //3, 2, 6,
        //6, 3, 7, // top
        //0, 1, 4,
        //1, 4, 5 // bottom
    });

    Mesh * mesh = new Mesh();
    mesh->setVertice(vertice);
    mesh->setTriangles(triangles);
    mesh->setColor(color);


    SceneUnit * cube = new SceneUnit();

    StaticMeshComponent * meshComp = cube->addComponent<StaticMeshComponent>();
    meshComp->setMesh(mesh);

/*
    std::vector < std::shared_ptr<BaseComponent> > vec;
    MeshRenderer * comp = new MeshRenderer(cube);
    std::shared_ptr <MeshRenderer> ptr(comp);
    vec.push_back(ptr);

    std::shared_ptr <MeshRenderer> new_ptr = std::dynamic_pointer_cast<MeshRenderer>(vec[0]);
*/


    MeshRenderer * meshRenderer = cube->addComponent<MeshRenderer>();
    //cube ->addComponent(meshRenderer);

    MeshRenderer * tmp = cube->getComponent<MeshRenderer>();

    World::thisWorld()->activeLevel()->root()->addChild(cube->getTransformComponent());

    CameraUnit * camera = World::thisWorld()->activeLevel()->currentCamera();
    TransformComponent * trans_comp = World::thisWorld()->activeLevel()->currentCamera()->getTransformComponent();
    CameraComponent * camera_comp = World::thisWorld()->activeLevel()->currentCamera()->camera();
    trans_comp->setLocalPosition(Vector3f(-0.5,-2.0 , 0));
    camera_comp->updateViewMatrix();



    application->init();

    while(!application->isQuit()) 
    {
        application->tick();
    }

    std::cout << " exit";

    return 0;
}