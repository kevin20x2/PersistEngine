#pragma once
#include <FrameWork/Renderer/Renderer.hpp>

namespace  Persist{
    
    class Renderer_Empty : extends IRenderer
    {
        public : 
        ~Renderer_Empty() {}
        
        int init() {return 0;}
        void destroy() {}

        void render() {}

        void beginFrame() {}

        void endFrame() {}

        void resize (uint32_t width , uint32_t height) {}



    };




}