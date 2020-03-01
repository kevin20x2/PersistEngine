#pragma once

#include "../RHI.hpp"
#include <dxgi.h>
#include <d3d11.h>



namespace Persist
{
    class RHIVertexLayout_D3D11 : extends IRHIVertexLayout
    {

        public : 
        RHIVertexLayout_D3D11 (RHIVertexFormatElementList & elmentList) ;
        static D3D11_INPUT_ELEMENT_DESC * getD3D11VertexLayout(const RHIVertexFormatElementList & elementList);

        D3D11_INPUT_ELEMENT_DESC * layout_D3D11() { return VertexLayout_;}

        uint32_t vertexSize() override ;

        RHIRefPtr <ID3D11InputLayout> layout_;
        private : 
        
        static HashMap<uint64_t ,  D3D11_INPUT_ELEMENT_DESC >  LayoutCache;

        D3D11_INPUT_ELEMENT_DESC * VertexLayout_;

        uint32_t size_  = 0 ; 

    };


}