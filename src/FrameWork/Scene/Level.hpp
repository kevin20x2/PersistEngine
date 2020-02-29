#pragma once
#include <FrameWork/Unit/Unit.hpp>
#include <FrameWork/Components/TransformComponent.hpp>

namespace Persist
{
class Level : public Unit
{
    public :
    Level()
    {
        root_ = addComponent<TransformComponent>();
    }
    TransformComponent * root() { return root_;}
    void tick() ;

    protected:
    TransformComponent * root_ = nullptr;

};

}