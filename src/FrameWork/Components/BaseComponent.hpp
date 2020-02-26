#pragma once
#include <FrameWork/Interface/IObject.hpp>
#include <FrameWork/Unit/Unit.hpp>


namespace Persist
{
interface BaseComponent : extends IObject
{

    public :
        virtual ~BaseComponent(){}
        Unit* unit() { return unit_; } 

    protected: 
        Unit * unit_  = nullptr; 


};
}
