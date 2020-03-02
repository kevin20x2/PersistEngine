#pragma once
#include "../RHIResource.hpp"
#include <d3d11.h>

namespace Persist
{

    struct RHIDepthStencilState_D3D11 : public RHIDepthStencilState
    {
        RHIRefPtr <ID3D11DepthStencilState> state;
    };

}