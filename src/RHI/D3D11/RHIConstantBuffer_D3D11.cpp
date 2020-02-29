#include "RHIContext_D3D11.hpp"
#include "RHIResourceD3D11.hpp"
namespace Persist
{
    

RHIConstantBufferPtr RHIContext_D3D11::createConstantBuffer(uint32_t size ,uint32_t usage , RHIResourceCreateInfo & info)
{
    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd , sizeof(bd));
    bd.Usage = (usage & Buf_Dynamic) ? D3D11_USAGE_DYNAMIC :D3D11_USAGE_DEFAULT;
    bd.ByteWidth = size ;
    bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    bd.CPUAccessFlags = (usage & Buf_Dynamic) ? D3D11_CPU_ACCESS_WRITE :0;
    bd.MiscFlags = 0 ;
    
    D3D11_SUBRESOURCE_DATA initData;
    D3D11_SUBRESOURCE_DATA * pinitData = nullptr;
    if(info.resourceArray())
    {
        initData.pSysMem = info.resourceArray()->getArray();
        initData.SysMemPitch = 0;
        initData.SysMemSlicePitch = 0 ;
        pinitData = & initData;
    }
    RHIRefPtr <ID3D11Buffer> constantBuffer;
    HRESULT hr = pDev_->CreateBuffer(&bd, pinitData ,constantBuffer.initRef());
    if(FAILED(hr))
    {
        
    }
    return new RHIConstantBufferD3D11(constantBuffer,size, usage);


}

Status RHIContext_D3D11 :: setConstantBuffer( RHIConstantBufferPtr buffer , IRHIResourceArray * data  )
{
    //RHIBufferDataArrayD3D11 * data_ptr = dynamic_cast <RHIBufferDataArrayD3D11 * > (data);

    RHIConstantBufferD3D11 * buffer_ptr = dynamic_cast <RHIConstantBufferD3D11 *>(buffer.get());
    D3D11_MAPPED_SUBRESOURCE mappedResource;
    HRESULT hr = pDevContext_->Map(buffer_ptr->constantBuffer(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

    if(FAILED(hr))
    {
        return Status::Error("set Constant buffer error");
    }
    memcpy (mappedResource.pData ,data->getArray(), data->getArraySize()) ;

    pDevContext_->Unmap(buffer_ptr->constantBuffer(), 0 );

    return Status::Ok();

}


}