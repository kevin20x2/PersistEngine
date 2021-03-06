#pragma once 
#include <FrameWork/Interface/IRunTimeModule.hpp>
#include <cstdint>
#include <RHI/RHI.hpp>
#include <FrameWork/Math/Vectors.hpp>

namespace Persist 
{

    class IRHIContext : extends IRunTimeModule
    {
        public :

        static IRHIContext * RHIContext();


        public :

        // from runtime module
        virtual ~IRHIContext() {}
        virtual Status init() override = 0 ;
        virtual void destroy() override = 0;
        virtual void tick() override {} ;

        // default 

        virtual void beginFrame() = 0;

        virtual void render() = 0 ;

        virtual void endFrame() = 0;

        virtual void resize(uint32_t width , uint32_t height) = 0;

        virtual RHIVertexBufferPtr createVertexBuffer(uint32_t size , uint32_t usage , RHIResourceCreateInfo & info) = 0;
        virtual RHIIndexBufferPtr createIndexBuffer(uint32_t size , uint32_t usage , RHIResourceCreateInfo & info) = 0 ;
        virtual RHIConstantBufferPtr createConstantBuffer(uint32_t size , uint32_t usage , RHIResourceCreateInfo & info) = 0 ;
        virtual Status setConstantBufferValue(RHIConstantBufferPtr buffer , IRHIResourceArray *  data  ) = 0 ;


        virtual RHIDepthStencilStatePtr createDepthStencilState(const RHIDepthStencilStateInitializer & init ) = 0 ;
        virtual Status setDepthStencilState(RHIDepthStencilState * state) = 0 ;
        


        virtual RHIVertexLayoutPtr createVertexLayout(RHIVertexFormatElementList & elementList ) = 0 ;  
        virtual RHIVertexLayoutPtr createVertexLayout(RHIVertexFormatElementList & elementList , RHIGpuProgram & vs ) = 0 ;  


        virtual Status createVertexShader(RHIGpuProgram & program) = 0;
        virtual Status createPixelShader(RHIGpuProgram & program) = 0;

        virtual Status setVertexShader(RHIGpuProgram & program) = 0 ;
        virtual Status setPixelShader(RHIGpuProgram & program ) = 0 ;
        virtual Status setVertexLayout(RHIVertexLayoutPtr &layout) = 0 ;
        
        virtual Status setVertexBuffer(RHIVertexBufferPtr buffer , RHIVertexLayoutPtr layout) = 0;
        virtual Status setIndexBuffer(RHIIndexBufferPtr buffer) = 0;
        virtual Status setConstantBuffer(RHIConstantBufferPtr buffer) = 0 ;


        virtual void setViewPort(uint32_t topLeftX , uint32_t topLeftY , uint32_t width , uint32_t height) = 0;
        virtual void clearRenderTargetView(const Vector4f & color) = 0;

        virtual void drawTriangleList(uint32_t vertexCount , uint32_t startPoint) = 0 ;
        virtual void drawTriangleListRip(uint32_t indexCount ,uint32_t  startPoint, uint32_t vertexOffset) = 0;

        



        


    };


}
