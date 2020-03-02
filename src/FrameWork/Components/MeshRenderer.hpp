#pragma once
#include "BaseRenderer.hpp"
#include "StaticMeshComponent.hpp"
#include <RHI/RHIResource.hpp>

namespace Persist
{
    class GpuProgram;
    class MeshRenderer : public IBaseRenderer
    {
        public : 
        MeshRenderer(Unit * unit = nullptr) :
            IBaseRenderer(unit)
        {
            if(unit != nullptr)
            {
                meshComp_ = getComponent<StaticMeshComponent>();
            }
        }
        // temp : 
        void initShader() ;
        void commitMesh();
        void commitConstant();
        virtual void _commit() override ;
        protected :
        // TODO : remove here
        StaticMeshComponent * meshComp_;
        RHIVertexLayoutPtr layout_ = nullptr;
        RHIVertexBufferPtr vertexBuffer_ = nullptr;
        RHIIndexBufferPtr indexBuffer_ = nullptr;
        RHIConstantBufferPtr constant_buffer_ = nullptr;

        RHIDepthStencilStatePtr depthState_ = nullptr;

        GpuProgram * vs_ = nullptr;
        GpuProgram * ps_ = nullptr;

        bool inited_ = false;

    };

}