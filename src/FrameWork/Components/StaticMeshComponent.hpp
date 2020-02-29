#pragma once
#include "BaseComponent.hpp"
#include <FrameWork/Geometry/Mesh.hpp>

namespace Persist
{
    class StaticMeshComponent : public BaseComponent
    {
        public : 
        StaticMeshComponent(Unit * unit = nullptr) : 
            BaseComponent(unit) ,
            mesh_(nullptr)
            {
                
            }
        void setMesh(Mesh * mesh ) { mesh_ = mesh;}

        protected:
            Mesh *mesh_;

    };

}

