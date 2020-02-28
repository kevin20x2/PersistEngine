#include "RHIContext_D3D11.hpp"
namespace Persist
{
    class RHIConstantBufferD3D11 : public RHIConstantBuffer
    {
        public :
        RHIConstantBufferD3D11(ID3D11Buffer * cb , uint32_t size , uint32_t usage):
            constantBuffer_(cb) , RHIConstantBuffer(size, usage)
        {

        }
        RHIRefPtr <ID3D11Buffer> constantBuffer() {return constantBuffer_ ;}
        private : 
        RHIRefPtr <ID3D11Buffer> constantBuffer_;


    };

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

}