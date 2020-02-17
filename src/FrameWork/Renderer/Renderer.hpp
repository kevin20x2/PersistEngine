#pragma once 
#include <FrameWork/Interface/IRunTimeModule.hpp>
#include <cstdint>
#include <RHI/RHI.hpp>

namespace Persist 
{

    class IRenderer : extends IRunTimeModule
    {
        public :

        static IRenderer * renderer();


        public :

        // from runtime module
        virtual ~IRenderer() {}
        virtual int init() override = 0 ;
        virtual void destroy() override = 0;
        virtual void tick() override {} ;

        // default 

        virtual void beginFrame() = 0;

        virtual void render() = 0 ;

        virtual void endFrame() = 0;

        virtual void resize(uint32_t width , uint32_t height) = 0;

        virtual RHIVertexBufferPtr createVertexBuffer(uint32_t size , uint32_t usage , RHIResourceCreateInfo & info) = 0;

        virtual void setViewPort(uint32_t topLeftX , uint32_t topLeftY , uint32_t width , uint32_t height) = 0;

        



        


    };


}
