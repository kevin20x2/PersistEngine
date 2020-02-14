#pragma once 
#include <FrameWork/Interface/IRunTimeModule.hpp>
#include <cstdint>

namespace Persist 
{

    class IRenderer : extends IRunTimeModule
    {
        public :
        virtual int init() = 0 ;
        virtual void destroy() = 0;
        virtual void tick() = 0 ;

        virtual void beginFrame() = 0;

        virtual void render() = 0 ;

        virtual void endFrame() = 0;

        virtual void resize(uint32_t width , uint32_t height) = 0;


    };


}
