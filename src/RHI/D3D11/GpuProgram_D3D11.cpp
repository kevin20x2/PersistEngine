#include "GpuProgram_D3D11.hpp"
#include <FrameWork/Shaders/SerializeShaderData.hpp>
namespace Persist
{

   RHIGpuProgram *RHIGpuProgram ::createFromSerializedProgram(const SerializedGpuProgram & program ,RHIGpuProgram::ProgramType type)
    {
        return GpuProgram_D3D11 :: createFromSerializedProgram(program , type);

    }


    GpuProgram_D3D11 * GpuProgram_D3D11 :: createFromSerializedProgram
    (const SerializedGpuProgram & program ,RHIGpuProgram::ProgramType type)
    {
        GpuProgram_D3D11 * ans = new GpuProgram_D3D11();
        ans->type_ = type;
        ans->buffer_ =   program.buffer_ ;
        ans->buffer_size_ = program.buffer_.size();
        return ans;
    }


}