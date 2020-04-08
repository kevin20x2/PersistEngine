#pragma once
#include "BaseComponent.hpp"
#include <FrameWork/Geometry/Mesh.hpp>

namespace Persist
{
    class Mesh;
    PERSIST_OBJECT()
    class StaticMeshComponent : public BaseComponent
    {

        public : 
        REGISTER_CLASS(StaticMeshComponent);
        StaticMeshComponent(Unit * unit = nullptr) : 
            BaseComponent(unit) ,
            mesh_(nullptr)
            {
                
            }
        void setMesh(Mesh * mesh ) { mesh_ = mesh;}
        Mesh * mesh() { return mesh_;}

        protected:
            Mesh *mesh_;

    };

}

