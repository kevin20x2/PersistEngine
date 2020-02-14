#pragma once 
#include <FrameWork/Interface/IRunTimeModule.hpp>
#include <cstdint>

namespace Persist 
{

    class IRenderer : extends IRunTimeModule
    {
        public :

        static IRenderer * renderer();


        public :

        virtual ~IRenderer() {}
        virtual int init() override = 0 ;
        virtual void destroy() override = 0;
        

        // default 
        virtual void tick() override {} ;

        virtual void beginFrame() = 0;

        virtual void render() = 0 ;

        virtual void endFrame() = 0;

        virtual void resize(uint32_t width , uint32_t height) = 0;


    };


}
