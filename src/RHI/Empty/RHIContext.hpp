#pragma once
#include <FrameWork/RHIContext/RHIContext.hpp>

namespace  Persist{
    
    class RHIContext_Empty : extends IRHIContext
    {
        public : 
        ~RHIContext_Empty() {}
        
        int init() {return 0;}
        void destroy() {}

        void render() {}

        void beginFrame() {}

        void endFrame() {}

        void resize (uint32_t width , uint32_t height) {}



    };




}