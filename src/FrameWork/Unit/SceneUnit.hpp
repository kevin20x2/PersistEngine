#pragma once
#include "Unit.hpp"
#include <FrameWork/Components/TransformComponent.hpp>

namespace Persist
{

class SceneUnit : public Unit
{
    public : 
        SceneUnit( ) : 
        tranform_comp_( new TransformComponent())
        {
        }


        TransformComponent * getTransformComponent()
        {
            return tranform_comp_;
        }
    protected:

        TransformComponent * tranform_comp_;



};

}