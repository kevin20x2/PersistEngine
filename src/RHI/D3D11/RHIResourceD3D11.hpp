#pragma 
#include "../RHI.hpp"
#include "Renderer_D3D11.hpp"

namespace Persist
{

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

        ID3D11DeviceContext * context  = Renderer_D3D11::instance->getDeviceContext(); 
        context->Map( vertexBuffer_ ,NULL ,D3D11_MAP_WRITE_DISCARD ,NULL , &ms );
        memcpy(ms.pData , value,  size);
        context->Unmap(vertexBuffer_ , NULL);


    };

    RHIRefPtr < ID3D11Buffer>  vertexBuffer()  {return vertexBuffer_;}

    private :

    RHIRefPtr <ID3D11Buffer>  vertexBuffer_;

};

class RHIVertexDataArrayD3D11 : public IRHIResourceArray
{
public:
    RHIVertexDataArrayD3D11(void * src , uint32_t size ) :
    array_(src),size_(size)
    {

    }
    void * getArray() override { return array_;}   
    uint32_t getArraySize() override {return size_ ;}
    
private : 
    void * array_ ;
    uint32_t size_ ;
};



}