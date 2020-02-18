#pragma once

#include "../RHI.hpp"
#include <dxgi.h>
#include <d3d11.h>



namespace Persist
{
    class RHIVertexLayout_D3D11 : extends IRHIVertexLayout
    {

        public : 
        RHIVertexLayout_D3D11 (const RHIVertexFormatElementList & elmentList) ;
        static D3D11_INPUT_ELEMENT_DESC * getD3D11VertexLayout( const RHIVertexFormatElementList & elementList);

        private : 
        
        static HashMap<uint64_t , RHIRefPtr < D3D11_INPUT_ELEMENT_DESC> >  LayoutCache;

        D3D11_INPUT_ELEMENT_DESC * VertexLayout_;

    };


}