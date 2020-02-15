#pragma 
#include "../RHI.hpp";
#include "Renderer_D3D11.hpp";

namespace Persist
{

class RHIVertexBufferD3D11 : public RHIVertexBuffer
{
    public :
    RHIVertexBufferD3D11(ID3D11Buffer * vb , uint32_t size, uint32_t usage) :
        vertexBuffer_(vb),RHIVertexBuffer(size, usage)
    {

    }
    private :

    ID3D11Buffer * vertexBuffer_;

};


}