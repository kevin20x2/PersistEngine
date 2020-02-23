#include "Renderer_D3D11.hpp"
#include "RHIResourceD3D11.hpp"
#include "../RHI.hpp"
//#include "../RHIResource.hpp"
namespace Persist
{

  RHIVertexBufferPtr  Renderer_D3D11 :: createVertexBuffer(uint32_t size , uint32_t usage , RHIResourceCreateInfo & info) 
    {
        D3D11_BUFFER_DESC bd;
        ZeroMemory(&bd ,sizeof(bd));
        bd .Usage = (usage & Buf_Dynamic) ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_DEFAULT;
        bd.ByteWidth = size;
        bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        bd.CPUAccessFlags = (usage & Buf_Dynamic) ? D3D11_CPU_ACCESS_WRITE : 0;
        bd.MiscFlags = 0;

        D3D11_SUBRESOURCE_DATA initData;
        D3D11_SUBRESOURCE_DATA * pinitData = nullptr;
        if(info.resourceArray())
        {
            initData.pSysMem = info.resourceArray()->getArray();
            initData.SysMemPitch = 0 ; 
            initData.SysMemSlicePitch = 0;
            pinitData = & initData;
        }

        RHIRefPtr <ID3D11Buffer> vertexBuffer;
        HRESULT hr = pDev_->CreateBuffer( &bd ,pinitData , vertexBuffer.initRef());
        if (FAILED(hr))
        {

        }
        return  new RHIVertexBufferD3D11(vertexBuffer, size, usage);

    }
    int Renderer_D3D11 :: setVertexBuffer(uint32_t size , void * src ,RHIVertexBuffer & dst )
    {
        //dst.setValue(size, src);
        return 0;
    }

}

