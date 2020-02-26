#include "Renderer_D3D11.hpp"
#include <FrameWork/Common/Status.hpp>
#include "RHIResourceD3D11.hpp"
namespace Persist
{

RHIIndexBufferPtr Renderer_D3D11::createIndexBuffer(uint32_t size , uint32_t usage,RHIResourceCreateInfo & info)
{
    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd , sizeof(bd));
    bd.Usage = (usage & Buf_Dynamic) ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_DEFAULT;
    bd.ByteWidth = size ;
    bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    bd.CPUAccessFlags = (usage & Buf_Dynamic) ? D3D11_CPU_ACCESS_WRITE : 0 ;
    bd.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA initData;
    D3D11_SUBRESOURCE_DATA * pinitData = nullptr;
    if(info.resourceArray())
    {
        initData.pSysMem = info.resourceArray()->getArray();
        initData.SysMemPitch = 0 ;
        initData.SysMemSlicePitch = 0 ;
        pinitData = & initData;
    }
    RHIRefPtr <ID3D11Buffer> indexBuffer;
    HRESULT hr = pDev_->CreateBuffer(&bd , pinitData , indexBuffer.initRef());
    if( FAILED(hr))
    {
        throw Status::Error("create index buffer error");
    }
    return new RHIIndexBufferD3D11(indexBuffer , size , usage);
}



}