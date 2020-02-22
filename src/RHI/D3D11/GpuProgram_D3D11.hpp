#pragma once
#include <FrameWork/Shaders/GpuProgram.hpp>
#include <FrameWork/Common/Array.hpp>


namespace Persist
{
    class GpuProgram_D3D11 : public GpuProgram 
    {
        public :
            static GpuProgram_D3D11 * createFromSerializedProgram(const SerializedGpuProgram & program);
            Array<uint8_t> buffer_;
            uint32_t buffer_size_;
    };


}