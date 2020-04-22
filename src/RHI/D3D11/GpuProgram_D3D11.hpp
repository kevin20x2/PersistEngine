#pragma once
#include <RHI/RHIGpuProgram.hpp>
#include <FrameWork/Common/Array.hpp>
#include "../RHIResource.hpp"
#include <d3d11.h>


namespace Persist
{
    class GpuProgram_D3D11 : public RHIGpuProgram 
    {
        public :
            static GpuProgram_D3D11 * createFromSerializedProgram
            (const SerializedGpuProgram & program ,RHIGpuProgram::ProgramType type =RHIGpuProgram::PT_Vertex);
            Array<uint8_t> buffer_;
            uint32_t buffer_size_;
            RHIRefPtr <ID3D11VertexShader> vertexShader_;
            RHIRefPtr <ID3D11PixelShader> pixelShader_;
            //RHIRefPtr <ID3D11InputLayout> layout_;
    };


}