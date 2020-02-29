#pragma once
#include "SceneUnit.hpp"
#include <FrameWork/Components/CameraComponent.hpp>
namespace Persist
{

class CameraUnit : public SceneUnit
{
    public : 
    CameraUnit () : 
    cameraComponent_(new CameraComponent())
    {
        addComponent<CameraComponent>(cameraComponent_);

    }

    protected:

    CameraComponent * cameraComponent_ ;
};

}