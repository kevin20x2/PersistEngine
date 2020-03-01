#pragma once
#include "BaseRenderer.hpp"
#include "StaticMeshComponent.hpp"
#include <RHI/RHIResource.hpp>

namespace Persist
{
    class MeshRenderer : public IBaseRenderer
    {
        public : 
        MeshRenderer(Unit * unit = nullptr) :
            IBaseRenderer(unit)
        {
            meshComp_ = getComponent<StaticMeshComponent>();
        }
        // temp : 
        void initShader() ;
        void commitMesh();
        virtual void _commit() override ;
        protected :
        // TODO : remove here
        StaticMeshComponent * meshComp_;
        RHIVertexLayoutPtr layout_;

    };

}