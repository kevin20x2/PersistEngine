#include "FbxImporter.hpp"
#include <FrameWork/Components/StaticMeshComponent.hpp>
#include <FrameWork/Geometry/Mesh.hpp>
#include <fbxsdk.h>
namespace Persist
{


    static void HandleMesh (fbxsdk :: FbxMesh * fbxMesh, SceneUnit * unit)
    {
        StaticMeshComponent * meshComp = unit->addComponent<StaticMeshComponent>();
        Mesh * mesh = new Mesh();

        fbxsdk::FbxVector4* controlPoints =  fbxMesh->GetControlPoints();
        int controlPointCount = fbxMesh->GetControlPointsCount();
        int triangleCount = fbxMesh->GetPolygonCount();
        int vertexCounter = 0 ;
        Array <Vector3f> * vertices = new Array <Vector3f>();
        Array <int> * triangles = new Array <int>();

        for(int i = 0 ; i < controlPointCount ; ++i)
        {
            vertices->push_back(Vector3f(controlPoints[i][0],controlPoints[i][1],controlPoints[i][2]));
        }

        for(int i = 0 ; i < triangleCount ; ++ i)
        {
            for (int j = 0 ; j < 3 ; ++j)
            {
                int ctrlPointIndex = fbxMesh->GetPolygonVertex(i , j );
                triangles->push_back(ctrlPointIndex);
                fbxsdk::FbxVector4 ctrlPoint = controlPoints[ctrlPointIndex];
            }

        }



        /*
        std::cout << "Control Point Count " << controlPointCount  << std::endl;
        for(int i = 0 ; i < controlPointCount ; ++ i)
        {
            std::cout << "<point " << i << " : "
             << controlPoints[i][0] << " , "
             << controlPoints[i][1] << " , "
             << controlPoints[i][2] << " , "
             << controlPoints[i][3] << " > " << std::endl;

        }
        */


    }

    static void HandleNodeAttribute(fbxsdk :: FbxNode  * node, SceneUnit * unit)
    {
        int attributeCount = node->GetNodeAttributeCount();
        for(int i = 0 ; i < attributeCount ; ++i)
        {
            fbxsdk::FbxNodeAttribute *  attri = node->GetNodeAttributeByIndex(i);
            if(attri != nullptr)
            {
                fbxsdk::FbxNodeAttribute::EType type = attri->GetAttributeType();
                switch (type)
                {
                case fbxsdk::FbxNodeAttribute::eMesh:
                    fbxsdk::FbxMesh * mesh = static_cast <fbxsdk :: FbxMesh * > (attri);
                    if(mesh != nullptr)
                    {
                        std::cout << "getMeshName" << mesh->GetName() <<std::endl;
                        HandleMesh(mesh , unit);
                    }
                    break;
                }

            }
        }



    }

    static void traverseNode( fbxsdk::FbxNode * node , SceneUnit * unit)
    {
        if(node != nullptr)
        {
            HandleNodeAttribute(node ,unit );
        }
        int len = node->GetChildCount();
        for(int i = 0 ; i < len ; ++ i)
        {
            SceneUnit * childUnit = unit->addChild(new SceneUnit());
            fbxsdk::FbxNode * child = node->GetChild(i);
            if(child != nullptr)
            {
                std::cout << "child Name :" << child->GetName() << std::endl;
                traverseNode(child,childUnit);
            }
        }
    }


    SceneUnit * FbxImporter::loadFromDisk(const String & path)
    {
        fbxsdk::FbxManager * lSdkManager = fbxsdk::FbxManager::Create();
        fbxsdk::FbxIOSettings * ios = fbxsdk::FbxIOSettings ::Create(lSdkManager , IOSROOT);
        lSdkManager->SetIOSettings(ios);

        fbxsdk::FbxImporter * lImporter = fbxsdk::FbxImporter::Create(lSdkManager ,"");

        if(!lImporter->Initialize(path.c_str(), -1,lSdkManager->GetIOSettings()))
        {
            std::cout << "FbxImport ::Initialize Failed" << std::endl;

        }
        fbxsdk::FbxScene * lScene = fbxsdk ::FbxScene::Create(lSdkManager , "myScene");

        lImporter->Import(lScene);

        fbxsdk::FbxNode * root = lScene->GetRootNode();

        SceneUnit * res = new SceneUnit();

        traverseNode(root,res);

        lImporter->Destroy();

        return res;

    }


}