#include "Renderer_D3D11.hpp"
namespace Persist
{
    int Renderer_D3D11 :: setVertexBuffer(uint32_t size , void * src ,RHIVertexBuffer & dst )
    {
        dst.setValue(size, src);
    }

}

