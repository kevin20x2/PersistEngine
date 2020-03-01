#include "GpuProgram_D3D11.hpp"
#include <FrameWork/Shaders/SerializeShaderData.hpp>
namespace Persist
{

    GpuProgram * GpuProgram ::createFromSerializedProgram(const SerializedGpuProgram & program , GpuProgram::ProgramType type)
    {
        return GpuProgram_D3D11 :: createFromSerializedProgram(program , type);

    }


    GpuProgram_D3D11 * GpuProgram_D3D11 :: createFromSerializedProgram
    (const SerializedGpuProgram & program , GpuProgram::ProgramType type)
    {
        GpuProgram_D3D11 * ans = new GpuProgram_D3D11();
        ans->type_ = type;
        ans->buffer_ =   program.buffer_ ;
        ans->buffer_size_ = program.buffer_.size();
        return ans;
    }


}