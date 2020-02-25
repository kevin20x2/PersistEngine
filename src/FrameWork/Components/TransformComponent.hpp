#pragma once
#include "BaseComponent.hpp"
#include <FrameWork/Scene/Transform.hpp>


namespace Persist
{
// Component with transform 
class TransformComponent : public BaseComponent
{
    public : 
     TransformComponent()  :
     transform_()
     {

     }
    private : 


    Transform transform_;

};

}