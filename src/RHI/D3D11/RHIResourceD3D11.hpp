#pragma 
#include "../RHI.hpp"
#include "RHIContext_D3D11.hpp"

namespace Persist
{

class RHIIndexBufferD3D11 : public RHIIndexBuffer
{
    public : 
    RHIIndexBufferD3D11(ID3D11Buffer * ib , uint32_t size , uint32_t usage) :
        indexBuffer_(ib ) , RHIIndexBuffer(size, usage)
    {

    }
    RHIRefPtr <ID3D11Buffer> indexBuffer() {return indexBuffer_;}
    private:
    RHIRefPtr <ID3D11Buffer> indexBuffer_;



};

class RHIVertexBufferD3D11 : public RHIVertexBuffer
{
    public :
    RHIVertexBufferD3D11(ID3D11Buffer *  vb , uint32_t size, uint32_t usage) :
        vertexBuffer_( vb),RHIVertexBuffer(size, usage)
    {

    }
    int setValue(uint32_t size , const void * value ) 
    {
        D3D11_MAPPED_SUBRESOURCE ms;
        //ms.pData = new uint8_t [size];

        ID3D11DeviceContext * context  = RHIContext_D3D11::instance->getDeviceContext(); 
        context->Map( vertexBuffer_ ,NULL ,D3D11_MAP_WRITE_DISCARD ,NULL , &ms );
        memcpy(ms.pData , value,  size);
        context->Unmap(vertexBuffer_ , NULL);


    };

    RHIRefPtr < ID3D11Buffer>  vertexBuffer()  {return vertexBuffer_;}

    private :

    RHIRefPtr <ID3D11Buffer>  vertexBuffer_;

};



class RHIBufferDataArrayD3D11 : public IRHIResourceArray
{
public:
    RHIBufferDataArrayD3D11(void * src , uint32_t size ) :
    array_(src),size_(size)
    {

    }
    void * getArray() override { return array_;}   
    uint32_t getArraySize() override {return size_ ;}
    
private : 
    void * array_ ;
    uint32_t size_ ;
};
class RHIConstantBufferD3D11 : public RHIConstantBuffer
{
public:
    RHIConstantBufferD3D11(ID3D11Buffer *cb, uint32_t size, uint32_t usage) : constantBuffer_(cb), RHIConstantBuffer(size, usage)
    {
    }
    RHIRefPtr<ID3D11Buffer> constantBuffer() { return constantBuffer_; }

private:
    RHIRefPtr<ID3D11Buffer> constantBuffer_;
};
}