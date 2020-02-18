#include "RHIVertexLayout_D3D11.hpp"
#include <algorithm>

namespace Persist 
{

HashMap <uint64_t ,  D3D11_INPUT_ELEMENT_DESC  >  RHIVertexLayout_D3D11 :: LayoutCache = 
HashMap<uint64_t ,  D3D11_INPUT_ELEMENT_DESC > () ;

RHIVertexLayout_D3D11 ::RHIVertexLayout_D3D11(RHIVertexFormatElementList & elementList)
{
    //elementList.sort();
    std::sort(elementList.begin() , elementList.end());
    //rt(elementList.begin(), elementList.end());

    uint64_t key = IRHIVertexLayout::GenerateKey(elementList);
    if(LayoutCache.find(key) == LayoutCache.end())
    {
        //LayoutCache.insert()
        VertexLayout_ = getD3D11VertexLayout(elementList);
        LayoutCache[key] = * VertexLayout_;
    }
    else 
    {
        VertexLayout_ =  &LayoutCache[key] ;
    }
}


D3D11_INPUT_ELEMENT_DESC * RHIVertexLayout_D3D11::getD3D11VertexLayout(const RHIVertexFormatElementList & elementList)
{
    uint32_t len = elementList.size();
    D3D11_INPUT_ELEMENT_DESC * LayoutList = new D3D11_INPUT_ELEMENT_DESC[len];

    for(int i = 0 ; i < len ; ++ i)
    {
        D3D11_INPUT_ELEMENT_DESC & layout = LayoutList[i];
        const ENMVertexUsageType &  usage = elementList[i].vertexUsageType;
        const ENMVertexFormatType & format = elementList[i].vertexFormatType;
        switch(usage)
        {
            case VUT_POSITION : layout.SemanticName = "POSITION" ; break;
            case VUT_COLOR    : layout.SemanticName = "COLOR"; break;
            case VUT_NORMAL   : layout.SemanticName = "NORMAL"; break;
            case VUT_TANTENT  : layout.SemanticName = "TANTENT"; break;
            default : throw Status::Error(Status::InvalidArg);
        };


        switch (format)
        {
        case VFT_Float3 : layout.Format = DXGI_FORMAT_R32G32B32_FLOAT; break;
        case VFT_Float4 : layout.Format = DXGI_FORMAT_R32G32B32A32_FLOAT ;  break;
        // TODO : fill all types 
        default:
            break;
        }

        // TODO: add more argments
        layout.InputSlot = 0 ;
        layout.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
        layout.AlignedByteOffset = 0;
        layout.InstanceDataStepRate = 0;
        //layout.AlignedByteOffset = 0;
        /// for matrix  normal 0
        layout.SemanticIndex = 0;
    }
    return LayoutList;

}


}