#include "Renderer.hpp"
#include <RHI/D3D11/Renderer_D3D11.hpp>


namespace Persist
{
    IRenderer *IRenderer ::renderer()
    {
        static Renderer_D3D11 s_local ;
        return & s_local;
    }
}