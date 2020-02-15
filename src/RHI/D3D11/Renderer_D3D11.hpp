#pragma once 
#include <FrameWork/Renderer/Renderer.hpp>
#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>
#include <d3dcompiler.h>



namespace Persist
{
    class Renderer_D3D11 : extends IRenderer
    {
        public: 

        // common from IRenderer
        virtual ~Renderer_D3D11() {};

        virtual int init() override ;

        virtual void destroy() override;

        virtual void beginFrame() override;

        virtual void render() override;

        virtual void endFrame() override;

        virtual void resize( uint32_t width , uint32_t height) override ;


        // d3d11 

        void setHWND(HWND hWnd)
        {
            hWnd_ = hWnd;
        }
        void createRenderTarget();
        void setViewPort();
        void initPipeline();
        void initGraphics();


        private : 
        IDXGISwapChain * pSwapchain_  = nullptr;
        ID3D11Device * pDev_           = nullptr;
        ID3D11DeviceContext * pDevContext_ = nullptr;
        ID3D11RenderTargetView * pRTView_ = nullptr;
        ID3D11VertexShader * vs_ = nullptr;
        ID3D11PixelShader * ps_ = nullptr;
        ID3D11InputLayout * pLayout_ = nullptr;

        ID3D11Buffer * pVBuffer = nullptr;

        HWND hWnd_ ;

        uint32_t rtWidth_ ;
        uint32_t rtHeight_;

        bool inited_;


    };

}