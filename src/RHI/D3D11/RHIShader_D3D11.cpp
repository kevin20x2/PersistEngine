#include "Renderer_D3D11.hpp"
#include "GpuProgram_D3D11.hpp"
namespace Persist
{

Status Renderer_D3D11 ::createVertexShader(GpuProgram & program)
{
    if(program.type() != program.PT_Vertex)
    {
        return Status::Error("Renderer_D3D11:: CreateVertexShader: program Type error");
    }
    GpuProgram_D3D11 & pro  =  dynamic_cast <GpuProgram_D3D11&>(program);
    HRESULT hr = pDev_->CreateVertexShader(pro.buffer_.data(), pro.buffer_size_, NULL ,  pro.vertexShader_.initRef());

    if(!FAILED(hr))
    {
        return Status::Ok();
    }
    else 
    {
        return Status::Error("Renderer_D3D11 :: createVertexShader error");

    }
}

Status Renderer_D3D11 :: createPixelShader(GpuProgram & program)
{
    if(program.type() != program.PT_Pixel)
    {
        return Status::Error("Renderer_D3D11::createPixelShader : program type error");
    }
    GpuProgram_D3D11 & pro = dynamic_cast <GpuProgram_D3D11 &>(program);
    HRESULT hr = pDev_->CreatePixelShader(pro.buffer_.data() , pro.buffer_size_ ,NULL, pro.pixelShader_.initRef());
    if(!FAILED(hr))
    {
        return Status::Ok();
    }
    else 
    {
        return Status::Error("Renderer_D3D11 :: createPixelShader error");
    }

}


}