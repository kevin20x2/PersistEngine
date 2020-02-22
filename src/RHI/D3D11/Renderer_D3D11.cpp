#include "Renderer_D3D11.hpp"
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXColors.h>
#include <iostream>
#include "RHIResourceD3D11.hpp"
#include "RHIVertexLayout_D3D11.hpp"
#include "GpuProgram_D3D11.hpp"
#include <FrameWork/Serialize/Serialize.hpp>
#include <FrameWork/Shaders/SerializeShaderData.hpp>

const int screen_width = 800;
const int screen_height = 600;

//ID3D11Buffer *g_buffer;

template <class T>
void safeRelease(T ** InterfaceToRelease)
{
    if(*InterfaceToRelease != nullptr)
    {
        //delete (*InterfaceToRelease);
        (*InterfaceToRelease)->Release();
        *InterfaceToRelease = nullptr;
    }


}

namespace Persist
{

    Renderer_D3D11* Renderer_D3D11 ::instance = nullptr;

    int Renderer_D3D11::init()
    {
        HRESULT hr = S_OK;
        if(pSwapchain_ == nullptr)
        {
            DXGI_SWAP_CHAIN_DESC scd;

            ZeroMemory(&scd ,sizeof(DXGI_SWAP_CHAIN_DESC));

            RECT rect ;

            GetWindowRect(hWnd_ , &rect);

            rtWidth_ = rect.right - rect.left;
            rtHeight_ = rect.bottom - rect.top;

            scd.BufferCount = 1;
            scd.BufferDesc.Width =  rtWidth_;
            scd.BufferDesc.Height = rtHeight_;
            scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
            //60fps 
            scd.BufferDesc.RefreshRate.Numerator = 60;
            scd.BufferDesc.RefreshRate.Denominator = 1;
            scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
            scd.OutputWindow = hWnd_;
            scd.SampleDesc.Count = 4;
            scd.Windowed = TRUE;
            scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;


            const D3D_FEATURE_LEVEL FeatureLevels[] = {
                //D3D_FEATURE_LEVEL_11_1,
                D3D_FEATURE_LEVEL_11_0,
                //D3D_FEATURE_LEVEL_10_1,
                //D3D_FEATURE_LEVEL_10_0,
                //D3D_FEATURE_LEVEL_9_3,
                //D3D_FEATURE_LEVEL_9_2,
                //D3D_FEATURE_LEVEL_9_1 
                };

            D3D_FEATURE_LEVEL FeatureLevelSupported;

            HRESULT hr = S_OK;

            hr = D3D11CreateDeviceAndSwapChain(NULL ,
                D3D_DRIVER_TYPE_HARDWARE,
                NULL,
                0,
                FeatureLevels,
                _countof(FeatureLevels),
                D3D11_SDK_VERSION,
                &scd,
                &pSwapchain_,
                &pDev_,
                &FeatureLevelSupported,
                &pDevContext_);
            
            if ( hr == E_INVALIDARG)
            {
                hr = D3D11CreateDeviceAndSwapChain(NULL,
                                                   D3D_DRIVER_TYPE_HARDWARE,
                                                   NULL,
                                                   0,
                                                   &FeatureLevelSupported,
                                                   1,
                                                   D3D11_SDK_VERSION,
                                                   &scd,
                                                   &pSwapchain_,
                                                   &pDev_,
                                                   NULL,
                                                   &pDevContext_);
            }

            if(hr == S_OK)
            {
                createRenderTarget();
                setViewPort();
                initPipeline();
                initGraphics();

            }
            return hr;

        }



    }
    void Renderer_D3D11::createRenderTarget()
    {
        HRESULT hr;
        ID3D11Texture2D * pBackBuffer ;

        pSwapchain_->GetBuffer(0 , __uuidof(ID3D11Texture2D) ,
                    (LPVOID*) & pBackBuffer
        );
        pDev_->CreateRenderTargetView(pBackBuffer ,NULL , &pRTView_);

        pBackBuffer->Release();

        pDevContext_->OMSetRenderTargets(1, & pRTView_, NULL);
    }
    void Renderer_D3D11::setViewPort()
    {
        D3D11_VIEWPORT viewport;
        ZeroMemory(&viewport , sizeof(D3D11_VIEWPORT));


        viewport.TopLeftX = 0;
        viewport.TopLeftY = 0;
        viewport.Width =  rtWidth_;
        viewport.Height = rtHeight_;
        pDevContext_->RSSetViewports(1, & viewport);
    }
    void Renderer_D3D11 ::initPipeline()
    {
        SerializedGpuProgram program;
        TransferContext::addReadRequest("copy.vso", program);
        GpuProgram_D3D11 * pro = GpuProgram_D3D11::createFromSerializedProgram(program);

        ID3DBlob * VS , *PS;

        D3DCreateBlob(pro->buffer_size_,&VS);
        memcpy(VS->GetBufferPointer(),pro->buffer_.data(),pro->buffer_size_);

    
        //D3DReadFileToBlob(L"copy.vso" , &VS);
        D3DReadFileToBlob(L"copy.pso" , & PS);
        pDev_->CreateVertexShader(VS->GetBufferPointer() , VS->GetBufferSize(),
        NULL , &vs_) ;
        pDev_->CreatePixelShader(PS->GetBufferPointer() , PS->GetBufferSize(),
        NULL, &ps_);

        pDevContext_->VSSetShader(vs_ ,0,0);
        pDevContext_->PSSetShader(ps_,0,0);

        RHIVertexFormatElementList elementList = 
         { { VUT_POSITION ,VFT_Float3 ,  16},
            { VUT_COLOR , VFT_Float3 , 16} };
       layout_ = createVertexLayout(elementList);
       RHIVertexLayout_D3D11 * layout_D3d11 = dynamic_cast<RHIVertexLayout_D3D11*>(layout_.get());


        pDev_->CreateInputLayout(layout_D3d11->layout_D3D11(), 2, VS->GetBufferPointer(), VS->GetBufferSize(),&pLayout_);
        //pDev_->CreateInputLayout(ied, 2, VS->GetBufferPointer(), VS->GetBufferSize(),&pLayout_);
        pDevContext_->IASetInputLayout(pLayout_);
        VS->Release();
        PS->Release();

    }
   
    RHIVertexBufferPtr  buffer = nullptr ;
    void Renderer_D3D11::initGraphics()
    {
        float Vertices[] =
            {
                0.0f, 0.5f, 0.0f,
                1.0f, 0.0f, 0.0f, 1.0f,

                0.45f, -0.5f, 0.0f,
                0.0f, 1.0f, 0.0f, 1.0f,
                -0.45f, -0.5f, 0.0f,
                0.0f, 0.0f, 1.0f, 1.0f};
        uint32_t size = sizeof(float) * 7 *3;
        RHIVertexDataArrayD3D11 *verticeData = new RHIVertexDataArrayD3D11(Vertices ,size);

        RHIResourceCreateInfo info(verticeData);
        buffer =  createVertexBuffer(size, Buf_Dynamic , info);

        //buffer->AddRef();
        //setVertexBuffer(size , Vertices , *buffer );
        //D3D11_BUFFER_DESC bd ;
        //ZeroMemory(&bd ,sizeof(bd));


        //bd.Usage = D3D11_USAGE_DYNAMIC;
        // 3 vertex  , 7float each
        //bd.ByteWidth = sizeof(float)*7 * 3;
        //bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        //bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

        //pDev_->CreateBuffer(&bd ,NULL, &pVBuffer);

        //D3D11_MAPPED_SUBRESOURCE ms;
        //pDevContext_->Map(pVBuffer,NULL,D3D11_MAP_WRITE_DISCARD , NULL , &ms);
        //memcpy(ms.pData , Vertices ,sizeof(float)*3 *7);
        //pDevContext_->Unmap(pVBuffer ,NULL);

    }

    void Renderer_D3D11::render()
    {
        RHIVertexBuffer * ptr = buffer;

        RHIRefPtr <ID3D11Buffer>  vb = dynamic_cast<RHIVertexBufferD3D11*>(ptr)->vertexBuffer();
        const FLOAT clearColor [] = {0.0f, 0.2f,0.4f ,1.0f};
        pDevContext_->ClearRenderTargetView(pRTView_,clearColor);
        pVBuffer_ = vb ;

        {
            UINT stride = sizeof(float ) * 7;
            UINT offset = 0 ;
            pDevContext_->IASetVertexBuffers(0,1,&pVBuffer_,&stride , &offset);

            pDevContext_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

            pDevContext_->Draw(3,0);

        }
        pSwapchain_->Present(0,0);

    }
    void Renderer_D3D11::beginFrame()
    {

    }
    void Renderer_D3D11::endFrame()
    {
        
    }
    void Renderer_D3D11::destroy()
    {
        //safeRelease(&pLayout_);
        safeRelease(&pRTView_);
        safeRelease(&pSwapchain_);
        safeRelease(&vs_);
        safeRelease(&ps_);
        safeRelease(&pVBuffer_);
        safeRelease(& pDev_);
        safeRelease( &pDevContext_);

    }
    void Renderer_D3D11::resize(uint32_t width , uint32_t height)
    {
        //std::cout <<  width << height << std::endl;
        rtWidth_ = width;
        rtHeight_ = height;
        pSwapchain_->ResizeBuffers(0,width ,height,DXGI_FORMAT_UNKNOWN , DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH);
        createRenderTarget();
        //setViewPort();

    }
    void Renderer_D3D11::setViewPort(uint32_t topLeftX , uint32_t topLeftY , uint32_t width, uint32_t height)
    {
        D3D11_VIEWPORT viewport;
        ZeroMemory(&viewport , sizeof(D3D11_VIEWPORT));
        viewport.TopLeftX = topLeftX;
        viewport.TopLeftY = topLeftY;
        viewport.Width =  width;
        viewport.Height = height;
        pDevContext_->RSSetViewports(1, & viewport);
    }
    RHIVertexLayoutPtr Renderer_D3D11::createVertexLayout(RHIVertexFormatElementList & elementList) 
    {
        return new  RHIVertexLayout_D3D11(elementList);
    }

  


}