#pragma once 
#include <FrameWork/RHIContext/RHIContext.hpp>
#include "../RHIResource.hpp"
#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>
#include <d3dcompiler.h>



namespace Persist
{
    class RHIContext_D3D11 : extends IRHIContext
    {
        public : 
        static RHIContext_D3D11 *instance ;
        RHIContext_D3D11()
        {
            RHIContext_D3D11 ::instance = this;
        }

        
        public: 

        // common from IRHIContext
        virtual ~RHIContext_D3D11() {};

        virtual Status init() override ;

        virtual void destroy() override;

        virtual void beginFrame() override;

        virtual void render() override;

        virtual void endFrame() override;

        virtual void resize( uint32_t width , uint32_t height) override ;

        virtual RHIVertexBufferPtr createVertexBuffer(uint32_t size , uint32_t usage , RHIResourceCreateInfo & info  ) override;
        virtual RHIIndexBufferPtr createIndexBuffer(uint32_t size , uint32_t usage , RHIResourceCreateInfo & info) override;
        virtual RHIVertexLayoutPtr createVertexLayout(RHIVertexFormatElementList & elementList)  override;
        virtual RHIVertexLayoutPtr createVertexLayout(RHIVertexFormatElementList & elementList ,RHIGpuProgram & vs)  override;
        virtual RHIConstantBufferPtr createConstantBuffer(uint32_t size ,uint32_t usage , RHIResourceCreateInfo & info) override ;
        virtual Status setConstantBufferValue( RHIConstantBufferPtr , IRHIResourceArray * data) override ;


        virtual RHIDepthStencilStatePtr createDepthStencilState(const RHIDepthStencilStateInitializer & init ) override ;
        virtual Status setDepthStencilState(RHIDepthStencilState * state) override ;

        virtual Status createVertexShader(RHIGpuProgram  & program) override;
        virtual Status createPixelShader(RHIGpuProgram & program ) override; 

        virtual Status setVertexShader(RHIGpuProgram & program ) override ;
        virtual Status setPixelShader(RHIGpuProgram & program) override;
        virtual Status setVertexLayout(RHIVertexLayoutPtr & layout) override;

        virtual Status setVertexBuffer(RHIVertexBufferPtr buffer ,RHIVertexLayoutPtr layout) override;
        virtual Status setIndexBuffer(RHIIndexBufferPtr buffer) override;
        virtual Status setConstantBuffer(RHIConstantBufferPtr buffer) override;


        
        virtual int setVertexBuffer(uint32_t size , void * src , RHIVertexBuffer & dst );
        virtual void setViewPort(uint32_t  topLeftX, uint32_t topLeftY , uint32_t width , uint32_t height) override; 
        virtual void clearRenderTargetView(const Vector4f  & color) override;

        virtual void drawTriangleList(uint32_t vertexCount , uint32_t startPoint = 0) override;
        virtual void drawTriangleListRip(uint32_t indexCount , uint32_t startPoint = 0 , uint32_t vertexOffset = 0) override;


        // d3d11 

        void setHWND(HWND hWnd)
        {
            hWnd_ = hWnd;
        }
        void createRenderTarget();
        void setViewPort();
        void initPipeline();
        void initGraphics();

        ID3D11DeviceContext * getDeviceContext() { return pDevContext_; }
        Status createDepthStencilBuffer();

        private : 

        IDXGISwapChain * pSwapchain_  = nullptr;
        ID3D11Device * pDev_           = nullptr;
        ID3D11DeviceContext * pDevContext_ = nullptr;
        ID3D11RenderTargetView * pRTView_ = nullptr;
        ID3D11VertexShader * vs_ = nullptr;
        ID3D11PixelShader * ps_ = nullptr;
        ID3D11InputLayout * pLayout_ = nullptr;

        ID3D11Buffer * pVBuffer_ = nullptr;
        ID3D11Buffer * pIBuffer_ = nullptr;
        ID3D11Buffer * pCBuffer = nullptr;

        ID3D11Texture2D * pDepthStencil_ = nullptr;
        ID3D11DepthStencilView * pDSV_ = nullptr;
        ID3D11DepthStencilState * pDepthState_ = nullptr;

        RHIVertexLayoutPtr layout_;


        HWND hWnd_ ;

        uint32_t rtWidth_ ;
        uint32_t rtHeight_;

        bool inited_;


    };

}