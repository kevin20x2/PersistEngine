#include "RHIContext_D3D11.hpp"
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXColors.h>
#include <iostream>
#include "RHIResourceD3D11.hpp"
#include "RHIVertexLayout_D3D11.hpp"
#include "GpuProgram_D3D11.hpp"
#include <FrameWork/Serialize/Serialize.hpp>
#include <FrameWork/Shaders/SerializeShaderData.hpp>
#include <FrameWork/RHIContext/RHIContext.hpp>



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
    IRHIContext *IRHIContext ::RHIContext()
    {
        static RHIContext_D3D11 s_local;
        return &s_local;
    }



    RHIContext_D3D11* RHIContext_D3D11 ::instance = nullptr;

    Status RHIContext_D3D11::init()
    {
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
                //initPipeline();
                //initGraphics();

            }
            return Status::Ok();

        }
        return Status::Error("Init Error");
    }
    void RHIContext_D3D11::createRenderTarget()
    {
        //HRESULT hr;
        ID3D11Texture2D * pBackBuffer ;

        pSwapchain_->GetBuffer(0 , __uuidof(ID3D11Texture2D) ,
                    (LPVOID*) & pBackBuffer
        );
        pDev_->CreateRenderTargetView(pBackBuffer ,NULL , &pRTView_);

        pBackBuffer->Release();

        pDevContext_->OMSetRenderTargets(1, & pRTView_, NULL);
    }
    void RHIContext_D3D11::setViewPort()
    {
        D3D11_VIEWPORT viewport;
        ZeroMemory(&viewport , sizeof(D3D11_VIEWPORT));


        viewport.TopLeftX = 0;
        viewport.TopLeftY = 0;
        viewport.Width =  rtWidth_;
        viewport.Height = rtHeight_;
        pDevContext_->RSSetViewports(1, & viewport);
    }
    void RHIContext_D3D11 ::initPipeline()
    {
        SerializedGpuProgram program;
        SerializedGpuProgram ps_program;
        TransferContext::addReadRequest("copy.vso", program);
        TransferContext::addReadRequest("copy.pso" , ps_program);
        GpuProgram_D3D11 * pro = GpuProgram_D3D11::createFromSerializedProgram(program);
        GpuProgram_D3D11 * ps_pro = GpuProgram_D3D11::createFromSerializedProgram(ps_program , GpuProgram::PT_Pixel);

        //ID3DBlob * VS , *PS ; 
        //ID3DBlob * VS2;

    
        createVertexShader(* pro);
        createPixelShader(*ps_pro);

      


//        D3DReadFileToBlob(L"copy.pso" , & PS);

        //pDev_->CreateVertexShader(VS2->GetBufferPointer() , VS2->GetBufferSize(),
        //NULL , &vs_) ;
        //pDev_->CreatePixelShader(PS->GetBufferPointer() , PS->GetBufferSize(),
        //NULL, &ps_);

        pDevContext_->VSSetShader(pro->vertexShader_ ,0,0);
        pDevContext_->PSSetShader(ps_pro->pixelShader_,0,0);

        RHIVertexFormatElementList elementList = 
         { { VUT_POSITION ,VFT_Float3 ,  16},
            { VUT_COLOR , VFT_Float3 , 16} };
       layout_ = createVertexLayout(elementList);
       RHIVertexLayout_D3D11 * layout_D3d11 = dynamic_cast<RHIVertexLayout_D3D11*>(layout_.get());


        pDev_->CreateInputLayout(layout_D3d11->layout_D3D11(), 2, pro->buffer_.data(), pro->buffer_size_,&pLayout_);
        //pDev_->CreateInputLayout(ied, 2, VS->GetBufferPointer(), VS->GetBufferSize(),&pLayout_);
        pDevContext_->IASetInputLayout(pLayout_);
        //VS2->Release();
        //PS->Release();

    }

    Status RHIContext_D3D11 ::setVertexLayout(RHIVertexLayoutPtr & layout)
    {
        RHIVertexLayout_D3D11 * layout_d3d11 = dynamic_cast<RHIVertexLayout_D3D11 *>(layout.get());
        pLayout_ = layout_d3d11->layout_.get();
        pDevContext_->IASetInputLayout(pLayout_);
        return Status::Ok();

    }

    Status RHIContext_D3D11 :: setVertexShader(GpuProgram & program)
    {
        if(program.type() != GpuProgram::PT_Vertex)
        {
            return Status::Error(" setVertexShader : shader type error");
        }
        GpuProgram_D3D11 & pro = dynamic_cast <GpuProgram_D3D11 &>(program);
        pDevContext_->VSSetShader(pro.vertexShader_ ,0 , 0);
        return Status::Ok();

    }
    Status RHIContext_D3D11 :: setPixelShader(GpuProgram & program)
    {
        if(program.type() != GpuProgram::PT_Pixel)
        {
            return Status::Error(" setPixelShader : shader type error");
        }
        GpuProgram_D3D11 & pro = dynamic_cast <GpuProgram_D3D11 &>(program);
        pDevContext_->PSSetShader(pro.pixelShader_ , 0 , 0);
        return Status::Ok();

    }

    Status RHIContext_D3D11 :: setVertexBuffer(RHIVertexBufferPtr buffer , RHIVertexLayoutPtr layout)
    {
        RHIVertexBufferD3D11 * ptr = dynamic_cast<RHIVertexBufferD3D11 *>(buffer.get());
        pVBuffer_ =   ptr->vertexBuffer();
        uint32_t offset = 0;
        uint32_t stride  = layout->vertexSize();
        pDevContext_->IASetVertexBuffers(0 , 1, &pVBuffer_ , &stride , & offset);

        return Status :: Ok();


    }

    Status RHIContext_D3D11 :: setIndexBuffer(RHIIndexBufferPtr buffer)
    {
        RHIIndexBufferD3D11 * ptr = dynamic_cast <RHIIndexBufferD3D11 *>(buffer.get());
        pIBuffer_ = ptr->indexBuffer();
        pDevContext_->IASetIndexBuffer(pIBuffer_,DXGI_FORMAT_R32_UINT,0);
        return Status :: Ok();

    }
    Status RHIContext_D3D11 ::setConstantBuffer(RHIConstantBufferPtr buffer) 
    {
        RHIConstantBufferD3D11 * ptr = dynamic_cast <RHIConstantBufferD3D11*>(buffer.get());
        pCBuffer = ptr->constantBuffer();
        pDevContext_->VSSetConstantBuffers(0,1,&pCBuffer);

        return Status::Ok();

    }


   
    RHIVertexBufferPtr  buffer = nullptr ;
    RHIIndexBufferPtr index_buffer = nullptr;
    RHIConstantBufferPtr constant_buffer= nullptr;
    void RHIContext_D3D11::initGraphics()
    {
        float Vertices[] =
            {
                0.45f, 0.5f, 0.0f,
                1.0f, 0.0f, 0.0f, 1.0f,

                -0.45 , 0.5f, 0.0f,
                1.0f,1.0f,1.0f,1.0f,

                0.45f, -0.5f, 0.0f,
                0.0f, 1.0f, 0.0f, 1.0f,

                -0.45f, -0.5f, 0.0f,
                0.0f, 0.0f, 1.0f, 1.0f
                };
        int Indexes[] =
            {
                1, 0, 2,
                2,1 , 3
            };
        uint32_t size = sizeof(float) * 7 *4;
        RHIBufferDataArrayD3D11 *verticeData = new RHIBufferDataArrayD3D11(Vertices ,size);

        uint32_t index_size = sizeof(int) * 6;
        RHIBufferDataArrayD3D11 * indexData = new RHIBufferDataArrayD3D11(Indexes , index_size);


        float color [4 ] = { 1.0,0.5,0.5,1.0};


        RHIBufferDataArrayD3D11 * colorData = new RHIBufferDataArrayD3D11(color ,sizeof(color));
        RHIResourceCreateInfo colorInfo(colorData);
        constant_buffer = createConstantBuffer(sizeof(color), Buf_Dynamic , colorInfo);


        RHIResourceCreateInfo info(verticeData);
        buffer =  createVertexBuffer(size, Buf_Dynamic , info);

        RHIResourceCreateInfo indexInfo(indexData);
        index_buffer = createIndexBuffer(index_size , Buf_Dynamic , indexInfo);
        

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

    void RHIContext_D3D11::drawTriangleList(uint32_t vertexCount , uint32_t startPoint)
    {
        pDevContext_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        pDevContext_->Draw(vertexCount, startPoint);
    }
    
    void RHIContext_D3D11::drawTriangleListRip(uint32_t indexCount ,uint32_t startPoint,uint32_t vertexOffset)
    {
        pDevContext_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
        pDevContext_->DrawIndexed(indexCount,startPoint,vertexOffset);
    }
    void RHIContext_D3D11::clearRenderTargetView(const Vector4f & color)
    {
        pDevContext_->ClearRenderTargetView(pRTView_ ,reinterpret_cast<const float *>( & color) );

    }



    float deltaTime = 0;

    void RHIContext_D3D11::render()
    {
        RHIVertexBuffer * ptr = buffer;
        RHIIndexBuffer * ptr_index = index_buffer;
        RHIConstantBuffer * ptr_constant = constant_buffer;

        RHIRefPtr <ID3D11Buffer>  vb = dynamic_cast<RHIVertexBufferD3D11*>(ptr)->vertexBuffer();
        RHIRefPtr <ID3D11Buffer> ib =  dynamic_cast<RHIIndexBufferD3D11*>(ptr_index)->indexBuffer();
        RHIRefPtr <ID3D11Buffer> cb = dynamic_cast <RHIConstantBufferD3D11*>(ptr_constant)->constantBuffer();

        deltaTime += 0.016;
        float color[4];
        color[0] = sin(deltaTime);
        color[1] = 0.0;
        color[2] = 1.0;
        color[3] = 1.0;
        //std::cout << color[0] <<std::endl;
        //std::flush(std::cout);
        RHIBufferDataArrayD3D11 data(color , sizeof(color));
        setConstantBufferValue(ptr_constant,&data);


        const FLOAT clearColor [] = {0.0f, 0.2f,0.4f ,1.0f};
        pDevContext_->ClearRenderTargetView(pRTView_,clearColor);
        pVBuffer_ = vb ;
        pIBuffer_ = ib;
        pCBuffer = cb;

        {
            UINT stride = sizeof(float ) * 7;
            UINT offset = 0 ;
            pDevContext_->VSSetConstantBuffers(0,1,&pCBuffer);
            pDevContext_->IASetVertexBuffers(0,1,&pVBuffer_,&stride , &offset);
            pDevContext_->IASetIndexBuffer(pIBuffer_ , DXGI_FORMAT_R32_UINT , 0);


            drawTriangleListRip(6);

            //pDevContext_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

            //pDevContext_->Draw(3,0);

        }

    }
    void RHIContext_D3D11::beginFrame()
    {

    }
    void RHIContext_D3D11::endFrame()
    {
        pSwapchain_->Present(1,0);
    }
    void RHIContext_D3D11::destroy()
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
    void RHIContext_D3D11::resize(uint32_t width , uint32_t height)
    {
        //std::cout <<  width << height << std::endl;
        rtWidth_ = width;
        rtHeight_ = height;
        pSwapchain_->ResizeBuffers(0,width ,height,DXGI_FORMAT_UNKNOWN , DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH);
        createRenderTarget();
        //setViewPort();

    }
    void RHIContext_D3D11::setViewPort(uint32_t topLeftX , uint32_t topLeftY , uint32_t width, uint32_t height)
    {
        D3D11_VIEWPORT viewport;
        ZeroMemory(&viewport , sizeof(D3D11_VIEWPORT));
        viewport.TopLeftX = topLeftX;
        viewport.TopLeftY = topLeftY;
        viewport.Width =  width;
        viewport.Height = height;
        pDevContext_->RSSetViewports(1, & viewport);
    }
    RHIVertexLayoutPtr RHIContext_D3D11::createVertexLayout(RHIVertexFormatElementList & elementList) 
    {
        return new  RHIVertexLayout_D3D11(elementList);
    }

    RHIVertexLayoutPtr RHIContext_D3D11::createVertexLayout(RHIVertexFormatElementList & elementList , GpuProgram & program) 
    {

        GpuProgram_D3D11 & pro_d3d11 = dynamic_cast<GpuProgram_D3D11&>(program);
        RHIVertexLayout_D3D11 *layout = new RHIVertexLayout_D3D11(elementList);
        pDev_->CreateInputLayout(layout->layout_D3D11(), elementList.size(),pro_d3d11.buffer_.data(),pro_d3d11.buffer_size_ ,layout->layout_.initRef());

        return layout;
    }

  


}