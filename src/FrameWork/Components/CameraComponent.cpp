#include "CameraComponent.hpp"
#include "TransformComponent.hpp"
#include "MeshRenderer.hpp"
#include <FrameWork/Scene/World.hpp>
#include <FrameWork/RHIContext/RHIContext.hpp>
#include <stdint.h>
namespace Persist
{


static void IterateTransform(TransformComponent * comp)
{
    MeshRenderer * renderer = comp->getComponent<MeshRenderer>();
    if(renderer != nullptr)
    {
        renderer->_commit();

    }
    uint32_t len = comp->childNum();
    for(int i = 0 ;i < len ; ++ i )
    {
        TransformComponent * child = comp->getChildAt(i);
        IterateTransform(child);
    }

}


void CameraComponent::render()
{
    //TODO : Cull 
    TransformComponent * root = World::thisWorld()->activeLevel()->root();
    IRHIContext::RHIContext()->beginFrame();
    IRHIContext::RHIContext()->clearRenderTargetView(clearColor_);

    IterateTransform(root);
    IRHIContext::RHIContext()->endFrame();
}

}