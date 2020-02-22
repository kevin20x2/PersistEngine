#include "GpuProgram_D3D11.hpp"
#include <FrameWork/Shaders/SerializeShaderData.hpp>
namespace Persist
{

    GpuProgram_D3D11 * GpuProgram_D3D11 :: createFromSerializedProgram(const SerializedGpuProgram & program)
    {
        GpuProgram_D3D11 * ans = new GpuProgram_D3D11();
        ans->buffer_ =   program.buffer_ ;
        ans->buffer_size_ = program.buffer_.size();
        return ans;
    }


}