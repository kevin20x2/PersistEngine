#include "RHIContext.hpp"
#include <RHI/D3D11/RHIContext_D3D11.hpp>


namespace Persist
{
    IRHIContext *IRHIContext ::RHIContext()
    {
        static RHIContext_D3D11 s_local ;
        return & s_local;
    }
}