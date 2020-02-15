#include "Renderer_D3D11.hpp"
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXColors.h>
#include <iostream>
#include "RHIResourceD3D11.hpp"

const int screen_width = 800;
const int screen_height = 600;


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
        ID3DBlob * VS , *PS;
    
        D3DReadFileToBlob(L"copy.vso" , &VS);
        D3DReadFileToBlob(L"copy.pso" , & PS);
        pDev_->CreateVertexShader(VS->GetBufferPointer() , VS->GetBufferSize(),
        NULL , &vs_) ;
        pDev_->CreatePixelShader(PS->GetBufferPointer() , PS->GetBufferSize(),
        NULL, &ps_);

        pDevContext_->VSSetShader(vs_ ,0,0);
        pDevContext_->PSSetShader(ps_,0,0);

        D3D11_INPUT_ELEMENT_DESC ied[] =
        {
            {"POSITION" , 0 , DXGI_FORMAT_R32G32B32_FLOAT , 0, 0 , D3D11_INPUT_PER_VERTEX_DATA,0},
            {"COLOR" , 0 , DXGI_FORMAT_R32G32B32_FLOAT , 0, 0 , D3D11_INPUT_PER_VERTEX_DATA,0}
        };

        pDev_->CreateInputLayout(ied , 2, VS->GetBufferPointer(), VS->GetBufferSize(),&pLayout_);
        pDevContext_->IASetInputLayout(pLayout_);
        VS->Release();
        PS->Release();

    }
    void Renderer_D3D11::initGraphics()
    {
        float Vertices[]=
        {
            0.0f , 0.5f , 0.0f ,
            1.0f , 0.0f,0.0f,1.0f,

            0.45f,-0.5f,0.0f ,
            0.0f,1.0f,0.0f,1.0f,
            -0.45f,-0.5f,0.0f, 
            0.0f,0.0f,1.0f,1.0f
        };
        D3D11_BUFFER_DESC bd ;
        ZeroMemory(&bd ,sizeof(bd));


        bd.Usage = D3D11_USAGE_DYNAMIC;
        // 3 vertex  , 7float each
        bd.ByteWidth = sizeof(float)*7 * 3;
        bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

        pDev_->CreateBuffer(&bd ,NULL, &pVBuffer);

        D3D11_MAPPED_SUBRESOURCE ms;
        pDevContext_->Map(pVBuffer,NULL,D3D11_MAP_WRITE_DISCARD , NULL , &ms);
        memcpy(ms.pData , Vertices ,sizeof(float)*3 *7);
        pDevContext_->Unmap(pVBuffer ,NULL);

    }

    void Renderer_D3D11::render()
    {
        const FLOAT clearColor [] = {0.0f, 0.2f,0.4f ,1.0f};
        pDevContext_->ClearRenderTargetView(pRTView_,clearColor);

        {
            UINT stride = sizeof(float ) * 7;
            UINT offset = 0 ;
            pDevContext_->IASetVertexBuffers(0,1,&pVBuffer,&stride , &offset);

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
        safeRelease(&pLayout_);
        safeRelease(&pRTView_);
        safeRelease(&pSwapchain_);
        safeRelease(&vs_);
        safeRelease(&ps_);
        safeRelease(&pVBuffer);
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

    RHIVertexBufferPtr Renderer_D3D11 :: createVertexBuffer(uint32_t size , uint32_t usage , RHIResourceCreateInfo & info) 
    {
        D3D11_BUFFER_DESC bd;
        ZeroMemory(&bd ,sizeof(bd));
        bd .Usage = (usage & Buf_Dynamic) ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_DEFAULT;
        bd.ByteWidth = size;
        bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        bd.CPUAccessFlags = (usage & Buf_Dynamic) ? D3D11_CPU_ACCESS_WRITE : 0;

        D3D11_SUBRESOURCE_DATA initData;
        D3D11_SUBRESOURCE_DATA * pinitData = nullptr;

        RHIRefPtr <ID3D11Buffer> vertexBuffer;
        HRESULT hr = pDev_->CreateBuffer( &bd ,pinitData , vertexBuffer.initRef());


        if(FAILED(hr))
        {

        }
        return  new RHIVertexBufferD3D11(vertexBuffer, size, usage);

    }


}