#pragma once
#include <FrameWork/Unit/Unit.hpp>
#include <FrameWork/Components/TransformComponent.hpp>
#include <FrameWork/Unit/CameraUnit.hpp>

namespace Persist
{
class Level : public Unit
{
    public :
    Level()
    {
        root_ = addComponent<TransformComponent>();
        currentCamera_ = new CameraUnit();
        root_->addChild(currentCamera_->getComponent<TransformComponent>());
    }
    TransformComponent * root() { return root_;}
    CameraUnit * currentCamera() { return currentCamera_;}

    void tick() ;

    protected:
    TransformComponent * root_ = nullptr;
    CameraUnit * currentCamera_ = nullptr;


};

}