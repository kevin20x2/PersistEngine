#pragma once
#include "SceneUnit.hpp"
#include <FrameWork/Components/CameraComponent.hpp>
namespace Persist
{

class CameraUnit : public SceneUnit
{
    public : 
    CameraUnit () : 
    cameraComponent_(new CameraComponent(this))
    {
        addComponent<CameraComponent>(cameraComponent_);

    }
    void render() { cameraComponent_->render(); }

    CameraComponent * camera() { return cameraComponent_;}


    protected:

    CameraComponent * cameraComponent_ ;
};

}