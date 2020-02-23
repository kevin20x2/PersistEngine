#pragma once
#include <FrameWork/Shaders/GpuProgram.hpp>
#include <FrameWork/Common/Array.hpp>
#include "../RHIResource.hpp"
#include <d3d11.h>


namespace Persist
{
    class GpuProgram_D3D11 : public GpuProgram 
    {
        public :
            static GpuProgram_D3D11 * createFromSerializedProgram
            (const SerializedGpuProgram & program ,GpuProgram::ProgramType type = GpuProgram::PT_Vertex);
            Array<uint8_t> buffer_;
            uint32_t buffer_size_;
            RHIRefPtr <ID3D11VertexShader> vertexShader_;
            RHIRefPtr <ID3D11PixelShader> pixelShader_;
    };


}