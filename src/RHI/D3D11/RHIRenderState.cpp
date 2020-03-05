#include "RHIContext_D3D11.hpp"
#include "RHIState_D3D11.hpp"
namespace Persist
{

static D3D11_COMPARISON_FUNC TranslateCompFunc(ENMCompareFunctionType comp)
{
    switch(comp)
    {
        case CFT_Less : return D3D11_COMPARISON_LESS ;
        case CFT_LessEqual : return D3D11_COMPARISON_LESS_EQUAL;
        case CFT_Greater : return D3D11_COMPARISON_GREATER ;
        case CFT_GreaterEqual : return D3D11_COMPARISON_GREATER_EQUAL;
        case CFT_Always : return D3D11_COMPARISON_ALWAYS ;
        default : throw Status::Error("not supported type");
    }
    //return -1 ;
}


RHIDepthStencilStatePtr 
RHIContext_D3D11::createDepthStencilState(const RHIDepthStencilStateInitializer & init)
{
    RHIDepthStencilState_D3D11 * state = new RHIDepthStencilState_D3D11;

    D3D11_DEPTH_STENCIL_DESC dsDesc;

    dsDesc.DepthEnable = init.enableDepthWrite ;
    //dsDesc.DepthEnable = false ;
    dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    //dsDesc.DepthFunc = TranslateCompFunc(init.depthCompFunc);
    dsDesc.DepthFunc = TranslateCompFunc(init.depthCompFunc);

    dsDesc.StencilEnable = true;
    dsDesc.StencilReadMask = 0xFF;
    dsDesc.StencilWriteMask = 0xFF;

    dsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
    dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

    // Stencil operations if pixel is back-facing
    dsDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    dsDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
    dsDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    dsDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

    RHIRefPtr <ID3D11DepthStencilState > pDSState;
    HRESULT hr =  pDev_->CreateDepthStencilState( & dsDesc, pDSState.initRef());
    if(FAILED(hr))
    {
        throw Status ::Error("createDepthsate :  error");
    }



    state->state = pDSState;

    return state ; 
    


}

Status RHIContext_D3D11 ::setDepthStencilState(RHIDepthStencilState *state) 
{
    RHIDepthStencilState_D3D11 * s = dynamic_cast <RHIDepthStencilState_D3D11 *> (state);

    pDepthState_= s->state;

    pDevContext_->OMSetDepthStencilState(pDepthState_ , 1);

    return Status::Ok();


}
}